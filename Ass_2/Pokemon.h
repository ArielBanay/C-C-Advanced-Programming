// Created by admin on 11/20/2025.
#ifndef ASS_2_POKEMON_H
#define ASS_2_POKEMON_H
#include "Defs.h"

// This file contain all the structs and functions declerations.

/**
 * Pokemon_Type struct represent type of pokemon.
  This structure represents a Pokemon_type.
  The structure has 6 fields.
  1. Name - a pointer to a string
  2. How many Pokemon of this type exist in the system
  3. How many types effective against me exist in the system
  4. How many types I am effective against exist in the system
  5+6. Pointers to arrays containing pointers to those types from sections 4+3 respectively.
 */
typedef struct Pokemon_Type {
  char* name;
  int cnt_type;
  int num_ea_me;
  int num_ea_others;
  struct Pokemon_Type** ea_me;
  struct Pokemon_Type** ea_others;
} P_type;

/**
 *This structure represents biological information about the Pokémon.
 *Contains the fields height and weight in decimal numbers + attack power as an integer.
 */
typedef struct Biology_Information {
  double height;
  double weight;
  int atk;
} B_info;

/**
*This structure represents an instance of a specific Pokémon.
* Fields:
1. name - pointer to a string
2. species - pointer to a string
3. pointer to an instance of biological information
4. pointer to an instance of a Pokémon type
 */
typedef struct Pokemon{
  char* pokename;
  char* species;
  B_info* bio_info;
  P_type* type;
} Poke;

//List of all function signatures present in the pokemon.c file.
/**
 * This function takes the name of a Pokémon type and creates a new instance of a 'Pokémon Type' object.
 * The function initializes all of its fields with predefined default values.
 * @param name Pointer to a string of characters representing the type name
 * @return Pointing to the 'Pokémon Type' instance she just created.
 */
P_type* create_pokemon_type(char* name);

/**
 * This function is called by the function to create an instance of a Pokémon. This function creates an instance of an object
 * of type 'Biological Information' in the heap and returns a pointer to this instance.
 * @param h float represents the height of the Pokemon
 * @param w float represents the weight of the Pokemon
 * @param a int represent the attack power of the pokemon
 * @return Pointer to an instance of 'biological information'
 */
B_info* create_biology_information(double h, double w, int a);

/**
 * The function receives values and creates a new instance of a Pokémon in the heap and returns a pointer to it.
 * @param pP_type pointer to pokemon type struct
 * @param pname pointer to string represent the name of the pokemon
 * @param pspecies pointer to string represent the speciess of the pokemon
 * @param h float represents the height of the Pokemon
 * @param w float represents the weight of the Pokemon
 * @param a int represent the attack power of the pokemon
 * @return The returned value is a pointer to an object of type Pokémon.
 */
Poke* create_pokemon(P_type* pP_type, char* pname, char* pspecies, double h, double w, int a);

/**
 * Function adds a Pokémon type (B) to the list that they effective against me(A)
 * @param pP_typea pointer to a Pokemon_type
 * @param pP_typeb pointer to a Pokemon_type
 * @return Operation status. Was the add successful or not.
 */
status add_to_ea_me(P_type* pP_typea, P_type* pP_typeb);

/**
 * Function adds a Pokémon type (B) to the list that I (A) am effective against
 * @param pP_typea pointer to a Pokemon_type
 * @param pP_typeb pointer to a Pokemon_type
 * @return Operation status. Was the add successful or not.
 */
status add_to_ea_others(P_type* pP_typea, P_type* pP_typeb);

/**
 * A function that receives a pointer to a Pokemon_type(A) and removes another Pokemon_type(B) from the list of effective against A.
 * @param pP_typea pointer to a Pokemon_type
 * @param name_typeb Name of a Pokémon type that should be removed from the list
 * @return Operation status. Was the removal successful or not.
 */
status remove_from_ea_me(P_type* pP_typea, char* name_typeb);

/**
 * A function that receives a pointer to a Pokemon_type(A) and removes another Pokemon_type(B) from the list that A effective against them.
 * @param pP_typea pointer to a Pokemon_type
 * @param name_typeb Name of a Pokémon type that should be removed from the list
 * @return Operation status. Was the removal successful or not.
 */
status remove_from_ea_others(P_type* pP_typea, char* name_typeb);

/**
 * Print function. Takes a pointer to an instance of pokemon and prints it according to a specific format.
 * @param pPoke pointer to an instance of pokemon that needs to be printed
 * @return a status indicating whether the print was successful or not.
 */
status print_pokemon(Poke* pPoke);

/**
 * Print function. Takes a pointer to an instance of type_pokemon and prints it according to a specific format.
 * @param pP_type pointer to an instance of type_pokemon that needs to be printed
 * @return a status indicating whether the print was successful or not.
 */
status print_type(P_type* pP_type);

/**
 * Memory release function.
 * Receives a pointer to a Pokemon and releases the memory allocated to all its fields, including the memory allocated for it.
 * @param pPoke Points to the Pokémon that should be released.
 */
void free_pokemon(Poke* pPoke);

/**
 * Memory release function.
 * Receives a pointer to a Pokemon_type and releases the memory allocated to all its fields, including the memory allocated for it.
 * @param pP_type Points to the type of Pokémon that should be released.
 */
void free_type(P_type* pP_type);

#endif //ASS_2_POKEMON_H