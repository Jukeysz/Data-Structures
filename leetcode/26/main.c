#include <stdio.h>
#include <stdlib.h>

int removeDuplicates( int *nums, int numsLength );

int main( void ) {
	int nums[] = { 0,0,1,1,1,2,2,3,3,4 }; // should return 5 and the in place list
	int numsLength = 10;
	int result = removeDuplicates( nums, numsLength );
	printf( "The num output is %d\n", result );
	for ( int i = 0; i < numsLength; i++ ) {
		printf("%d", nums[i]);
	}
	printf("\n");
}

int removeDuplicates( int *nums, int numsLength ) {
	size_t nextIndex = 0;
	int duplicateCount = 0;
	int i = 0;
	while ( i < numsLength ) {
		int j = i + 1;
		for ( j; nums[i] == nums[j] && j < numsLength - 1; j++ );
		duplicateCount++;
		nums[nextIndex] = nums[i];
		nextIndex++;
		i = j;
	}

	return duplicateCount;
}
