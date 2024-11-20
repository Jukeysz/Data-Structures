#include <stdio.h>
#include <stdlib.h>

// USE TWO PASS ALGORITHM WITH COUNTING SORT

typedef struct hash_t {
    int key;
    int value;
} hash_t;

int main( void ) {
    int temp = 0;
    int *arr = NULL;
    int intCounter = 0;

    hash_t occurancies[3];
    occurancies[0].key = 1;
    occurancies[0].value = 0;
    occurancies[1].key = 2;
    occurancies[1].value = 0;
    occurancies[2].key = 3;
    occurancies[2].value = 0;

    // READ SECTION
    printf("This program prompts for integers and returns the in place sorted list\n");
    printf( "Usage: every integer different from 1, 2, 3 will exit the program\n" );
    while ( 1 ) { 
        printf( "Type the integer: " );
        scanf( "%d", &temp );
        getchar();
        if ( temp < 1 || temp > 3 ) {
            break;
        }

        if ( arr == NULL ) {
            arr = malloc( sizeof( int ) );
            arr[intCounter] = temp;
            intCounter++;
        } else {
            // extra sizeof due to the extra int being incremented for the new mem area
            int *tempList = realloc( arr, ( intCounter * sizeof( int ) ) + sizeof( int ) );
            arr = tempList;
            arr[intCounter] = temp;
            intCounter++;
        }

        // for ( int i = 0; i < intCounter; i++ ) {
        //     printf( "%d", arr[i] );
        // }
        // printf( "\n" );
    }

    // count the occurencies
    for ( int i = 0; i < intCounter; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            if (arr[i] == occurancies[j].key) {
                occurancies[j].value++;
            }
        }
    }

    // replace the original array based on occurrencies
    // this is a little complex
    for ( int i = 0; i < intCounter; i++ ) {
        for ( int j = 0; j < 3; j++ ) {
            if (occurancies[j].value > 0) {
                arr[i] = occurancies[j].key;
                occurancies[j].value--;
                break;
            }
        }
    }

    for ( int i = 0; i < intCounter; i++ ) {
        printf("%d", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}