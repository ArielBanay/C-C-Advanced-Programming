#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BattleByCategory.h"
#include "LinkedList.h"
#include "Pokemon.h"

/**
 * A function that receives an array of pointers to Pokémon types and searches for a specific type by its name.
 * @param type_set An array of pointers to Pokémon types
 * @param num_of_types The total number of Pokémon types in the array
 * @param name A string representing the name of the Pokémon type to search for
 * @return Pointer to the matching Pokémon type if found, otherwise NULL
 */
static P_type* find_type_pointer(P_type** type_set, int num_of_types, char* name) {
    //pointer validation
    if (type_set==NULL || name==NULL){return NULL;}

    for (int i=0; i<num_of_types; i++) {
        if (strcmp(type_set[i]->name,name)==0) {
            return type_set[i];
        }
    }
    return NULL;
}

/**
 * A function that receives a buffer containing Pokémon type names separated by commas,
 * creates new Pokémon_type instances for each name, and stores their pointers in the given set.
 * @param pSet_type An array of pointers where the created Pokémon types will be stored
 * @param buffer A comma-separated string of Pokémon type names
 * @param num_of_types The expected number of Pokémon types to create
 * @return success if all types were created, memory_error if any allocation fails,
 * or failure if the input pointers are NULL.
 */
static status create_types_set(P_type** pSet_type, char* buffer, int num_of_types) {
    //pointer validation
    if (pSet_type==NULL || buffer==NULL) {return failure;}

    //create temporrarilly copy of buffer to not destroy the source
    char* temp_buffer = (char*)malloc(strlen(buffer)+1);
    if (!temp_buffer){return memory_error;}
    strcpy(temp_buffer,buffer);

    char* typename=strtok(temp_buffer,",");
    int idx=0;
    //Iteratively traversing while decomposing the BUFFER line,
    //creating new instances of types and placing pointers into the super variable.
    while (typename!=NULL) {
        P_type* temp_ptype = create_pokemon_type(typename);
        if (!temp_ptype) {
            free(temp_buffer);
            return memory_error;
        }
        pSet_type[idx]=temp_ptype;
        idx++;
        typename=strtok(NULL,",");
    }
    free(temp_buffer);
    return success;
}

/**
 * A function that parses a buffer describing interactions between Pokémon types and updates
 * their 'effective against me' or 'effective against others' lists accordingly.
 * @param pSet_type An array of pointers to all existing Pokémon types
 * @param buffer A formatted string describing the type and the list of types to add
 * @param num_of_types The total number of Pokémon types in the set
 * @return success if everything was updated, memory_error if there was no room in
 * the lists, or failure if the input was wrong.
 */
static status add_to_ea_lists(P_type** pSet_type, char* buffer, int num_of_types) {
    //pointer validation
    if (pSet_type==NULL || buffer==NULL) {return failure;}

    //Temporarily placing parts of the buffer in string variables
    buffer += strspn(buffer," \t");
    char* typename = strtok(buffer," ");
    char* ea_mo = strtok(NULL,":");
    char* to_add = strtok(NULL,",");
    status st;
    //Division into cases
    if (strcmp(ea_mo,"effective-against-me")==0) {
        while (to_add!=NULL) {
            st = add_to_ea_me(find_type_pointer(pSet_type,num_of_types,typename),find_type_pointer(pSet_type,num_of_types,to_add));
            if (st==failure){return failure;}
            if (st==memory_error){return memory_error;}
            to_add = strtok(NULL,",");
        }
    } else if (strcmp(ea_mo,"effective-against-other")==0) {
        while (to_add!=NULL) {
            st = add_to_ea_others(find_type_pointer(pSet_type,num_of_types,typename),find_type_pointer(pSet_type,num_of_types,to_add));
            if (st==failure){return failure;}
            if (st==memory_error){return memory_error;}
            to_add = strtok(NULL,",");
        }
    }
    return success;
}

/**
 * Creates a Pokémon based on the data in the received string., and puts it in the battle system.
 * @param b A pointer to the Battle system.
 * @param buffer A string with Pokemon details separated by commas.
 * @param num_of_types The number of different Pokemon types available.
 * @param pSet_type An array of all the Pokemon types.
 * @return success if added, memory_error if creation failed, failure_fullcapacity
 * if the category is full, or failure if the input is wrong.
 */
static status load_poke_to_battle(Battle b,char* buffer, int num_of_types, P_type** pSet_type) {
    if (!b || !buffer) {return failure;}

    char* name = strtok(buffer,",");
    char* species = strtok(NULL,",");
    double height = atof(strtok(NULL,","));
    double weight = atof(strtok(NULL,","));
    int atk = atoi(strtok(NULL,","));
    char* type_name = strtok(NULL,",");

    P_type* ptype = find_type_pointer(pSet_type,num_of_types,type_name);
    if (ptype==NULL) {return failure;}

    Poke* pPoke = create_pokemon(ptype,name,species,height,weight,atk);
    if (pPoke==NULL) {return memory_error;}

    status insert_st = insertObject(b,pPoke);
    free_pokemon(pPoke);
    return insert_st;
}

/**
 * Creates a new Pokemon based on interactive user input from the terminal.
 * The function prompts the user for name, species, height, weight, and attack power,
 * then uses these values to initialize a new Pokemon instance.
 * @param ptype A pointer to the Pokemon's type (P_type).
 * @return A pointer to the newly created Pokemon (Poke*), or NULL if memory
 * allocation fails or input is invalid.
 */
static Poke* user_create_poke(P_type* ptype) {
    //input validation
    if (!ptype){return NULL;}
    char buffer[300];
    char name[300];
    char species[300];
    double h;
    double w;
    int a;

    printf("Please enter Pokemon name:\n");
    fgets(name,sizeof(name),stdin);
    name[strcspn(name,"\r\n")]='\0';

    printf("Please enter Pokemon species:\n");
    fgets(species,sizeof(species),stdin);
    species[strcspn(species,"\r\n")]='\0';

    printf("Please enter Pokemon height:\n");
    fgets(buffer,sizeof(buffer),stdin);
    h = atof(buffer);

    printf("Please enter Pokemon weight:\n");
    fgets(buffer,sizeof(buffer),stdin);
    w = atof(buffer);

    printf("Please enter Pokemon attack:\n");
    fgets(buffer,sizeof(buffer),stdin);
    a = atoi(buffer);

    Poke* new_pokemon = create_pokemon(ptype,name,species,h,w,a);
    if (new_pokemon==NULL) {return NULL;}
    return new_pokemon;
}

/**
 * Removes and frees the strongest Pokemon from a specific category according to the user input.
 * @param b A pointer to the Battle system.
 * @param type_set The array of all existing Pokemon types.
 * @param num_of_types The total number of available types.
 */
static void remove_strongest_poke(Battle b, P_type** type_set, int num_of_types) {
    if (!type_set || num_of_types<0) {return;}

    //get type name from user
    printf("Please enter type name:\n");
    char buffer[300];
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\r\n")]='\0';

    //search the desired type
    P_type* ptype = find_type_pointer(type_set,num_of_types,buffer);
    if (ptype==NULL) {
        printf("Type name doesn't exist.\n");
        return;
    }
    Poke* strongest = removeMaxByCategory(b,ptype->name);
    if (!strongest) {
        printf("There is no Pokemon to remove.\n");
        return;
    }
    printf("The strongest Pokemon was removed:\n");
    print_pokemon(strongest);
    free_pokemon(strongest);
}

/**
 * Memory deallocation function
 * @param ptr A pointer to an array that holds pointers to all instances of the Pokémon types existing in the system.
 * @param num_of_types The number of Pokémon types available in the system
 */
static void big_free_types(P_type** ptr,int num_of_types) {
    //Iterative transition and release of all existing 'Pokémon types' in the system
    for (int i=0; i<num_of_types; i++) {
        free_type(ptr[i]);
    }
}

/**
 * A function that prints all Pokémon types by iterating over the provided array
 * and invoking the designated print function for each existing type.
 * @param pSet_type An array of pointers to Pokémon types
 * @param num_of_types The total number of Pokémon types in the array
 * @return Operation status indicating whether all types were printed successfully
 */
static status print_all_types(P_type** pSet_type,int num_of_types) {
    //pointer validation
    if (pSet_type==NULL) {return failure;}

    //print each Pokemon type
    for (int i=0; i<num_of_types; i++) {
        if (pSet_type[i]==NULL) {return failure;}
        print_type(pSet_type[i]);
    }
    return success;
}

/**
 * Handles the logic for a user-initiated battle between a new Pokemon against the system.
 * It asks the user for a type, creates a new Pokemon based on input, and starts
 * a battle against the strongest available opponent in the system.
 * @param b A pointer to the Battle system.
 * @param type_set The array of all existing Pokemon types.
 * @param num_of_types The total number of available types.
 * @return success if the battle finished, memory_error if creating the Pokemon failed,
 * or failure if the type does not exist or input is invalid.
 */
static status big_fight(Battle b, P_type** type_set, int num_of_types) {
    //input validation
    if (!type_set || num_of_types<0) {return failure;}

    //get type name from user
    printf("Please enter Pokemon type name:\n");
    char buffer[300];
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\r\n")]='\0';

    //search the desired type
    P_type* ptype = find_type_pointer(type_set,num_of_types,buffer);
    if (ptype==NULL) {
        printf("Type name doesn't exist.\n");
        return failure;
    }

    Poke* pNewpoke = user_create_poke(ptype);
    if (pNewpoke==NULL) {return memory_error;}

    printf("You choose to fight with:\n");
    print_pokemon(pNewpoke);

    //call to fight func
    element result = fight(b,pNewpoke);
    if (result== (element)-1) {
        printf("There are no Pokemons to fight against you.\n");
    }

    //deallocate memory for pNewpoke
    free_pokemon(pNewpoke);
    return success;
}

/**
 * Gets Pokemon details from the user and adds the new Pokemon to the battle system.
 * The function checks if there is enough space, then creates
 * the Pokemon and inserts it into the correct category heap.
 * @param b A pointer to the Battle system.
 * @param type_set The array of all existing Pokemon types.
 * @param num_of_types The total number of types in the system.
 * @param max_capacity The maximum number of Pokemons allowed per category.
 * @return success if the Pokemon was added, memory_error if creation failed,
 * failure_fullcapacity if the category is full, or failure for invalid input.
 */
static status insert_pokemon_to_battle(Battle b, P_type** type_set, int num_of_types, int max_capacity) {
    //input validation
    if (!b || !type_set || num_of_types<0) {return failure;}

    //get type name from user
    printf("Please enter Pokemon type name:\n");
    char buffer[300];
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\r\n")]='\0';

    //search the desired type
    P_type* ptype = find_type_pointer(type_set,num_of_types,buffer);
    if (ptype==NULL) {
        printf("Type name doesn't exist.\n");
        return failure;
    }
    //check if there is enough place to insert more pokemons of this type.
    if (getNumberOfObjectsInCategory(b,ptype->name)>=max_capacity) {
        printf("Type at full capacity.\n");
        return failure_fullcapacity;
    }

    Poke* pNew_Poke = user_create_poke(ptype);
    if (pNew_Poke==NULL) {return memory_error;}

    if (insertObject(b,pNew_Poke)==success) {
        printf("The Pokemon was successfully added.\n");
        print_pokemon(pNew_Poke);
    }
    //free of New_Poke because the fact that insert create a copy of him.
    free_pokemon(pNew_Poke);
    return success;
}

/**
 * Auxiliary function for self use only.
 * A wrapper for print_pokemon to match the generic printFunction signature.
 * @param elem The generic element (Poke) to be printed.
 * @return success if printed, or failure if the input is NULL or the print fails.
 */
static status print_pokemon_Wrap(element elem) {
    //input validation
    if (!elem) {return failure;}

    return print_pokemon((Poke*)elem);
}

/**
 * Auxiliary function for self use only.
 * A wrapper for free_pokemon to match the generic freeFunction signature.
 * @param elem The generic element (Poke) to be freed.
 * @return success if the memory was freed, or failure if the input is NULL.
 */
static status free_pokemonWrap(element elem) {
    if (!elem) {return failure;}
    return free_pokemon((Poke*)elem);
}

/**
 * Compares two Pokemons based on their attack power.
 * @param elem1 The first generic element (Poke) to compare.
 * @param elem2 The second generic element (Poke) to compare.
 * @return 1 if the first Pokemon is stronger, -1 if the second is stronger,
 * 0 if they are equal, or 2 if an input is NULL.
 */
static int equal_pokemons(element elem1,element elem2){
    //input validation
    if (!elem1 || !elem2) {return 2;}
    Poke* poke1 = (Poke*)elem1;
    Poke* poke2 = (Poke*)elem2;

    if (poke1->bio_info->atk>poke2->bio_info->atk){return 1;}
    if (poke1->bio_info->atk<poke2->bio_info->atk){return -1;}
    return 0;
}

/**
 * Creates a deep copy of a Pokemon.
 * This function uses the specific attributes of the source Pokemon to create
 * a new instance, ensuring the data is duplicated in memory.
 * @param elem The generic element (Poke) to be copied.
 * @return A pointer to the new copy (element), or NULL if the input is invalid
 * or memory allocation fails.
 */
static element copy_pokemon(element elem) {
    //input validation
    if (!elem) {return NULL;}

    //casting
    Poke* source=(Poke*)elem;

    //create new pokemon
    Poke* copy = create_pokemon(source->type,source->pokename,source->species,source->bio_info->height,source->bio_info->weight,source->bio_info->atk);
    //Checks whether the creation was successful
    if (copy==NULL) {return NULL;}
    return (element)copy;
}

/**
 * This function extracts the type name from the Pokemon structure to identify
 * which category it belongs to.
 * @param elem The generic element (Poke) to get the category from.
 * @return A string containing the category name, or NULL if the input is invalid.
 */
static char* getcategory(element elem) {
    if (!elem) {return NULL;}
    return ((Poke*)elem)->type->name;
}

/**
 * Calculates the modified attack values for two Pokemons during a fight.
 * This function checks the type advantages and disadvantages of both Pokemons,
 * updates their attack scores accordingly through pointers, and returns the difference.
 * @param elem1 The first Pokemon (element).
 * @param elem2 The second Pokemon (element).
 * @param atk1 Pointer to store the final attack value of the first Pokemon.
 * @param atk2 Pointer to store the final attack value of the second Pokemon.
 * @return The difference between the first and second Pokemon's modified attack scores.
 */
static int getAttack(element elem1,element elem2, int* atk1,int* atk2){
    //I did the input validation out of this func before i called her in "fight" function at BattleByCategory.c file
    int temp1=0,temp2=0;
    Poke* poke1 = (Poke*)elem1;
    Poke* poke2 = (Poke*)elem2;

    //4 iterations to figure out if there is need to minus atk of one of them.
    for (int i=0; i<poke1->type->num_ea_me; i++) {
        if (poke1->type->ea_me[i] == poke2->type) {
            temp1 -= 10;
        }
    }
    for (int i=0; i<poke1->type->num_ea_others; i++) {
        if (poke1->type->ea_others[i] == poke2->type) {
            temp2 -= 10;
        }
    }
    for (int i=0; i<poke2->type->num_ea_me; i++) {
        if (poke2->type->ea_me[i] == poke1->type) {
            temp2 -= 10;
        }
    }
    for (int i=0; i<poke2->type->num_ea_others; i++) {
        if (poke2->type->ea_others[i] == poke1->type) {
            temp1 -= 10;
        }
    }

    //take care about double minus cases
    if (temp1 == -20){temp1 = -10;}
    if (temp2 == -20){temp2 = -10;}

    //calculate the update atk value
    int temp_atk1 = temp1 + poke1->bio_info->atk;
    int temp_atk2 = temp2 + poke2->bio_info->atk;

    //take care about that attack not goone be a negative number.
    if (temp_atk1<0) { temp_atk1 = 0;}
    if (temp_atk2<0) { temp_atk2 = 0;}


    *atk1 = temp_atk1;
    *atk2 = temp_atk2;

    return temp_atk1-temp_atk2;
}

/**
 * The main entry point of the Pokemon Battle System.
 * This function manages the entire program: it takes the arguments from the cmd,
 * initializing the Pokemon type system, loading data from a configuration file into
 * the Battle ADT, and running an interactive menu for the user. It ensures proper
 * error handling for memory allocations and file operations.
 * In addition, guarantees that all dynamic memory is freed before the program exits.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments (num_of_types, max_in_type, file_path).
 * @return 0 on successful execution and clean exit, or 1 if an error (memory or file) occurs.
 */
int main (int argc, char* argv[]) {

    //Saving the parameters obtained when running the file in variables
    int num_of_types=atoi(argv[1]);
    int max_in_type=atoi(argv[2]);
    char* file=argv[3];

    //Opening the file + Initializing a buffer to read the lines + Initializing an appropriate auxiliary flag for easier reading of the file.
    FILE* pfile = fopen(file,"r");

    //Check that the file was opened successfully
    if (pfile==NULL) {
        return 1;
    }

    char buffer[300];
    bool memory_problem=false;
    bool any_failure=false;
    status st;
    flagline fline=Types_header;

    P_type** pSet_type=(P_type**)malloc(num_of_types * sizeof(P_type *));
    if (pSet_type==NULL) {
        fclose(pfile);
        printf("No memory available.\n");
        return 1;
    }

    //Auxiliary rows to get the row that contains all the tapes to create the structure that contains all the Pokémon
    char* firstline=fgets(buffer,sizeof(buffer),pfile);
    if (firstline==NULL) {
        free(pSet_type);
        fclose(pfile);
        return 1;
    }
    char* types_list=fgets(buffer,sizeof(buffer),pfile);
    if (types_list==NULL) {
        free(pSet_type);
        fclose(pfile);
        return 1;
    }

    //Replaces the last character with \0 so that we can read each line as a 'regular' string for create battle.
    types_list[strcspn(types_list,"\r\n")]='\0';

    //Creating a structure for storing Pokémon
    Battle poke_battle = createBattleByCategory(max_in_type,num_of_types,types_list,equal_pokemons,copy_pokemon,free_pokemonWrap,getcategory,getAttack,print_pokemon_Wrap);
    if (poke_battle==NULL)
    {
        free(pSet_type);
        fclose(pfile);
        printf("No memory available.\n");
        return 1;
    }

    //reset the file position 'idx' to the beginning of the file, so the next read operation will start from the first line.
    rewind(pfile);

    //Reading each line separately from the file and saving the information according to the relevant content.
    while (fgets(buffer,sizeof(buffer),pfile)!=NULL) {
        if (memory_problem==true || any_failure==true){break;}
        //Replaces the last character with \0 so that we can read each line as a 'regular' string
        buffer[strcspn(buffer,"\r\n")]='\0';
        switch (fline) {

            case Types_header:
                //Skips the TYPES header in the data file
                fline=type_list;
                break;

            case type_list:
                //Calling a function that creates a new instance of 'Pokémon Type' while checking whether the creation was successful or not.
                st = create_types_set(pSet_type,buffer,num_of_types);
                if (st==failure){any_failure=true;}
                if (st==memory_error){memory_problem=true;}
                fline=ea;
                break;

            case ea:
                //Checking whether we need to move on to the next stage of creating the Pokémon instances themselves.
                if (strcmp(buffer,"Pokemons")==0) {
                    fline=pokemon;
                    break;
                }
                //A call to a function that takes care of adding certain types to the corresponding lists of other types.
                st = add_to_ea_lists(pSet_type,buffer,num_of_types);
                if (st==failure){any_failure=true;}
                if (st==memory_error){memory_problem=true;}
                break;

            case pokemon:
                //Creating an instance of a new Pokémon based on the data in the file and adding the pointer that points to it to the appropriate array in the heap.
                st = load_poke_to_battle(poke_battle,buffer,num_of_types,pSet_type);
                if (st==failure){any_failure=true;}
                if (st==memory_error){memory_problem=true;}
        }
    }

    //string represent the menu
    char* menu2print = "Please choose one of the following numbers:\n1 : Print all Pokemons by types\n2 : Print all Pokemons types\n3 : Insert Pokemon to battles training camp\n4 : Remove strongest Pokemon by type\n5 : Fight\n6 : Exit\n";

    //flag sign Exit case chosen
    bool exit=false;

    //Infinite loop for the main menu until we receive an exit command
    while (exit==false && memory_problem==false && any_failure==false) {
        input input_case = other;

        //Printing the menu for the user and checking the correctness of the input.
        printf("%s",menu2print);

        //Receiving input from the user
        fgets(buffer,sizeof(buffer),stdin);

        //Replaces the last character with \0 so that we can read each line as a 'regular' string
        buffer[strcspn(buffer,"\r\n")]='\0';

        //Input test
        if (strlen(buffer)!=1) {
            input_case = invalid;
        } else if (buffer[0]>'6'||buffer[0]<'1') {
            input_case = invalid;
        } else {input_case = valid;}

        //Invalid input case
        if (input_case==invalid) {
            printf("Please choose a valid number.\n");
            continue;
        }
        //Classification into cases according to user request from input
        int case_id=atoi(buffer);
        switch (case_id) {
            case 1:
                displayObjectsByCategories(poke_battle);
                break;
            case 2:
                print_all_types(pSet_type,num_of_types);
                break;
            case 3:
                st = insert_pokemon_to_battle(poke_battle,pSet_type,num_of_types,max_in_type);
                if (st==memory_error){memory_problem=true;}
                break;
            case 4:
                remove_strongest_poke(poke_battle,pSet_type,num_of_types);
                break;
            case 5:
                st = big_fight(poke_battle,pSet_type,num_of_types);
                if (st==memory_error){memory_problem=true;}
                break;
            case 6:
                exit=true;
                break;
        }
    }

    //Freeing memory allocations from the inside out according to the principle
    if (destroyBattleByCategory(poke_battle)==failure) {
        any_failure=true;
    }
    big_free_types(pSet_type,num_of_types);
    free(pSet_type);

    //Closing the data file
    fclose(pfile);

    //Exiting the program in case of a memory problem
    if (memory_problem==true) {
        printf("No memory available\n");
        return 1;
    }

    //Exit the program if there was a failure during system creation while reading data from the file.
    if (any_failure==true) {
        return 1;
    }

    //Exiting the program in a normal case
    printf("All the memory cleaned and the program is safely closed.\n");
    return 0;
}