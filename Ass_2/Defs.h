//
// Created by admin on 11/20/2025.
//

#ifndef ASS_2_DEFS_H
#define ASS_2_DEFS_H

typedef enum e_bool {false, true} bool;

//Auxiliary type. Represents the operation status of a function. Success or failure.
typedef enum e_status {success, failure} status;
//Auxiliary type. Represents what stage of the data file the system is currently in.
typedef enum e_flagline {Types_header,type_list,ea,pokemon} flagline;
//Auxiliary type. Represents whether the input we received from the user is valid.
typedef enum e_input {valid,invalid,other} input;
//Auxiliary type. Used as a flag to indicate whether a particular input that the system received
//from the user is in the system or in one of the lists.
typedef enum e_exist {not_exist, exist0, exist1} exist;

#endif //ASS_2_DEFS_H