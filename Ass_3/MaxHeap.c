#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "MaxHeap.h"

/**
 * Represents a generic Max-Heap data structure.
 * The heap is implemented using a dynamic array and stores elements
 * of any type, maintaining the Max-Heap rules where the largest
 * element is always at the root.
 */
struct MaxHeap_s {
    element* array;
    int MaxSize;
    int capacity;
    char* h_name;
    copyFunction copyfunc;
    freeFunction freefunc;
    printFunction printfunc;
    equalFunction eqlfunc;
};

/**
 * Auxiliary function for self use only.
 * Maintains the Max-Heap property by recursively move down an element.
 * @param heap A pointer to the MaxHeap structure.
 * @param i The index of the node that may violate the Max-Heap property.
 * @return Void.
 */
static void max_heapify (MaxHeap heap, int i) {
    //input validation
    if (!heap) {return;}

    int largest;
    int l = 2*i+1;
    int r = 2*i+2;

    if (l<heap->capacity && heap->eqlfunc(heap->array[l],heap->array[i])==1) {
        largest=l;
    }
    else {largest=i;}
    if (r<heap->capacity && heap->eqlfunc(heap->array[r],heap->array[largest])==1) {
        largest=r;
    }
    if (largest!=i) {
        element temp=heap->array[i];
        heap->array[i]=heap->array[largest];
        heap->array[largest]=temp;
        max_heapify(heap,largest);
    }
}

MaxHeap createHeap(char* name, int Max, copyFunction copyFunc, freeFunction freeFunc, printFunction printFunc, equalFunction eqlFunc) {
    //input validation
    if (!name || !copyFunc || !freeFunc || !printFunc || !eqlFunc || Max<0 ) {return NULL;}

    //Allocating memory and deep copying the string representing the heap name
    char* temp_name=(char*)malloc(strlen(name)+1);
    if (!temp_name) {return NULL;}
    strcpy(temp_name,name);

    //Allocating memory for the array
    element* temp_arr=(element*)malloc(sizeof(element)*Max);
    if (!temp_arr) {
        free(temp_name);
        return NULL;
    }

    //Allocating memory for the struct itself
    MaxHeap heap=(MaxHeap)malloc(sizeof(struct MaxHeap_s));
    if (!heap) {
        free(temp_arr);
        free(temp_name);
        return NULL;
    }

    //Initializing the struct members with the relevant values
    heap->array=temp_arr;
    heap->MaxSize=Max;
    heap->capacity=0;
    heap->h_name=temp_name;
    heap->copyfunc=copyFunc;
    heap->freefunc=freeFunc;
    heap->printfunc=printFunc;
    heap->eqlfunc=eqlFunc;
    return heap;
}

MaxHeap copyHeap(MaxHeap old) {
    //input validation
    if (!old) {return NULL;}

    //Creating a copy of the existing heap by using the existing heap members and a function that creates a new heap.
    MaxHeap new_heap=createHeap(old->h_name,old->MaxSize,old->copyfunc,old->freefunc,old->printfunc,old->eqlfunc);
    if (!new_heap) {return NULL;}

    //deepcopy of the array whose represent the heap itself.
    for (int i=0; i<old->capacity; i++) {
        element to_add = old->copyfunc(old->array[i]);
        if (!to_add) {
            destroyHeap(new_heap);
            return NULL;
        }
        new_heap->array[i]=to_add;
        new_heap->capacity++;
    }
    return new_heap;
}

status destroyHeap(MaxHeap heap) {
    //input validation
    if (!heap) {return failure;}

    //destroy all the elements in the array first according to inside out principle.
    for (int i=0; i<heap->capacity; i++) {
        heap->freefunc(heap->array[i]);
    }
    //free the fields of the structure itself that are stored in the heap
    free(heap->array);
    free(heap->h_name);
    free(heap);
    return success;
}

status printHeap(MaxHeap heap) {
    //input validation
    if (!heap||!heap->h_name) {return failure;}

    //copy of the origin heap in order to allow the heap to be destroyed by performing an extract max
    MaxHeap newheap=copyHeap(heap);
    if (!newheap) {return memory_error;}

    //Printing the first line according to the requested format
    printf("%s:\n",newheap->h_name);

    //no elements in the heap
    if (newheap->capacity<=0){
        printf("No elements.\n\n");

        //Deallocating memory for the copy of the heap we created
        destroyHeap(newheap);
        return success;
    }

    //capacity>0
    int i=1;

    //Holding a temporary pointer to the current maximum element on the heap.
    element elem=PopMaxHeap(newheap);

    //Removing all elements from the heap according to size
    while (elem!=NULL) {
        //Printing according to the requested format
        printf("%d. ",i);
        newheap->printfunc(elem);
        //Deallocating the element that removed from the heap
        newheap->freefunc(elem);
        //Retrieving the next largest element from the heap
        elem=PopMaxHeap(newheap);
        i++;
    }
    //Deallocating memory for the copy of the heap we created
    destroyHeap(newheap);
    return success;
}

char* getHeapid(MaxHeap heap) {
    //input validation
    if (!heap) {return NULL;}
    //allocating memory for the deepcopy of the name will be returnred
    char* temp_name=(char*)malloc(strlen(heap->h_name)+1);
    if (!temp_name) {return NULL;}
    strcpy(temp_name,heap->h_name);
    //return copy of the heapname
    return temp_name;
}

int getHeapCurrentSize(MaxHeap heap) {
    //input validation
    if (!heap) {return -1;}
    return heap->capacity;
}

element PopMaxHeap(MaxHeap heap) {
    //input validation
    if (!heap || heap->capacity==0) {return NULL;}

    //Retrieving the maximum element from the heap and updating the heap structure using a helper function
    element max=heap->array[0];
    heap->array[0]=heap->array[heap->capacity-1];
    heap->capacity--;

    if (heap->capacity>0) {
        max_heapify(heap,0);
    }

    return max;
}

element TopMaxHeap (MaxHeap heap) {
    //input validation
    if (!heap || heap->capacity==0) {return NULL;}
    return heap->array[0];
}

status insertToHeap(MaxHeap heap,element elem) {
    //input validation
    if (!heap || !elem ) {return failure;}

    //full capacity
    if (heap->capacity==heap->MaxSize){return failure_fullcapacity;}

    //enough place to add 1 more element
    element to_add=heap->copyfunc(elem);
    if (!to_add) {return memory_error;}

    //Adding the new element to the last position in the array and rearranging the array according to heap rules
    heap->array[heap->capacity]=to_add;
    heap->capacity++;
    int i=heap->capacity-1;
    while (i>0 && heap->eqlfunc(heap->array[i],heap->array[(i-1)/2])==1) {
        element temp=heap->array[i];
        heap->array[i]=heap->array[(i-1)/2];
        heap->array[(i-1)/2]=temp;
        i=(i-1)/2;
    }
    return success;
}