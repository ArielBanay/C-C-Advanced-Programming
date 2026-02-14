
#include "Pokemon.h"
#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

B_info* create_biology_information(double h, double w, int a) {

    //Memory allocation and success check
    B_info* pB_info=(B_info*)malloc(sizeof(B_info));
    if (pB_info==NULL) {return NULL;}

    //Assigning the appropriate values to the relevant fields
    pB_info->height=h;
    pB_info->weight=w;
    pB_info->atk=a;
    return pB_info;
}

P_type* create_pokemon_type(char* name){
    //pointer testing
    if (name==NULL){return NULL;}

    //Allocating memory for the type name
    P_type* pP_type=(P_type*)malloc(sizeof(P_type));
    if (pP_type==NULL) {return NULL;}

    //Allocating a dynamic array to save the name field
    pP_type->name = malloc((strlen(name)+1)*sizeof(char));
    if (pP_type->name==NULL) {
        free(pP_type);
        return  NULL;
    }
    //Assigning the appropriate values to the relevant fields
    strcpy(pP_type->name,name);
    pP_type->cnt_type=0;
    pP_type->num_ea_me=0;
    pP_type->num_ea_others=0;
    pP_type->ea_me=NULL;
    pP_type->ea_others=NULL;
    return pP_type;
}

Poke* create_pokemon(P_type* pP_type, char* pname, char* pspecies, double h, double w, int a) {
    //Pointer testing
    if (pP_type==NULL || pname==NULL || pspecies==NULL){return NULL;}

    //Allocate memory and check if it was successful. If not, release all allocations that were successful so far.
    Poke* pPoke=(Poke*)malloc(sizeof(Poke));
    if (pPoke==NULL) {return NULL;}

    //Allocate memory and check if it was successful. If not, release all allocations that were successful so far.
    B_info* pB_info=create_biology_information(h,w,a);
    if (pB_info==NULL) {
        free(pPoke);
        return NULL;
    }

    //Allocate memory and check if it was successful. If not, release all allocations that were successful so far.
    char* tname = (char*)malloc(strlen(pname)+1);
    if (tname==NULL) {
        free(pPoke);
        free(pB_info);
        return NULL;
    }

    //Allocate memory and check if it was successful. If not, release all allocations that were successful so far.
    char* tspecies = (char*)malloc(strlen(pspecies)+1);
    if (tspecies==NULL) {
        free(pPoke);
        free(pB_info);
        free(tname);
        return NULL;
    }
    //Assigning the appropriate values to the relevant fields
    strcpy(tname,pname);
    strcpy(tspecies,pspecies);
    pPoke->bio_info=pB_info;
    pPoke->pokename=tname;
    pPoke->species=tspecies;
    pPoke->type=pP_type;
    pPoke->type->cnt_type++;
    return pPoke;
}

status add_to_ea_me(P_type* pP_typea, P_type* pP_typeb) {
    //Checking whether the pointers we received are different from NULL
    if (pP_typea==NULL || pP_typeb==NULL){return failure;}
    pP_typea->num_ea_me++;
    //New space allocation with one additional space for the new type added to the list
    P_type** temp=(P_type** )realloc(pP_typea->ea_me,pP_typea->num_ea_me*sizeof(P_type*));
    //Memory allocation check
    if (temp==NULL) {
        pP_typea->num_ea_me--;
        return memory_error;
    }
    pP_typea->ea_me=temp;
    //Adding the new type to the end of the list
    pP_typea->ea_me[pP_typea->num_ea_me-1]=pP_typeb;
    return success;
}

status add_to_ea_others(P_type* pP_typea, P_type* pP_typeb) {
    //Checking whether the pointers we received are different from NULL
    if (pP_typea==NULL || pP_typeb==NULL){return failure;}
    pP_typea->num_ea_others++;
    //New space allocation with one additional space for the new type added to the list
    P_type** temp=(P_type** )realloc(pP_typea->ea_others,pP_typea->num_ea_others*sizeof(P_type*));
    //Memory allocation check
    if (temp==NULL) {
        pP_typea->num_ea_others--;
        return memory_error;
    }
    pP_typea->ea_others=temp;
    //Adding the new type to the end of the list
    pP_typea->ea_others[pP_typea->num_ea_others-1]=pP_typeb;
    return success;
}

status remove_from_ea_me(P_type* pP_typea, char* name_typeb) {
    //Checking whether the pointers we received are different from NULL
    if (pP_typea==NULL || name_typeb==NULL){return failure;}
    //If there are no types in the list, we will return failure because there is nothing to remove.
    if (pP_typea->num_ea_me<=0) {return failure;}
    //Special treatment in the case where exactly one type exists in this list.
    if (pP_typea->num_ea_me==1) {
        if (strcmp(pP_typea->ea_me[0]->name,name_typeb)==0) {
            pP_typea->num_ea_me--;
            free(pP_typea->ea_me);
            pP_typea->ea_me=NULL;
            return success;
        }
        else {
            return failure;
        }
    }
    //Iterating over all array elements and comparing names.
    //If the type to be removed is in the list, the value of the flag will change.
    bool flag = false;
    for (int i=0; i<pP_typea->num_ea_me; i++) {
        if (strcmp(pP_typea->ea_me[i]->name,name_typeb)==0) {
            flag = true;
            break;
        }
    }
    //Allocating a new memory location for the array after deletion.
    //Scraping the relevant content from the original array.
    if (flag==true) {
        P_type** temp=(P_type**)malloc(((pP_typea->num_ea_me-1)*sizeof(P_type*)));
        //Allocation of new memory location failed. NULL pointer.
        if (temp==NULL){return failure;}

        int idx=0;
        for (int j=0; j<pP_typea->num_ea_me; j++) {
            if (strcmp(pP_typea->ea_me[j]->name,name_typeb)!=0) {
                temp[idx]=pP_typea->ea_me[j];
                idx++;
            }
        }
        //Deallocating memory for the previous pointer and updating pointers.
        free(pP_typea->ea_me);
        pP_typea->ea_me=temp;
        pP_typea->num_ea_me--;
        return success;
    }
    //The name is not on the list.
    return failure;
}

status remove_from_ea_others(P_type* pP_typea, char* name_typeb) {
    //Checking whether the pointers we received are different from NULL
    if (pP_typea==NULL || name_typeb==NULL){return failure;}
    //If there are no types in the list, we will return failure because there is nothing to remove.
    if (pP_typea->num_ea_others<=0) {return failure;}
    //Special treatment in the case where exactly one type exists in this list.
    if (pP_typea->num_ea_others==1) {
        if (strcmp(pP_typea->ea_others[0]->name,name_typeb)==0) {
            pP_typea->num_ea_others--;
            free(pP_typea->ea_others);
            pP_typea->ea_others=NULL;
            return success;
        }
        else {
            return failure;
        }
    }

    //Iterating over all array elements and comparing names.
    //If the type to be removed is in the list, the value of the flag will change.
    bool flag = false;
    for (int i=0; i<pP_typea->num_ea_others; i++) {
        if (strcmp(pP_typea->ea_others[i]->name,name_typeb)==0) {
            flag = true;
            break;
        }
    }
    //Allocating a new memory location for the array after deletion.
    //Scraping the relevant content from the original array.
    if (flag==true) {
        P_type** temp=(P_type**)malloc(((pP_typea->num_ea_others-1)*sizeof(P_type*)));
        //Allocation of new memory location failed. NULL pointer.
        if (temp==NULL){return failure;}

        int idx=0;
        for (int j=0; j<pP_typea->num_ea_others; j++) {
            if (strcmp(pP_typea->ea_others[j]->name,name_typeb)!=0) {
                temp[idx]=pP_typea->ea_others[j];
                idx++;
            }
        }
        //Deallocating memory for the previous pointer and updating pointers.
        free(pP_typea->ea_others);
        pP_typea->ea_others=temp;
        pP_typea->num_ea_others--;
        return success;
    }
    //The name is not on the list.
    return failure;
}

status print_pokemon(Poke* pPoke) {
    //Checking whether the pointers we received are different from NULL
    if (pPoke==NULL || pPoke->bio_info==NULL || pPoke->type==NULL || pPoke->pokename==NULL || pPoke->species==NULL || pPoke->type->name==NULL) {return failure;}

    //Print according to appropriate format.
    printf("%s :\n",pPoke->pokename);
    printf("%s, %s Type.\n", pPoke->species,pPoke->type->name);
    printf("Height: %.2f m    Weight: %.2f kg    Attack: %.2d\n\n", pPoke->bio_info->height, pPoke->bio_info->weight, pPoke->bio_info->atk);
    return success;
}

status print_type(P_type* pP_type) {
    //Checking whether the pointers we received are different from NULL
    if (pP_type==NULL || pP_type->name==NULL ) {return failure;}

    printf("Type %s -- %d pokemons\n",pP_type->name,pP_type->cnt_type);

    //Checking whether the lists are empty or not.
    if (pP_type->num_ea_me>0 && pP_type->ea_me!=NULL) {
        printf("\tThese types are super-effective against %s:",pP_type->name);
        for (int i=0; i<pP_type->num_ea_me; i++) {
            if (pP_type->ea_me[i]->name!=NULL) {
                printf("%s%s",(i==0 ? "" : " ,"),pP_type->ea_me[i]->name);
            }
        }
        printf("\n");
    }
    if (pP_type->num_ea_others>0 && pP_type->ea_others!=NULL) {
        printf("\t%s moves are super-effective against:",pP_type->name);
        for (int i=0; i<pP_type->num_ea_others; i++) {
            if (pP_type->ea_others[i]->name!=NULL) {
                printf("%s%s",(i==0 ? "" : " ,"),pP_type->ea_others[i]->name);
            }
        }
        printf("\n");
    }
    //Adding a line of space for the desired format.
    printf("\n");
    return success;
}

status free_pokemon(Poke* pPoke) {
    if (!pPoke){return failure;}
    //Freeing memory allocations from the inside out according to the principle
    if (pPoke->type!=NULL){pPoke->type->cnt_type--;}
    free(pPoke->pokename);
    free(pPoke->species);
    free(pPoke->bio_info);
    free(pPoke);
    return success;
}

void free_type(P_type* pP_type) {
    //Freeing memory allocations from the inside out according to the principle
    free(pP_type->ea_me);
    free(pP_type->ea_others);
    free(pP_type->name);
    free(pP_type);
}

