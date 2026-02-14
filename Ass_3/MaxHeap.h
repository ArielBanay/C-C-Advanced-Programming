#ifndef ASS_3_MAXHEAP_H
#define ASS_3_MAXHEAP_H
#include "Defs.h"

//Pointer alias for the generic ADT Heap
typedef struct MaxHeap_s* MaxHeap;

/**
 * Creates and initializes a new generic MaxHeap structure.
 * This function allocates memory for the heap structure, the internal array, and
 * performs a deep copy of the heap's name.
 * It also sets up the necessary generic function pointers.
 * @param name A string representing the name/identifier of the heap.
 * @param Max The maximum capacity (num of elements) the heap can hold.
 * @param copyFunc A pointer to a function that performs a deep copy of an element.
 * @param freeFunc A pointer to a function that deallocates memory for an element.
 * @param printFunc A pointer to a function that prints an element.
 * @param eqlFunc A pointer to a function that compares two elements (returns 1 if first > second 0 if first==second -1 if first<second).
 * @return A pointer to the newly created MaxHeap, or NULL if any input is invalid.
 */
MaxHeap createHeap(char* name, int Max, copyFunction copyFunc, freeFunction freeFunc, printFunction printFunc, equalFunction eqlFunc);

/**
 * Creates a deep copy of an existing MaxHeap.
 * This function allocates a new MaxHeap as same as the original,
 * then perform a deep copy of each element using the heap's specific copy function.
 * @param old A pointer to the MaxHeap to be copied.
 * @return A pointer to the new MaxHeap or NULL if the original heap is NULL or allocation memory had failed.
 */
MaxHeap copyHeap(MaxHeap old);

/**
 * Destroys the MaxHeap and frees all its memory.
 * This function first frees all elements in the array using the heap's free function,
 * @param heap A pointer to the MaxHeap to be destroyed.
 * @return success if the heap was destroyed, or failure if the pointer is NULL.
 */
status destroyHeap(MaxHeap heap);

/**
* Prints the heap elements from largest to smallest.
* This function creates a temporary copy of the heap to extract elements
* without changing the original heap. It prints each element and frees the temporary copy when finished.
* @param heap A pointer to the MaxHeap to be printed.
* @return success if the heap was printed, memory_error if memory allocation
* for the temporary copy failed, or failure if the original heap pointer is invalid.
*/
status printHeap(MaxHeap heap);

/**
 * Returns a copy of the heap's name.
 * This function allocates memory and creates a deep copy of the id member of the heap.
 * The caller is responsible for freeing this memory.
 * @param heap A pointer to the MaxHeap.
 * @return A pointer to the copied string, or NULL if the heap is NULL or memory allocation failed.
 */
char* getHeapid(MaxHeap heap);

/**
 * Returns the current number of elements in the heap.
 * @param heap A pointer to the MaxHeap.
 * @return The current size of the heap, or -1 if the heap pointer is NULL.
 */
int getHeapCurrentSize(MaxHeap heap);

/**
 * Removes and returns the maximum element from the heap.
 * The caller is responsible for freeing the returned element.
 * @param heap A pointer to the MaxHeap.
 * @return A pointer to the maximum element, or NULL if the heap is empty or NULL.
 */
element PopMaxHeap(MaxHeap heap);

/**
 * Returns the maximum element from the heap without removing it.
 * The element is still managed by the heap and should not be freed by the user.
 * @param heap A pointer to the MaxHeap.
 * @return A pointer to the maximum element, or NULL if the heap is empty or NULL.
 */
element TopMaxHeap (MaxHeap heap);

/**
 * Inserts a new element into the MaxHeap.
 * The function creates a deep copy of the element and adds it to the heap,
 * maintaining the Max-Heap rules.
 * @param heap A pointer to the MaxHeap.
 * @param elem The element to be inserted.
 * @return success if inserted, failure_fullcapacity if the heap is full,
 * memory_error if memory allocation for the copy fails, or failure if the input is NULL.
 */
status insertToHeap(MaxHeap heap,element elem);
#endif //ASS_3_MAXHEAP_H