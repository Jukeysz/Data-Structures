#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// format style accordingly

int main( void ) {
    // name is the temp var and names is the result string

    char name[15] = {};
    char *names = NULL;
    int operation = 0;

    while ( 1 ) {
        printf( "MENU\n1) Adicionar nome\n2) Remover nome\n3) Listar\n4) Sair\n" );
        scanf( "%d", &operation );
        getchar();
        switch ( operation ) {
            case 1: {
                printf( "Escreva o nome: " );
                scanf( "%s", name );
                           
                getchar();
                // if names is empty, allocate memory and copy contents from "name"
                if ( names == NULL ) {
                    names = ( char * ) malloc( strlen( name ) + 1 );
                    int i;
                    // for ( i = 0; i < strlen(name); i++ ) {
                    //     names[i] = name[i];
                    // }
                    strncpy( names, name, strlen( name ) );
                    // add the null terminator
                    // names[i + 1] = '\0';
                } else {
                    // realloc the memory that names holds and add the size that name
                    // holds (which is the strlen of both, plus the null terminator of one of them)

                    char *newNames = ( char * ) realloc( names,  strlen( names ) + strlen( name ) + 1 );
                    names = newNames;

                    // start copying the contents from "name", getting the correct offset index
                    // which just happens to be the strlen of names because it is an index
                    // int i = 0;
                    // int j = 0;
                    // for ( i = strlen( names ), j; j < strlen( name ); i++, j++ ) {
                    //     names[i] = name[j];
                    // }
                    // names[i + 1] = '\0';

                    // pointer arithmetic
                    strcpy(names + strlen(names), name);
                }
                break;
            }
            case 2: {
                printf( "Escreva o nome a ser removido: " );
                scanf( "%s", name );
                getchar();

                // allocate memory without the given name using malloc
                // add the range of forbidden indexes when copying!!!
                // once it reaches a forbidden index, I have to add the name size
                // to the index and continue copying

                int nameLength = strlen( name );
                char *newNames = malloc( strlen( names ) - nameLength );
                int subStringIndex;
                int i, j, k, l;

                // spaghetti code that finds the substring index
                for ( i = 0; i < strlen( names ); i++ ) {
                    int matchSequence = 0;
                    if ( names[i] == name[0] ) {
                        // if the l makes the loop run collapse the string, is it an issue
                        for ( j = i, k = 0, l = 0; l < strlen( name ); j++, k++, l++ ) {
                            if ( names[j] == name[k] ) {
                                matchSequence++;
                                if ( matchSequence == nameLength ) {
                                    subStringIndex = i;
                                    i, j, k = 0;
                                    break;
                                }
                            }
                        }
                    }
                }

                // hold two indices, one for newNames (new string) 
                // and the other for the old string (names)
                for ( i = 0, j = 0; j < strlen(names) - strlen(name); j++ ) {
                    // if i is the same as the subStringIndex, add some amount to avoid
                    // the forbidden index, which is the substring
                    if ( i == subStringIndex ) {
                        i += nameLength;
                    }

                    newNames[j] = names[i];
                    i++;
                }
                newNames[j + 1] = '\0';
                free(names);
                names = newNames;
                break;
            }

            case 3: {
                for ( int i = 0; i < strlen( names ); i++ ) {
                    printf( "%c", names[i] );
                }
                printf( "\n" );
                break;
            }

            case 4: {
                free( names );
                exit( 0 );
            }
        }
    }
}