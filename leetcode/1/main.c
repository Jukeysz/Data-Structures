#include <stdio.h>
#include <stdlib.h>

int *twoSum( int entry[], int target, int entrySize );

int main( void ) {
    int entry[] = {2, 7, 11, 15};
    int entrySize = 4;
    int target = 9;

    int *result = NULL;

    result = twoSum( entry, target, entrySize );

    for ( int i = 0; i < 2; i++ ) {
        printf("%d", result[i]);
    }
    printf("\n");

    free(result);
}

int *twoSum( int entry[], int target, int entrySize ) {
    for ( int i = 0; i < entrySize; i++) {
        for ( int j = i + 1; j < entrySize; j++ ) {
            if ( ( entry[i] + entry[j] ) == target ) {
                int *res = malloc(sizeof(int) * 2);
                res[0] = i;
                res[1] = j;
                return res;
            }
        } 
    }
}