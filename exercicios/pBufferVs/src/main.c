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
	
	int *op = (int *)malloc(sizeof(int));
	void *pBuffer = malloc(500 * sizeof(char));
	int *firstFlag = (int *)malloc(sizeof(int));
	*firstFlag = 1;
	if (pBuffer == NULL) {
		printf("Failed to allocate memory buffer\n");
		return 1;
	}
	
	// buffer for searching a name
	char *search = (char *)malloc(40 * sizeof(char));
	
	// temp buffers for adding a user
	char *tempName = NULL;
	char *tempAge = NULL;
	char *tempEmail = NULL;

	int *nameLength = (int *)malloc(sizeof(int));
	int *ageLength = (int *)malloc(sizeof(int));
	int *emailLength = (int *)malloc(sizeof(int));

	char *colon = (char *)malloc(sizeof(char));
	*colon = ':';
	
	printf("buffer agenda\n1- add person(Name, Age, Email)\n2- remove person\n3- search person\n4- list all\n5-exit\n");
	while( scanf( "%i", op ) ) {
		getchar();
		switch ( *op ) {
			// add user
			case 1: {
				int *i = (int *)malloc(sizeof(int));
				*i = 0;
				char *byteBuffer = pBuffer;
				// find the offset to copy memory to (only valid if there is already something in the buffer)
				// this is wrong !!!!!!!!!!!!!!!!!!!
				if (!(*firstFlag)) {
					for (*i = 0; byteBuffer[*i] != ':'; (*i)++);
					// increment by one because I want the position right after the colon
					(*i)++;
				}

				tempName = (char *)malloc(30 * sizeof(char));
				if (tempName == NULL) {
					printf("Failed to allocate name buffer\n");
					return 1;
				}
				printf("Enter name: ");
				fgets(tempName, 30, stdin);
				// remove the \n
				tempName[strcspn(tempName, "\n")] = '\0';


				tempAge = (char *)malloc(3 * sizeof(char));
				if (tempAge == NULL) {
					printf("Failed to allocate age buffer\n");
					return 1;
				}
				printf("Enter age: ");
				fgets(tempAge, 3, stdin);
				tempAge[strcspn(tempAge, "\n")] = '\0';

				int *c = (int *)malloc(sizeof(int));
    			while ((*c = getchar()) != '\n' && c != EOF);

				tempEmail = (char *)malloc(40 * sizeof(char));
				if (tempEmail == NULL) {
					printf("Failed to allocate email buffer\n");
					return 1;
				}
				printf("Enter email: ");
				fgets(tempEmail, 40, stdin);
				tempEmail[strcspn(tempEmail, "\n")] = '\0';

				// I have three buffers, I have to copy them to pBuffer with the appropriate offset,
				// each information is delimited by \0
				// it is pertinent to use memcpy perhaps
				
				// It is the length + 1 because I also want to copy the \0
				*nameLength = strlen(tempName) + 1;
				*ageLength = strlen(tempAge) + 1;
				*emailLength = strlen(tempEmail) + 1;
				
				// if we are adding a user and there are already some, adjust the old colon into a semicolon
				if (!*firstFlag) {
					char *adjustSemicolon = pBuffer + *i - 1;
					*adjustSemicolon = ';';
				}
				
				// base offset + pBuffer
				memcpy(*i + pBuffer, tempName, *nameLength);
				// base offset + pBuffer + the previous data offset (+1 because I need the index after the \0)
				memcpy(*i + pBuffer + *nameLength, tempAge, *ageLength);
				// base offset + pBuffer + the two previous data offset
				memcpy(*i + pBuffer + *nameLength + *ageLength, tempEmail, *emailLength);
				
				// add the final colon for marking the buffer's end
				// this is of subtle importance when calculating the offset for the next person
				memcpy(*i + pBuffer + *nameLength + *ageLength + *emailLength, colon, strlen(colon));

				*firstFlag = 0;

				break;
			} break;

			case 2: {
				// use memmove for dealing with memory spots that overlap
				// in juliano\020\0jsf\0;joao\021\0joaor\0:, for instance,
				// if I want to remove joao
				// the first parameter is the destination, that is to say, shrink the data after the joao's region
				// into the beginning of joao's region
				char *username = (char *)malloc(sizeof(char) * 30);
				if (username == NULL) {
					printf("Failed memory allocation\n");
					return 1;
				}

				printf("Enter the name to be removed: ");
				fgets(username, 30, stdin);
				username[strcspn(username, "\n")] = '\0';

				char *byteBuffer = NULL;
				char *j = malloc(sizeof(char));
				if (j == NULL) {
					printf("Failed memory allocation\n");
					return 1;
				}			

				int *beginning = malloc(sizeof(int));
				if (beginning == NULL) {
					printf("Failed memory allocation\n");
					return 1;
				}						
				*beginning = 1;

				for (byteBuffer = pBuffer; *byteBuffer != ':'; byteBuffer++) {
					if (*byteBuffer == ';' || beginning) {
						if (!beginning) {
							byteBuffer++;
						}
						// takes the beginning of byte buffer up to the next \0
						if (strcmp(byteBuffer, username) == 0) {
							// once I found the string, take the beginning into account 
							// and find the index of the next ';' or ':'
							// remaining points to the beginning of the section that comes after the chunk that has to be removed
							char *remaining = byteBuffer;
							char *auxRemaining = NULL;
							
							while (*remaining != ':' && *remaining != ';') {
								remaining++;
							}

							/// remaining ends up pointing at one address before the ':' or ';'
							// this is why I use remaining++
							remaining++;

							auxRemaining = remaining;
							size_t *remainingSize = malloc(sizeof(size_t));
							// 1 because there has to be at least one ';' or ':'
							*remainingSize = 1;						
							while (*auxRemaining != ':') {
								(*remainingSize)++;
								auxRemaining++;
							}

							memmove(byteBuffer, remaining, *remainingSize);

							// clean up the old bytes that were shrinked
							memset(remaining, '0', remainingSize);

							break;
						}
					}
				}
				printf("Username not found\n");
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
				if ( ageLength != NULL ) {
					free(ageLength);
				}
				if ( nameLength != NULL ) {
					free(nameLength);
				}
				if ( emailLength != NULL ) {
					free(emailLength);
				}
				if (colon != NULL) {
					free(colon);
				}
				if ( tempName != NULL ) {
					free(tempName);
				} 
				if ( tempAge != NULL ) {
					free( tempAge );
				}
				if (tempEmail != NULL) {
					free( tempEmail );
				}
				if (firstFlag != NULL) {
					free( firstFlag );
				}

				return 0;
			}
		}
	}
}
