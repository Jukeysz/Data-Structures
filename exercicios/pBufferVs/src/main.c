#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// store all data in a single buffer pBuffer
// juliano fonseca\015\0email@gmail.com\0;mauro\030\0email@gmail.com\0:
// the very end of the buffer is always ':'

int main( void ) {
	// make IO interface
	// 1- add person (Name, Age, Email)
	// 2- remove person
	// 3- search person
	// 4- list all
	// 5- exit

	// pBuffer specification (initially has 500 bytes):
	// op | firstFlag | search | tempName | tempAge | tempEmail | remainingSize | DATASPOT
	// 4B | 4B        | 30B    | 30B      | 3B      | 40B       | 4B            | rest of the 385 bytes

	// before DATASPOT, we have the intermediate vars, and after it
	// we have the user data

	// TODO: two functions manipulating the same firstflag variable is messy
	
	void *pBuffer = malloc(500 * sizeof(char));
	if (pBuffer == NULL) {
		printf("Failed to allocate memory buffer\n");
		return 1;
	}
	int *op = pBuffer;
	int *hasUser = pBuffer + 4;
	*hasUser = 1;
	
	
	// buffer for searching a name
	char *search = pBuffer + 8;
	
	// temp buffers for adding a user
	char *tempName = pBuffer + 38;
	char *tempAge = pBuffer + 68;
	char *tempEmail = pBuffer + 71;

	// how many bytes to copy after the region to be shrinked 
	int *remainingSize = pBuffer + 111;

	printf("buffer agenda\n1- add person(Name, Age, Email)\n2- remove person\n3- search person\n4- list all\n5-exit\n");
	while( printf("Op:"), scanf( "%i", op ) ) {
		getchar();
		switch ( *op ) {
			// add user
			case 1: {
				// beginning of the data spot
				char *byteBuffer = pBuffer + 115;
				// find the offset to copy memory to (only valid if there is already something in the buffer)
				if (!(*hasUser)) {
					while ( *byteBuffer != ':' ) {
						byteBuffer++;
					}
					// stepping after the ':'
					byteBuffer++;
				}

				printf("Enter name: ");
				fgets(tempName, 30, stdin);
				// remove the \n
				tempName[strcspn(tempName, "\n")] = '\0';

				printf("Enter age: ");
				fgets(tempAge, 3, stdin);
				tempAge[strcspn(tempAge, "\n")] = '\0';

				getchar();

				printf("Enter email: ");
				fgets(tempEmail, 40, stdin);
				tempEmail[strcspn(tempEmail, "\n")] = '\0';

				// I have three buffers, I have to copy them to pBuffer with the appropriate offset,
				// each information is delimited by \0
				// it is pertinent to use memcpy perhaps

				// if I am adding a user and there are already some, adjust the old colon into a semicolon
				if (!*hasUser) {
					*(byteBuffer - 1) = ';';
				}
				
				// base offset + pBuffer
				memcpy(byteBuffer, tempName, strlen(tempName) + 1);
				// base offset + pBuffer + the previous data offset (+1 because I need the index after the \0)
				memcpy(byteBuffer + strlen(tempName) + 1, tempAge, strlen(tempAge) + 1);
				// base offset + pBuffer + the two previous data offset
				memcpy(byteBuffer + strlen(tempName) + 1 + strlen(tempAge) + 1, tempEmail, strlen(tempEmail) + 1);
				
				// add the final colon for marking the buffer's end
				// this is of subtle importance when calculating the offset for the next person
				//memcpy(byteBuffer + *nameLength + *ageLength + *emailLength, colon, strlen(colon));
				*(byteBuffer + strlen(tempName) + 1 + strlen(tempAge) + 1 + strlen(tempEmail) + 1)  = ':';
				*hasUser = 0;

				break;
			} break;

			case 2: {
				// use memmove for dealing with memory spots that overlap
				// in juliano\020\0jsf\0;joao\021\0joaor\0:, for instance,
				// if I want to remove joao
				// the first parameter is the destination, that is to say, shrink the data after the joao's region
				// into the beginning of joao's region

				// i've got to handle the particular case which there is a single user
				char *username = search;

				printf("Enter the name to be removed: ");
				fgets(username, 30, stdin);
				username[strcspn(username, "\n")] = '\0';

				char *byteBuffer;
				// change this variable, its purpose is telling whether or not the user is at the beginning
				*hasUser = 1;

				for (byteBuffer = pBuffer + 115; *byteBuffer != ':'; byteBuffer++) {
					if (*byteBuffer == ';' || *hasUser) {
						if (!(*hasUser)) {
							byteBuffer++;
						}
						// takes the beginning of byte buffer up to the next \0
						if (strcmp(byteBuffer, username) == 0) {
							// once I found the string, take the beginning into account 
							// and find the index of the next ';' or ':'
							// remaining points to the beginning of the section that comes after the chunk that has to be removed

							// the beginning of the region to be overwritten is the ';'
							// so bytebuffer - 1
							char *remaining = byteBuffer;
							byteBuffer -= 1;
							char *auxRemaining = NULL;
							
							while (*remaining != ':' && *remaining != ';') {
								remaining++;
							}

							/// remaining ends up pointing at one address that has ':' or ';'
							auxRemaining = remaining;
							// 1 because there has to be at least one ';' or ':'
							*remainingSize = 1;						
							while (*auxRemaining != ':') {
								(*remainingSize)++;
								auxRemaining++;
							}

							memmove(byteBuffer, remaining, *remainingSize);

							break;
						}
					}
					*hasUser = 0;
				}
				printf("Username not found\n");
				break;
			}
			case 4: {
				char *byteBuffer = pBuffer + 115;
				if ( byteBuffer != NULL ) {
					// TODO
					// Print only the people names
					// first one is easy, no need to adjust offset
					if (byteBuffer == NULL) {
						printf("No users\n");
						break;
					} else {
						char *word = byteBuffer;
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
				free(pBuffer);
				printf("Program finished!\n");
				return 0;
			}
		}
	}
}
