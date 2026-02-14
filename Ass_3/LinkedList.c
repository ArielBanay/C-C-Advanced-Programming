#include <stddef.h>
#include <stdlib.h>
#include "LinkedList.h"

/**
 * Represents a single node in the doubly linked list.
 * Each node stores a generic element and pointers to its neighbors,
 * allowing for both directions traversal.
 */
typedef struct Node_s {
    element prim_p;
    struct Node_s* prev;
    struct Node_s* next;
} Node;

/**
 * Internal structure representing a doubly linked list.
 * It saved pointers to the head and tail nodes for efficient access
 * and stores function pointers for handling generic elements.
 */
struct LinkedList_T {
    Node* head;
    Node* tail;
    copyFunction copyfunc;
    freeFunction freefunc;
    printFunction printfunc;
    equalFunction eqlfunc;
    equalFunction cmpfunc;
};

/**
 * Auxiliary function for internal use only.
 * Creates a new node for the linked list and performs a deep copy of the given element.
 * This function allocates memory for a Node structure, invokes the provided copy
 * function to duplicate the generic element, and initializes the node's pointers to NULL.
 * @param elem The generic element to be stored in the node.
 * @param copy_function A pointer to a function that creates a deep copy of the element.
 * @return A pointer to the newly created Node, or NULL if memory allocation fails,
 * if the element is NULL, or if the copy function fails.
 */
static Node* createNode(element elem,copyFunction copy_function) {
    //Input validation
    if (!elem) {return NULL;}

    //Allocate memory for the current cell
    Node* temp=malloc(sizeof(Node));
    if (!temp) {return NULL;}

    //Updating the fields of the cell we just created
    element new_elem=copy_function(elem);
    if (!new_elem) {
        free(temp);
        return NULL;
    }

    //Initializing the relevant fields
    temp->prim_p=new_elem;
    temp->prev=NULL;
    temp->next=NULL;
    return temp;
}

LinkedList createLinkedList(copyFunction copyFunc, freeFunction freeFunc, printFunction printFunc, equalFunction eqlFunc , equalFunction cmpFunc) {
    //input validation
    if (!copyFunc || !freeFunc || !printFunc || !eqlFunc || !cmpFunc) {return NULL; }

    //Allocating memory for the linked list structure
    LinkedList l_list=(LinkedList)malloc(sizeof(struct LinkedList_T));

    //check allocation
    if (!l_list) {return NULL; }

    //Initializing the relevant fields
    l_list->head=NULL;
    l_list->tail=NULL;
    l_list->copyfunc=copyFunc;
    l_list->freefunc=freeFunc;
    l_list->printfunc=printFunc;
    l_list->eqlfunc=eqlFunc;
    l_list->cmpfunc=cmpFunc;
    return l_list;
}

status destroyLinkedList(LinkedList l_list) {
    //validate arguments
    if (!l_list) { return failure;}

    //empty list,
    if (l_list->head==NULL) {
        free(l_list);
        return success;
    }

    //iterate over all the nodes and free each.
    Node* temp=l_list->head;

    while (temp!=NULL) {
        Node* next=temp->next;

        //free the main component of the Node by its specific free function
        if (l_list->freefunc(temp->prim_p)==failure) {
            return failure;
        }

        //free of the current Node
        free(temp);

        //Promote the temp pointer to the next node
        temp=next;
    }

    //free the linked list itself
    free(l_list);
    return success;
}

status appendNode(LinkedList l_list, element elem){
    //input validation
    if (!l_list || !elem) {return failure;}

    //create new Node struct
    Node* temp=createNode(elem,l_list->copyfunc);
    if (!temp) {return memory_error;}

    //case analysis
    //first element added
    if (l_list->head==NULL) {
        l_list->head=temp;
        l_list->tail=temp;
        return success;
    }
    //l_list contain at least 1 element
    l_list->tail->next=temp;
    temp->prev=l_list->tail;
    l_list->tail=temp;
    return success;
}

status deleteNode(LinkedList l_list, element elem) {
    //input validation
    if (!l_list || !elem) {return failure;}

    //iterate over all the nodes to find the relevant one.
    Node* temp=l_list->head;
    while (temp!=NULL) {
        if (temp->prim_p!=NULL && l_list->eqlfunc(temp->prim_p,elem)==0) {

            //only one object in the linked_list
            if (temp==l_list->head && temp==l_list->tail ){l_list->head=NULL;l_list->tail=NULL;}

            //headcase
            else if (temp==l_list->head && temp!=l_list->tail ) {
                l_list->head=l_list->head->next;
                temp->next->prev=NULL;
            }

            //tailcase
            else if (temp!=l_list->head && temp==l_list->tail) {
                l_list->tail=l_list->tail->prev;
                temp->prev->next=NULL;
            }

            //middlecase
            else {
                temp->prev->next=temp->next;
                temp->next->prev=temp->prev;
            }
            //in all cases free Node
            l_list->freefunc(temp->prim_p);
            free(temp);
            return success;
        }
        //Move to the next element in the linked list
        temp=temp->next;
    }
    //All links in the linked list were traversed and the requested element was not found.
    return failure;
}

status printLinkedList(LinkedList l_list) {
    //input validation
    if (!l_list) {return failure;}

    //Holding a temporary pointer with which we will iterate over all the elements in the list.
    Node* temp=l_list->head;
    while (temp!=NULL) {
        //Calling the print function that the user entered when creating the data structure and checking whether the printing was successful
        if (l_list->printfunc(temp->prim_p)==failure) {
            return failure;
        }
        //Move to the next element in the linked list
        temp=temp->next;
    }
    return success;
}

element searchByKeyInList(LinkedList l_list, element key) {
    //input validation
    if (!l_list || !key) {return NULL;}

    //Holding a temporary pointer with which we will iterate over all the elements in the list.
    Node* temp=l_list->head;

    while (temp!=NULL) {
        //Compares the value in the current cell to the requested value and returns it if there is a match.
        if (temp->prim_p!=NULL && l_list->eqlfunc(temp->prim_p,key)==0) {
            return temp->prim_p;
        }
        //Move to the next element in the linked list
        temp=temp->next;
    }
    //No element was found that met the search criteria.
    return NULL;
}