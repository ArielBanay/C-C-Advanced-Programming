// Created by admin on 11/21/2025.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"

/**
 * A function that receives an array of pointers to Pokémon types and searches for a specific type by its name.
 * @param type_set An array of pointers to Pokémon types
 * @param num_of_types The total number of Pokémon types in the array
 * @param name A string representing the name of the Pokémon type to search for
 * @return Pointer to the matching Pokémon type if found, otherwise NULL
 */
P_type* find_type_pointer(P_type** type_set, int num_of_types, char* name) {
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
 * @return Operation status indicating whether the creation was successful
 */
status create_types_set(P_type** pSet_type, char* buffer, int num_of_types) {
    //pointer validation
    if (pSet_type==NULL || buffer==NULL) {return failure;}

    char* typename=strtok(buffer,",");
    int idx=0;
    //Iteratively traversing while decomposing the BUFFER line,
    //creating new instances of types and placing pointers into the super variable.
    while (typename!=NULL) {
        pSet_type[idx]=create_pokemon_type(typename);
        idx++;
        typename=strtok(NULL,",");
    }
    return success;
}

/**
 * A function that parses a buffer describing interactions between Pokémon types and updates
 * their 'effective against me' or 'effective against others' lists accordingly.
 * @param pSet_type An array of pointers to all existing Pokémon types
 * @param buffer A formatted string describing the type and the list of types to add
 * @param num_of_types The total number of Pokémon types in the set
 * @return Operation status indicating whether the update of the lists was successful
 */
status add_to_ea_lists(P_type** pSet_type, char* buffer, int num_of_types) {
    //pointer validation
    if (pSet_type==NULL || buffer==NULL) {return failure;}

    //Temporarily placing parts of the buffer in string variables
    buffer += strspn(buffer," \t");
    char* typename = strtok(buffer," ");
    char* ea_mo = strtok(NULL,":");
    char* to_add = strtok(NULL,",");

    //Division into cases
    if (strcmp(ea_mo,"effective-against-me")==0) {
        while (to_add!=NULL) {
            if (add_to_ea_me(find_type_pointer(pSet_type,num_of_types,typename),find_type_pointer(pSet_type,num_of_types,to_add))==failure){return failure;}
            to_add = strtok(NULL,",");
        }
    } else if (strcmp(ea_mo,"effective-against-other")==0) {
        while (to_add!=NULL) {
            if (add_to_ea_others(find_type_pointer(pSet_type,num_of_types,typename),find_type_pointer(pSet_type,num_of_types,to_add))==failure){return failure;}
            to_add = strtok(NULL,",");
        }
    }
    return success;
}

/**
 * A function that parses a buffer containing Pokémon data, creates a new Pokémon instance,
 * and stores its pointer in the global Pokémon set at the next available index.
 * @param pPoke_set An array of pointers to all created Pokémon instances
 * @param buffer A comma-separated string containing the Pokémon's attributes
 * @param pSet_type An array of pointers to all Pokémon types in the system
 * @param num_of_types The total number of available Pokémon types
 * @return Operation status indicating whether the Pokémon was successfully created and added
 */
status add_pokemon_struct(Poke** pPoke_set, char* buffer,P_type** pSet_type,int num_of_types) {
    //pointer validation
    if (pPoke_set==NULL || buffer==NULL || pSet_type==NULL) {return failure;}

    //An auxiliary variable represents the index in an array that contains the pointers to all Pokémon.
    static int idx = 0;

    //Breaking down the data about Pokémon
    char* name = strtok(buffer,",");
    char* species = strtok(NULL,",");
    double height = atof(strtok(NULL,","));
    double weight = atof(strtok(NULL,","));
    int atk = atoi(strtok(NULL,","));
    char* type = strtok(NULL,",");

    //ptype will hold the pointer to the Pokemon's 'type'
    P_type* ptype=find_type_pointer(pSet_type,num_of_types,type);

    //Creating a new instance of a Pokemon and holding the pointer to it in the Poke_set array at the appropriate index.
    pPoke_set[idx]=create_pokemon(ptype,name,species,height,weight,atk);
    idx++;
    return success;
}

/**
 * A function that prints all Pokémon stored in the Pokémon set by iterating over the array
 * and invoking the print function for each existing Pokémon.
 * @param pPoke_set An array of pointers to Pokémon instances
 * @param num_of_pokemons The total number of Pokémon stored in the array
 * @return Operation status indicating whether the printing process was successful
 */
status print_all_pokemons(Poke** pPoke_set,int num_of_pokemons) {
    //Receiving input from the user + editing it
    if (pPoke_set==NULL) {return failure;}

    //print each Pokemon
    for (int i=0; i<num_of_pokemons; i++) {
        if (pPoke_set[i]==NULL){return failure;}
        print_pokemon(pPoke_set[i]);
    }
    return  success;
}

/**
 * A function that prints all Pokémon types by iterating over the provided array
 * and invoking the designated print function for each existing type.
 * @param pSet_type An array of pointers to Pokémon types
 * @param num_of_types The total number of Pokémon types in the array
 * @return Operation status indicating whether all types were printed successfully
 */
status print_all_types(P_type** pSet_type,int num_of_types) {
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
 * A function that receives user input to add a Pokémon type to another type's
 * 'effective against me' list, performs validations, and updates the list if possible.
 * @param pSet_type An array of pointers to all Pokémon types in the system
 * @param num_of_types The total number of Pokémon types available
 * @return Operation status indicating whether the update was successful
 */
status add_type_ea_ma(P_type** pSet_type, int num_of_types) {
    //pointer validation
    if (pSet_type==NULL){return failure;}

    //Receiving input from the user + editing it
    char buffer[300];
    bool to_do=true;
    printf("Please enter type name:\n");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\r\n")]='\0';
    //Finding the required pointer so that we can access the relevant instance.
    P_type* source_type_me_add=find_type_pointer(pSet_type,num_of_types,buffer);

    if (source_type_me_add!=NULL){
        //Receiving input from the user + editing it
        printf("Please enter type name to add to %s effective against me list:\n",source_type_me_add->name);
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer,"\r\n")]='\0';
        //Finding the required pointer so that we can access the relevant instance.
        P_type* target_type=find_type_pointer(pSet_type,num_of_types,buffer);
        if (target_type!=NULL) {
            //Checking whether the target 'type' is already in the requested list
            for (int i=0; i<source_type_me_add->num_ea_me; i++) {
                if (source_type_me_add->ea_me[i]==target_type) {
                    to_do=false;
                    //The type already exists. A message is printed and exits to receive new input from the user in the main menu.
                    printf("This type already exist in the list.\n");
                    break;
                }
            }
            //The new type does not yet exist in the current list, so we will add it.
            if (to_do==true) {
                if (add_to_ea_me(source_type_me_add,target_type)==failure){return failure;}
                print_type(source_type_me_add);
            }
        }
        // the target type doesn't exist in the system.
        else {printf("Type name doesn't exist.\n");}

    }
    // the source type doesn't exist in the system.
    else {printf("Type name doesn't exist.\n");}
    return success;
}

/**
 * A function that receives user input to add a Pokémon type to another type's
 * 'effective against others' list, performs validations, and updates the list if needed.
 * @param pSet_type An array of pointers to all Pokémon types in the system
 * @param num_of_types The total number of Pokémon types available
 * @return Operation status indicating whether the update was successfully completed
 */
status add_type_ea_others(P_type** pSet_type, int num_of_types) {
    //pointer validation
    if (pSet_type==NULL) {return failure;}
    //Receiving input from the user + editing it
    char buffer[300];
    bool to_do=true;
    printf("Please enter type name:\n");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\r\n")]='\0';
    //Finding the required pointer so that we can access the relevant instance.
    P_type* source_type_others_add=find_type_pointer(pSet_type,num_of_types,buffer);

    if (source_type_others_add!=NULL) {
        //Receiving input from the user + editing it
        printf("Please enter type name to add to %s effective against others list:\n",source_type_others_add->name);
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer,"\r\n")]='\0';
        //Finding the required pointer so that we can access the relevant instance.
        P_type* target_type=find_type_pointer(pSet_type,num_of_types,buffer);
        if (target_type!=NULL) {
            //Checking whether the target 'type' is already in the requested list
            for (int i=0; i<source_type_others_add->num_ea_others; i++) {
                if (source_type_others_add->ea_others[i]==target_type) {
                    to_do=false;
                    //The type already exists. A message is printed and exits to receive new input from the user in the main menu.
                    printf("This type already exist in the list.\n");
                    break;
                }
            }
            if (to_do==true) {
                //The new type does not yet exist in the current list, so we will add it.
                if (add_to_ea_others(source_type_others_add,target_type)==failure){return failure;}
                print_type(source_type_others_add);
            }
        }
        // the target type doesn't exist in the system.
        else {printf("Type name doesn't exist.\n");}

    }
    // the source type doesn't exist in the system.
    else {printf("Type name doesn't exist.\n");}
    return success;
}

/**
 * A function that receives user input to remove a Pokémon type from another type's
 * 'effective against me' list, performs validations, and updates the list accordingly.
 * @param pSet_type An array of pointers to all Pokémon types in the system
 * @param num_of_types The total number of Pokémon types available
 * @return Operation status indicating whether the removal was successfully completed
 */
status remove_type_ea_me(P_type** pSet_type, int num_of_types) {
    //pointer validation
    if (pSet_type==NULL){return failure;}
    //Receiving input from the user + editing it
    char buffer[300];
    bool exist=false;
    printf("Please enter type name:\n");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\r\n")]='\0';
    //Finding the required pointer so that we can access the relevant instance.
    P_type* source_type_me_remove=find_type_pointer(pSet_type,num_of_types,buffer);

    if (source_type_me_remove!=NULL) {
        //Receiving input from the user + editing it
        printf("Please enter type name to remove from %s effective against me list:\n",source_type_me_remove->name);
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer,"\r\n")]='\0';
        //Finding the required pointer so that we can access the relevant instance.
        P_type* target_type=find_type_pointer(pSet_type,num_of_types,buffer);
        if (target_type!=NULL) {
            //Checking whether the target 'type' is in the requested list
            for (int i=0; i<source_type_me_remove->num_ea_me; i++) {
                if (source_type_me_remove->ea_me[i]==target_type) {
                    exist=true;
                    if (remove_from_ea_me(source_type_me_remove,target_type->name)==failure){return failure;}
                    print_type(source_type_me_remove);
                    break;
                }
            }
            if (exist==false) {
                printf("Type name doesn't exist in the list.\n");
            }
        }
        // the target type doesn't exist in the system.
        else {printf("Type name doesn't exist in the list.\n");}

    }
    // the source type doesn't exist in the system.
    else {printf("Type name doesn't exist.\n");}
    return success;
}

/**
 * A function that receives user input to remove a Pokémon type from another type's
 * 'effective against others' list, performs validations, and updates the list accordingly.
 * @param pSet_type An array of pointers to all Pokémon types in the system
 * @param num_of_types The total number of Pokémon types available
 * @return Operation status indicating whether the removal was successfully completed
 */
status remove_type_ea_others(P_type** pSet_type, int num_of_types) {
    //pointer validation
    if (pSet_type==NULL) {return failure;}

    //Receiving input from the user + editing it
    char buffer[300];
    bool exist=false;
    printf("Please enter type name:\n");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\r\n")]='\0';
    //Finding the required pointer so that we can access the relevant instance.
    P_type* source_type_others_remove=find_type_pointer(pSet_type,num_of_types,buffer);

    if (source_type_others_remove!=NULL) {
        //Receiving input from the user + editing it
        printf("Please enter type name to remove from %s effective against others list:\n",source_type_others_remove->name);
        fgets(buffer,sizeof(buffer),stdin);
        buffer[strcspn(buffer,"\r\n")]='\0';
        //Finding the required pointer so that we can access the relevant instance.
        P_type* target_type=find_type_pointer(pSet_type,num_of_types,buffer);
        if (target_type!=NULL) {
            //Checking whether the target 'type' is in the requested list
            for (int i=0; i<source_type_others_remove->num_ea_others; i++) {
                if (source_type_others_remove->ea_others[i]==target_type) {
                    exist=true;
                    if (remove_from_ea_others(source_type_others_remove,target_type->name)==failure){return failure;}
                    print_type(source_type_others_remove);
                    break;
                }
            }
            if (exist==false) {
                printf("Type name doesn't exist in the list.\n");
            }
        }
        // the target type doesn't exist in the system.
        else {printf("Type name doesn't exist in the list.\n");}

    }
    // the source type doesn't exist in the system.
    else {printf("Type name doesn't exist.\n");}
    return success;
}

/**
 * A function that receives a Pokémon name from the user, searches for a matching Pokémon
 * in the system, and prints its information if found.
 * @param pPoke_set An array of pointers to Pokémon instances
 * @param num_of_pokemons The total number of Pokémon stored in the array
 * @return Operation status indicating whether the search and print process completed successfully
 */
status print_pokemon_by_name(Poke** pPoke_set,int num_of_pokemons) {
    //input validation
    if (pPoke_set==NULL) {return failure;}

    //Receiving input from the user + editing it
    char buffer[300];
    printf("Please enter Pokemon name:\n");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\r\n")]='\0';

    //Checks whether a Pokemon with such a name exists in the system and print it.
    for (int i=0; i<num_of_pokemons; i++) {
        if (pPoke_set[i]==NULL) {return failure;}
        if (strcmp(pPoke_set[i]->pokename,buffer)==0) {
            print_pokemon(pPoke_set[i]);
            return success;
        }
    }

    printf("The Pokemon doesn't exist.\n");
    return success;
}

/**
 * A function that receives a Pokémon type name from the user, verifies that the type exists,
 * and prints all Pokémon belonging to that type if any are found in the system.
 * @param pSet_type An array of pointers to all Pokémon types
 * @param pPoke_set An array of pointers to all Pokémon instances
 * @param num_of_types The total number of Pokémon types in the system
 * @param num_of_pokemons The total number of Pokémon stored in the system
 * @return Operation status indicating whether the search and print operation completed successfully
 */
status print_pokemons_by_type(P_type** pSet_type,Poke** pPoke_set,int num_of_types,int num_of_pokemons) {
    //input validation
    if (pSet_type==NULL || pPoke_set==NULL) {return failure;}

    //Receiving input from the user + editing it
    char buffer[300];
    P_type* temp=NULL;
    exist ex=not_exist;
    printf("Please enter type name:\n");
    fgets(buffer,sizeof(buffer),stdin);
    buffer[strcspn(buffer,"\r\n")]='\0';

    for (int i=0; i<num_of_types; i++) {
        //Checks whether a type with such a name exists in the system.
        if (pSet_type[i]==NULL){return failure;}
        if (strcmp(pSet_type[i]->name,buffer)==0) {

            //Checks if there are Pokemon of this type in the system
            if (pSet_type[i]->cnt_type>0) {
                temp=pSet_type[i];
                ex=exist1;
                printf("There are %d Pokemons with this type:\n",pSet_type[i]->cnt_type);
                break;
            }
        ex=exist0;
        }
    }
    //Once the function has found that the requested type exists, it will the rellevant Pokemin with the same type.
    if (ex==exist1) {
        for (int j=0; j<num_of_pokemons; j++) {
            if (pPoke_set[j]==NULL) {return failure;}
            if (pPoke_set[j]->type==temp) {
                print_pokemon(pPoke_set[j]);
            }
        }
    }
    //The requested type does not exist.
    if (ex==exist0) {
        printf("There are no Pokemons with this type.\n");
    }

    //There is no Pokemons with this type in the system
    if (ex==not_exist) {
        printf("Type name doesn't exist.\n");
    }
    return success;
}

/**
 * Memory deallocation function
 * @param ptr A pointer to an array that holds pointers to all instances of the Pokémon existing in the system.
 * @param num_of_pokemons The number of Pokémon in the system
 */
void big_free_pokemons(Poke** ptr,int num_of_pokemons) {
    //Iterative transition and release of all existing 'Pokémons' in the system
    for (int i=0; i<num_of_pokemons; i++) {
        free_pokemon(ptr[i]);
    }
}

/**
 * Memory deallocation function
 * @param ptr A pointer to an array that holds pointers to all instances of the Pokémon types existing in the system.
 * @param num_of_types The number of Pokémon types available in the system
 */
void big_free_types(P_type** ptr,int num_of_types) {
    //Iterative transition and release of all existing 'Pokémon types' in the system
    for (int i=0; i<num_of_types; i++) {
        free_type(ptr[i]);
    }
}

/**
 * The main function of the program, responsible for initializing all system structures,
 * reading data from the input file, parsing and creating Pokémon types and Pokémon instances,
 * and managing the user menu that allows interaction with all supported operations.
 * It loads the number of types and Pokémon from command-line arguments, allocates memory
 * for the relevant dynamic arrays, processes the file line by line, and handles errors
 * such as invalid input and memory allocation failures. After execution, it frees all
 * allocated memory and closes the program safely.
 * @param argc Number of command-line arguments
 * @param argv Array of command-line argument strings
 * @return 0 on successful execution, or 1 in case of memory or file errors
 */
int main(int argc, char* argv[]) {

    //Saving the parameters obtained when running the file in variables
    int num_of_types=atoi(argv[1]);
    int num_of_pokemons=atoi(argv[2]);
    char* file=argv[3];

    //Opening the file + Initializing a buffer to read the lines + Initializing an appropriate auxiliary flag for easier reading of the file.
    FILE* pfile = fopen(file,"r");
    char buffer[300];
    flagline fline=Types_header;

    //Statement on pointers to dynamic arrays that will contain the instances of the various types
    Poke** pPoke_set=(Poke**)malloc(num_of_pokemons*sizeof(Poke*));
    if (pPoke_set==NULL) {
        printf("Memory problem\n");
        fclose(pfile);
        return 1;
    }
    //Creating an array in the heap that will hold pointers to all instances of the 'Pokémon type' that will be created during the program.
    //Additionally, it checks that the memory allocation was successful. If no memory problem is reported,
    //it releases all memory allocated so far and exits the program.
    P_type** pSet_type=(P_type**)malloc(num_of_types*sizeof(P_type*));
    if (pSet_type==NULL) {
        free(pPoke_set);
        fclose(pfile);
        printf("Memory problem\n");
        return 1;
    }

    bool memory_problem=false;
    //Reading each line separately from the file and saving the information according to the relevant content.
    while (fgets(buffer,sizeof(buffer),pfile)!=NULL) {
        if (memory_problem==true){break;}
        //Replaces the last character with \0 so that we can read each line as a 'regular' string
        buffer[strcspn(buffer,"\r\n")]='\0';
        switch (fline) {
            case Types_header:
                //Skips the TYPES header in the data file
                fline=type_list;
                break;

            case type_list:
                //Calling a function that creates a new instance of 'Pokémon Type' while checking whether the creation was successful or not.
                if (create_types_set(pSet_type,buffer,num_of_types)==failure){memory_problem=true;}
                fline=ea;
                break;

            case ea:
                //Checking whether we need to move on to the next stage of creating the Pokémon instances themselves.
                if (strcmp(buffer,"Pokemons")==0) {
                    fline=pokemon;
                    break;
                }
                //A call to a function that takes care of adding certain types to the corresponding lists of other types.
                if (add_to_ea_lists(pSet_type,buffer,num_of_types)==failure){memory_problem=true;}
                break;

            case pokemon:
                //Creating an instance of a new Pokémon based on the data in the file and adding the pointer that points to it to the appropriate array in the heap.
                if (add_pokemon_struct(pPoke_set,buffer,pSet_type,num_of_types)==failure){memory_problem=true;}
        }
    }

    //Setting the menu string to be printed to the user
    char* menu2print="Please choose one of the following numbers:\n1 : Print all Pokemons\n2 : Print all Pokemons types\n3 : Add type to effective against me list\n4 : Add type to effective against others list\n5 : Remove type from effective against me list\n6 : Remove type from effective against others list\n7 : Print Pokemon by name\n8 : Print Pokemons by type\n9 : Exit\n";
    bool b=true;

    //Infinite loop for the main menu until we receive an exit command
    while (b==true && memory_problem==false){
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
        } else if (buffer[0]>'9'||buffer[0]<'1') {
            input_case = invalid;
        } else {input_case = valid;}

        //Invalid input case
        if (input_case==invalid) {
            printf("Please choose a valid number.\n");
            continue;
        }
        //Classification into cases according to user request from input
        int case_id=atoi(buffer);

        //A call to perform a specific action based on what the user has entered.
        switch (case_id) {
            case 1:
                print_all_pokemons(pPoke_set,num_of_pokemons);
                break;

            case 2:
                print_all_types(pSet_type,num_of_types);
                break;

            case 3:
                add_type_ea_ma(pSet_type,num_of_types);
                break;

            case 4:
                add_type_ea_others(pSet_type, num_of_types);
                break;

            case 5:
                remove_type_ea_me(pSet_type, num_of_types);
                break;

            case 6:
                remove_type_ea_others(pSet_type, num_of_types);
                break;

            case 7:
                print_pokemon_by_name(pPoke_set,num_of_pokemons);
                break;

            case 8:
                print_pokemons_by_type(pSet_type,pPoke_set,num_of_types,num_of_pokemons);
                break;

            case 9:
                b=false;
                break;
        }
    }

    //Closing the data file
    fclose(pfile);

    //Freeing memory allocations from the inside out according to the principle
    big_free_pokemons(pPoke_set,num_of_pokemons);
    big_free_types(pSet_type,num_of_types);
    free(pSet_type);
    free(pPoke_set);

    //Exiting the program in case of a memory problem
    if (memory_problem==true) {
        printf("Memory Problem\n");
        return 1;
    }

    //Exiting the program in a normal case
    if (memory_problem==false) {
        printf("All the memory cleaned and the program is safely closed.\n");
        return 0;
    }
}