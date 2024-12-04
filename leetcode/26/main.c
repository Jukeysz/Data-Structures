#include <stdio.h>
#include <stdlib.h>

int removeDuplicates( int *nums, int numsLength );

typedef struct num {
	int symbol;
	int count;
	int done;
} num;

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
	num hashes[10] = {
		{0, 0},
		{1, 0},
		{2, 0},
		{3, 0},
		{4, 0},
		{5, 0},
		{6, 0},
		{7, 0},
		{8, 0},
		{9, 0}
	};

	size_t nextIndex = 0;
	int sum = 0;

	for ( int i = 0; i < numsLength; i++ ) {
		// todo write instruction
		for ( int j = 0; j < 10; j++ ) {
			if ( hashes[j].count == 2 && hashes[j].done == 0) {
				nums[nextIndex] = hashes[j].symbol;
				hashes[j].done = 1;
				nextIndex++;
			}
		}
		
		// check duplicates
		for ( int j = 0; j < 10; j++ ) {
			if ( hashes[j].symbol == nums[i] ) {
				hashes[j].count++;
				continue;
			}
		}
	}

	// operate sum of all duplicates
	for ( int i = 0; i < nextIndex; i++) {
		sum += nums[i];
	}

	return sum;
}
