#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "BattleByCategory.h"
#include "LinkedList.h"
#include "MaxHeap.h"

/**
 * Represents the main Battle system structure.
 * This structure acts as a container for managing
 * multiple MaxHeaps stored within a linked list.
 * It holds the configuration for category limits and the necessary logic
 * for battling and data management.
 */
struct battle_s {
    int capacity;
    int numberOfCategories;
    char* categories;
    LinkedList category_l_list;
    copyFunction copyfunc;
    freeFunction freefunc;
    printFunction printfunc;
    equalFunction eqlfunc;
    getCategoryFunction getcatfunc;
    getAttackFunction getatkfunc;
};

/**
 * Auxiliary function for self use only.
 * wrapper for the copyHeap function to match the generic copyFunction signature.
 * @param elem The generic element (MaxHeap) to be copied.
 * @return A generic pointer to the new copy of the MaxHeap, or NULL if the input is NULL.
 */
static element copyHeapWrap(element elem) {
    if (!elem) {return NULL;}
    return (element)copyHeap((MaxHeap)elem);
}

/**
 * Auxiliary function for self use only.
 * wrapper for the destroyHeap function to match the generic freeFunction signature.
 * @param elem The generic element (MaxHeap) to be destroyed.
 * @return success if the heap was destroyed, or failure if the input is NULL.
 */
static status destroyHeapWrap(element elem){
    if (!elem) {return failure;}
    return destroyHeap((MaxHeap)elem);
}

/**
 * Auxiliary function for self use only.
 * A wrapper for printHeap to match the printFunction signature.
 * @param elem The generic element to be printed.
 * @return success if printed, memory_error if a memory allocation failed during printing,
 * or failure if the input is NULL.
 */
static status printHeapWrap(element elem) {
    if (!elem) {return failure;}
    return printHeap((MaxHeap)elem);
}

/**
 * Auxiliary function for self use only.
 * Compares a heap's name with a given key string.
 * @param e_heap The generic element (MaxHeap) to check.
 * @param e_key The key string to compare against the heap's name.
 * @return 0 if the names match, or -1 if they do not match or an error occurs.
 */
static int equalheap(element e_heap, element e_key){
    if (!e_heap || !e_key){return -1;}

    MaxHeap heap = (MaxHeap)e_heap;
    char* n_heap = getHeapid(heap);
    if (!n_heap){return -1;}

    char* key = (char*)e_key;
    int cmp = strcmp(key,n_heap);
    free(n_heap);
    if (cmp==0) {return 0;}
    return -1;
}

/**
 * Auxiliary function for self use only.
 * Compares two heaps by their names to follow the equalFunction format.
 * @param elem1 First generic element (MaxHeap).
 * @param elem2 Second generic element (MaxHeap).
 * @return 1 if first name > second, -1 if first < second, or 0 if equal.
 * 2 if input is NULL or memory allocation failed.
 */
static int cmpheap(element elem1,element elem2) {
    //input validation
    if (!elem1 || !elem2) {return 2;}

    //temporarily vars represent heaps names
    char* id1 = getHeapid((MaxHeap)elem1);
    char* id2 = getHeapid((MaxHeap)elem2);

    //check if the malloc in getHeapid succeded
    if (!id1 || !id2) {return 2;}

    //the real comparing
    int result = strcmp(id1,id2);

    //deallocate memory of both strings
    free(id1);
    free(id2);

    //return value according the format of equalfunc in Defs.h file
    if (result>0) {return 1;}
    if (result<0) {return -1;}
    return 0;
}

Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement) {
    //input validation
    if (!categories || !equalElement || !copyElement ||! printElement || !freeElement ||!getCategory ||!getAttack || capacity<0) {
        return NULL;
    }
    //Allocating memory for deepcopy of 'categories' input string.
    char* temp_categories=malloc(strlen(categories)+1);
    if (!temp_categories) {return NULL;}
    strcpy(temp_categories,categories);

    //Allocating memory for the linked list structure and releasing the allocations that have succeeded so far if the current allocation fails.
    LinkedList temp_l=createLinkedList(copyHeapWrap,destroyHeapWrap,printHeapWrap,equalheap,cmpheap);
    if (!temp_l) {
        free(temp_categories);
        return NULL;
    }

    //Allocating memory for the Battle structure and releasing the allocations that have succeeded so far if the current allocation fails.
    Battle battle = (Battle)malloc(sizeof(struct battle_s));
    if (!battle) {
        destroyLinkedList(temp_l);
        free(temp_categories);
        return NULL;
    }

    //Construction of the linked list where each link contains a max heap
    char* token = strtok(categories,",");
    while (token!=NULL) {
        //Allocating memory for the 'Max_Heap'. The stack name will be the current 'category' according to the string we received as input from the user.
        MaxHeap temp_h = createHeap(token,capacity,copyElement,freeElement,printElement,equalElement);
        if (!temp_h) {
            destroyLinkedList(temp_l);
            free(temp_categories);
            destroyBattleByCategory(battle);
            return NULL;
        }
        //Adding the heap as a link in the linked list and checking that the addition was successful.
        status st = appendNode(temp_l, temp_h);
        if (st==failure || st==memory_error) {
            destroyLinkedList(temp_l);
            free(temp_categories);
            destroyHeap(temp_h);
            destroyBattleByCategory(battle);
            return NULL;
        }
        destroyHeap(temp_h);
        //Promote the 'category' to the next category in the string.
        token = strtok(NULL,",");
    }

    //Placing the appropriate values in the members of the Battle struct
    battle->capacity=capacity;
    battle->numberOfCategories=numberOfCategories;
    battle->categories=temp_categories;
    battle->category_l_list=temp_l;
    battle->copyfunc=copyElement;
    battle->freefunc=freeElement;
    battle->printfunc=printElement;
    battle->eqlfunc=equalElement;
    battle->getcatfunc=getCategory;
    battle->getatkfunc=getAttack;
    return battle;
}

status destroyBattleByCategory(Battle b) {
    if (!b) {return failure;}

    free(b->categories);

    if (destroyLinkedList(b->category_l_list)==success){
        free(b);
        return success;
    }
    free(b);
    return failure;
}

status insertObject(Battle b, element elem) {
    //input validation
    if (!b || !elem) {return failure;}

    //Checking the element's category
    char* temp_category=b->getcatfunc(elem);
    if (!temp_category) {return failure;}

    //Finding the relevant link in the linked list into which we will insert the desired element
    MaxHeap temp_h = searchByKeyInList(b->category_l_list,temp_category);
    if (!temp_h) {return failure;}

    //Inserting into the heap and returning the status whether the insertion was successful or not
    return insertToHeap(temp_h,elem);
}

void displayObjectsByCategories(Battle b) {
    //input validation
    if (!b) {return;}

    //call to linked list print func
    printLinkedList(b->category_l_list);
}

element removeMaxByCategory(Battle b,char* category) {
    //input validation
    if (!b || !category) {return NULL;}

    //Finding the relevant heap in the linked list
    MaxHeap temp_h = searchByKeyInList(b->category_l_list,category);
    if (!temp_h) {return NULL;}

    //Remove the strongest element from the current heap and return it to the user
    element strongest = PopMaxHeap(temp_h);
    if (!strongest) {return NULL;}
    return strongest;
}

int getNumberOfObjectsInCategory(Battle b,char* category) {
    //input validation
    if (!b || !category) {return -1;}

    //Finding the relevant heap in the linked list
    MaxHeap temp_h = searchByKeyInList(b->category_l_list,category);
    if (!temp_h) {return 0;}

    return getHeapCurrentSize(temp_h);
}

element fight(Battle b,element elem) {
    if (!b || !elem) {return NULL;}

    char* temp_category=(char*)malloc(strlen(b->categories)+1);
    if (!temp_category) {return NULL;}
    strcpy(temp_category,b->categories);

    char* token = strtok(temp_category,",");
    if (!token) {
        free(temp_category);
        return NULL;
    }

    MaxHeap temp_h;
    element current;
    element strongest=NULL;
    int best_c_atk=0;
    int best_e_atk=0;
    int curr_c_atk;
    int curr_e_atk;

    int diff=0;
    int total=0;
    // f serves as a flag for me and ensures that if all candidates are weaker than the opponent,
    // we will still put the least bad option in the fight against him.
    bool f=false;

    while (token!=NULL) {
        temp_h = searchByKeyInList(b->category_l_list,token);
        if (temp_h==NULL) {
            free(temp_category);
            return NULL;
        }

        total+=getHeapCurrentSize(temp_h);

        current = TopMaxHeap(temp_h);
        if (!current) {
            token = strtok(NULL,",");
            continue;
        }

        int curr_diff = b->getatkfunc(current,elem,&curr_c_atk,&curr_e_atk);
        if (curr_diff>diff || f==false) {
            f=true;
            diff = curr_diff;
            strongest=current;
            best_c_atk=curr_c_atk;
            best_e_atk=curr_e_atk;
        }
        token = strtok(NULL,",");
    }

    // There is no enemies in the system to fight against 'elem'.
    if (total==0 || strongest==NULL) {
        free(temp_category);
        return (element)-1;
    }

    //prints part
    printf("The final battle between:\n");
    b->printfunc(elem);
    printf("In this battle his attack is :%d\n\n",best_e_atk);
    printf("against ");
    b->printfunc(strongest);
    printf("In this battle his attack is :%d\n\n",best_c_atk);

    if (diff>0) {
        printf("THE WINNER IS:\n");
        b->printfunc(strongest);
        free(temp_category);
        return strongest;
    }
    if (diff<0) {
        printf("THE WINNER IS:\n");
        b->printfunc(elem);
        free(temp_category);
        return elem;
    }
    printf("IT IS A DRAW.\n");
    free(temp_category);
    return strongest;
}





