int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    int arraySize = 1;
    *returnSize = numRows;
    *returnColumnSizes = ( int* ) malloc( numRows * sizeof( int ) );
    
    // define array of int pointers, setting every pointer to NULL
    int **result = malloc( sizeof( int * ) * numRows );

    for ( int i = 0; i < numRows; i++ ) {

        // allocate memory for the current row
        int *current = ( int * ) malloc( sizeof(int) * arraySize );
        ( *returnColumnSizes )[i] = i + 1;
        result[i] = current;

        // handle first edge case in the first row
        if ( i == 0 ) {
            result[i][0] = 1;
            arraySize++;
            continue;
        }

        // define the numbers of the current row
        for ( int j = 0; j < arraySize; j++ ) {
            // handle edge cases for avoiding buffer overflow (beginning and ending)
            if ( j == 0 ) {
                result[i][j] = result[i - 1][j];
            } else if ( j == arraySize - 1 ) {
                result[i][j] = result[i - 1][j - 1];
            } else {
                // make the nums for the elements that are neither the beginning or the ending
                int a = result[i - 1][j] + result[i - 1][j - 1];
                result[i][j] = a;
            }
        }
        arraySize++;
    }

    return result;
}