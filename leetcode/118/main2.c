/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    int arraySize = 1;
    
    // define array of int pointers, setting every pointer to NULL
    int **result = malloc(sizeof(int *) * numRows);

    for ( int i = 0; i < numRows; i++ ) {

        // allocate memory for the current row
        int *current = (int *) malloc(sizeof(int) * arraySize);
        result[i] = current;

        // handle first edge case in the first row
        if (i == 0) {
            result[i][0] = 1;
            arraySize++;
            continue;
        }

        // define the numbers of the current row
        for (int j = 0; j < arraySize; j++) {
            // handle edge cases for avoiding buffer overflow (beginning and ending)
            if ( j == 0 ) {
                int a = result[i - 1][j];
                result[i][j] = a;
                printf("%d", a);
            } else if ( j == arraySize - 1 ) {
                int a = result[i - 1][j];
                result[i][j] = result[i - 1][j];
                printf("%d", a);
            } else {
                // make the nums for the elements that are neither the beginning or the ending
                int a = result[i - 1][j] + result[i - 1][j - 1];
                printf("%d", a);
                result[i][j] = a;
            }
        }
        printf("\n");
        arraySize++;
    }

    // I am having trouble to return the returnSize and the returnColumnSizes accordingly
    // define arrays sizes
    int counter = 1 * sizeof(int);
    int total = 0;
    for ( int i = 0; i < numRows - 1; i++ ) {
        int *atual = (int *)malloc(sizeof(int));
        atual[0] = counter * sizeof(int);
        total += counter * sizeof(int);
        returnColumnSizes[i] = atual;
        counter++;
    }

    returnSize = malloc(sizeof(int));
    returnSize[0] = total;


    return result;
}