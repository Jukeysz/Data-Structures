#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// store all data in a single buffer pBuffer
// find some way of detaching each data and detaching each user
// juliano fonseca\015\0email@gmail.com\0;mauro\030\0email@gmail.com\0:
// the very end of the buffer is always ':'

int main( void ) {
	// make IO interface
	// 1- add person (Name, Age, Email)
	// 2- remove person
	// 3- search person
	// 4- list all
	// 5- exit
	
	int *op = NULL;
	void *pBuffer = malloc(500 * sizeof(char));
	int *firstFlag;
	*firstFlag = 1;
	if (pBuffer == NULL) {
		printf("Failed to allocate memory buffer\n");
		return 1;
	}
	
	// buffer for searching a name
	char *search = NULL;
	
	// temp buffers for adding a user
	char *tempName = NULL;
	char *tempAge = NULL;
	char *tempEmail = NULL;

	int *nameLength = NULL;
	int *ageLength = NULL;
	int *emailLength = NULL;
	
	printf("buffer agenda\n1- add person(Name, Age, Email)\n2- remove person\n3- search person\n4- list all\n5-exit\n");
	while( scanf( "%d", op ) != EOF ) {
		switch ( *op ) {
			// add user
			case 1: {
				int *i = NULL;
				*i = 0;
				char *byteBuffer = pBuffer;
				// find the offset to copy memory to (only valid if there is already something in the buffer)
				if (!firstFlag) {
					for (*i = 0; byteBuffer[*i] != ':'; (*i)++) {
						printf("yay\n");
					}
					// increment by one because I want the position right after the colon
					(*i)++;
				}

				printf("reaches this part\n");

				tempName = (char *)malloc(30 * sizeof(char));
				if (tempName == NULL) {
					printf("Failed to allocate name buffer\n");
					return 1;
				}
				fgets(tempName, strlen(tempName), stdin);
				// remove the \n
				tempName[strcspn(tempName, "\n")] = '\0';


				tempAge = (char *)malloc(3 * sizeof(char));
				if (tempAge == NULL) {
					printf("Failed to allocate age buffer\n");
					return 1;
				}
				fgets(tempAge, strlen(tempAge), stdin);
				tempAge[strcspn(tempAge, "\n")] = '\0';

				tempEmail = (char *)malloc(40 * sizeof(char));
				if (tempEmail == NULL) {
					printf("Failed to allocate email buffer\n");
					return 1;
				}
				fgets(tempEmail, strlen(tempEmail), stdin);
				tempEmail[strcspn(tempEmail, "\n")] = '\0';

				// I have three buffers, I have to copy them to pBuffer with the appropriate offset,
				// each information is delimited by \0
				// it is pertinent to use memcpy perhaps
				
				// It is the length + 1 because I also want to copy the \0
				*nameLength = strlen(tempName) + 1;
				*ageLength = strlen(tempAge) + 1;
				*emailLength = strlen(tempEmail) + 1;
				
				// if we are adding a user and there are already some, adjust the old colon into a semicolon
				if (pBuffer != NULL) {
					char *adjustSemicolon = pBuffer + *i - 1;
					*adjustSemicolon = ';';
				}
				
				// base offset + pBuffer
				memcpy(*i + pBuffer, tempName, *nameLength);
				// base offset + pBuffer + the previous data offset (+1 because I need the index after the \0)
				memcpy(*i + pBuffer + *nameLength + 1, tempAge, *ageLength);
				// base offset + pBuffer + the two previous data offset
				memcpy(*i + pBuffer + *nameLength + 1 + *ageLength + 1, tempEmail, *emailLength);
				
				// add the final colon for marking the buffer's end
				// this is of subtle importance when calculating the offset for the next person

				char *colon;
				*colon = ':';
				memcpy(*i + pBuffer + *nameLength + 1 + *ageLength + 1 + *emailLength + 1, colon, strlen(colon));

				*firstFlag = 0;

				break;
			}
			case 4: {
				if ( pBuffer != NULL ) {
					// TODO
					// Print only the people names
					// first one is easy, no need to adjust offset
					if (pBuffer == NULL) {
						printf("No users\n");
						break;
					} else {
						char *word = pBuffer;
						printf("%s\n", word);
						
						// stop at the next semicolon, breaking if it finds any ':'
						while (*word != ';') {
							if (*word == ':') {
								break;
							}
							word++;
						}
						
						// +1 for not printing out the semicolon as well
						printf("%s\n", word + 1);
					}
					break;
				}
			}
			case 5: {
				if ( pBuffer != NULL ) {
					free(pBuffer);
				}
				return 0;
				break;
			}
		}
	}

	

}
