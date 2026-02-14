#ifndef ASS_3_LINKEDLIST_H
#define ASS_3_LINKEDLIST_H

#include "Defs.h"

//Pointer alias for the generic ADT Linked List
typedef struct LinkedList_T* LinkedList;

/**
 * Creates and initializes a new generic LinkedList.
 * This function allocates memory for the structure and sets up the
 * function pointers.
 * @param copyFunc Function to perform deep copy of elements.
 * @param freeFunc Function to deallocate elements.
 * @param printFunc Function to print elements.
 * @param eqlFunc Function to compare an element against a key.
 * @param cmpFunc Function to compare two elements.
 * @return A pointer to the new LinkedList, or NULL if any input is NULL or allocation failed.
 */
LinkedList createLinkedList(copyFunction copyFunc, freeFunction freeFunc, printFunction printFunc, equalFunction eqlFunc, equalFunction cmpFunc);

/**
 * Destroys a linked list and deallocates all associated memory.
 * The function iterates through the list, invoking the specific free function
 * for each element's data, freeing each node, and finally freeing the list structure itself.
 * @param l_list A pointer to the LinkedList to be destroyed.
 * @return status success if the list and all its elements were successfully deallocated,
 * or failure if the list pointer is NULL or an element's free function fails.
 */
status destroyLinkedList(LinkedList l_list);

/**
 * Adds a new element to the end of the linked list.
 * This function creates a new node, performs a deep copy of the provided element
 * and updates the list's head and tail pointers
 * @param l_list A pointer to the LinkedList where the element will be added.
 * @param elem The element to be copied and appended to the list.
 * @return status success if the element was successfully added, memory_error if
 * memory allocation for the new node fails, or failure if the list or element
 * pointers are NULL.
 */
status appendNode(LinkedList l_list, element elem);

/**
 * Removes a specific element from the doubly linked list if it exists.
 * The function searches for a node containing an element equal to the provided one
 * using the list's equality function. If found, it unlinks the node and deallocates the element's data and the node itself.
 * @param l_list A pointer to the LinkedList from which the element will be deleted.
 * @param elem The element to be searched for and removed.
 * @return status success if the element was found and deleted, or failure if the
 * list or element pointers are NULL or if the element was not found in the list.
 */
status deleteNode(LinkedList l_list, element elem);

/**
 * Iterates through the linked list and prints each element.
 * The function traverses the list from head to tail, invoking the specific
 * print function associated with the list for each node's element.
 * @param l_list A pointer to the LinkedList to be printed.
 * @return status success if the entire list was traversed and printed successfully,
 * or failure if the list pointer is NULL or if any element's print function fails.
 */
status printLinkedList(LinkedList l_list);

/**
 * Searches for an element within the linked list based on a provided key.
 * The function traverses the list and uses the list's equality function to compare
 * each node's element with the search key. If a match is found the pointer to the stored element is returned.
 * @param l_list A pointer to the LinkedList to search in.
 * @param key The element or key used for comparison.
 * @return A pointer to the matching element within the list if found,
 * or NULL if the element does not exist or if the input pointers are invalid.
 */
element searchByKeyInList(LinkedList l_list, element key);
#endif //ASS_3_LINKEDLIST_H