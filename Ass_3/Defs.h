#ifndef ASS_3_DEFS_H
#define ASS_3_DEFS_H

typedef enum e_bool {false, true} bool;

//Defines the possible return status for functions.
//Allows functions to distinguish between logical failures, memory issues, and capacity limits.
typedef enum e_status {success, failure, failure_fullcapacity, memory_error} status;

//Auxiliary type. Represents what stage of the data file the system is currently in.
typedef enum e_flagline {Types_header,type_list,ea,pokemon} flagline;

//Auxiliary type. Represents whether the input we received from the user is valid.
typedef enum e_input {valid,invalid,other} input;

typedef void* element;
typedef element (*copyFunction)(element);
typedef status (*freeFunction)(element);
typedef status (*printFunction)(element);

/* equalFunction: Compares two elements:
 * returns:
 *     1 if first>second
 *     0 if they are equal
 *     -1 if first<second
 */
typedef int (*equalFunction)(element,element);

typedef char* (*getCategoryFunction)(element);

/* getAttackFunction :Calculates the attack of both elements.
* Returns (attackFirst - attackSecond) and stores each attack value in the
given pointers. */
typedef int(*getAttackFunction)(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond);


#endif //ASS_3_DEFS_H