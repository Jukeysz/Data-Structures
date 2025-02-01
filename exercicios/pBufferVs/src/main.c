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
	// 4B | 4B        | 30B    | 30B      | 3B      | 40B       | 4B            | single byte that holds a single ':'

	// before DATASPOT, we have the intermediate vars, and after it
	// we have the user data

	//void *pBuffer = malloc(125 * sizeof(char));
	void *pBuffer = malloc(3 * sizeof(int) + 104 * sizeof(char));
	if (pBuffer == NULL) {
		printf("Failed to allocate memory buffer\n");
		return 1;
	}
	int *op = pBuffer;

	// determines how many users there are in the list
	// useful for removing elements that are unique on the list
	int *hasUser = pBuffer + 4;
	*hasUser = 0;
	
	
	// buffer for searching a name
	char *search = pBuffer + 8;
	
	// temp buffers for adding a user
	char *tempName = pBuffer + 38;
	char *tempAge = pBuffer + 68;
	char *tempEmail = pBuffer + 71;

	// how many bytes to copy after the region to be shrinked 
	int *remainingSize = pBuffer + 111;

	// making the list empty
	char *colon = pBuffer + 115;
	*colon = ':';

	printf("buffer agenda\n1- add person(Name, Age, Email)\n2- remove person\n3- search person\n4- list all\n5-exit\n");
	while( printf("Op:"), scanf( "%i", op ) ) {
		getchar();
		switch ( *op ) {
			// add user
			case 1: {
				// beginning of the data spot
				// char *byteBuffer = pBuffer + 115;
				// find the offset to copy memory to (only valid if there is already something in the buffer)
				// if (*byteBuffer != ':') {
				//	while ( *byteBuffer != ':' ) {
				//		byteBuffer++;
				//	}
				//	// stepping after the ':'
				//	byteBuffer++;
				//}

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
				char *byteBuffer = pBuffer + 115;

				char *beginning = pBuffer;
				// find the offset that is the end of the buffer for calculating byteBuffer - beginning
				if (*byteBuffer != ':') {
					while ( *byteBuffer != ':' ) {
						byteBuffer++;
					}
				}

				pBuffer = realloc(pBuffer, strlen(tempEmail) + 1 + strlen(tempAge) + 1 + strlen(tempName) + 1 + (byteBuffer - beginning + 2));
				op = pBuffer;
				hasUser = pBuffer + 4;
				search = pBuffer + 8;
				tempName = pBuffer + 38;
				tempAge = pBuffer + 68;
				tempEmail = pBuffer + 71;
				remainingSize = pBuffer + 111;


				byteBuffer = pBuffer + 115;
				while ( *byteBuffer != ':' ) {
					byteBuffer++;
				}

				// if there is more than a single user in the list, reach the beginning of next section to copy memory to
				// and adjust the old colon into a semicolon
				if (*hasUser != 0) {
					byteBuffer++;
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
				(*hasUser)++;

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

				for (byteBuffer = pBuffer + 115; *byteBuffer != ':'; byteBuffer++) {
					// compare strings if reading at the beginning, when byteBuffer == pBuffer
					if (*byteBuffer == ';' || byteBuffer == pBuffer + 115) {
						// advancing through the char after ';', except when at the beginning
						if (byteBuffer != pBuffer + 115) {
							byteBuffer++;
						} 
						if (strcmp(byteBuffer, username) == 0) {
							char *remaining = byteBuffer;
							// if there is a single user and strcmp passed, just clean up the buffer by adding : at the beginning
							if (*hasUser == 1) {
								pBuffer = realloc(pBuffer, 3 * sizeof(int) + 104 * sizeof(char));
								byteBuffer = pBuffer + 115;
								*byteBuffer = ':';
								op = pBuffer;
								hasUser = pBuffer + 4;
								search = pBuffer + 8;
								tempName = pBuffer + 38;
								tempAge = pBuffer + 68;
								tempEmail = pBuffer + 71;
								remainingSize = pBuffer + 111;

								*hasUser = 0;
								break;
							} else {
								// had to increment one before for the strcmp, go back to the original idx ';'
								if (byteBuffer != pBuffer + 115) {
									byteBuffer -= 1;
								}
								char *auxRemaining = NULL;
								
								while (*remaining != ':' && *remaining != ';') {
									remaining++;
								}
								// the region to be moved is the first char of the
								// next user to the beginning
								if (byteBuffer == pBuffer + 115) {
									remaining++;
								}

								/// remaining ends up pointing at one address that has ':' or ';'
								// auxremaining exists for counting how many characters still exist in the rest of the buffer
								auxRemaining = remaining;
								// 1 because there has to be at least one ';' or ':'
								*remainingSize = 1;						
								while (*auxRemaining != ':') {
									(*remainingSize)++;
									auxRemaining++;
								}

								memmove(byteBuffer, remaining, *remainingSize);

								remaining = pBuffer + 115;
								while (*remaining != ':') {
									remaining++;
								}
								byteBuffer = pBuffer;

								pBuffer = realloc(pBuffer, remaining - byteBuffer + 1);
								op = pBuffer;
								hasUser = pBuffer + 4;
								search = pBuffer + 8;
								tempName = pBuffer + 38;
								tempAge = pBuffer + 68;
								tempEmail = pBuffer + 71;
								remainingSize = pBuffer + 111;
								(*hasUser)--;
								break;
							}
							if (*(byteBuffer + 1) == ':') {
								printf("Username not found");
								break;
							}
						}
					}
				}
				break;
			} break;

			case 3: {
				char *username = search;

				fgets(username, 30, stdin);
				username[strcspn(username, "\n")] = '\0';

				char *byteBuffer = pBuffer + 115;

				if (*hasUser == 0) {
					printf("No users in the list\n");
					break;
				}

				while (*byteBuffer != ':') {
					if (*byteBuffer == ';' || byteBuffer == pBuffer + 115) {
						if (byteBuffer != pBuffer + 115) {
							byteBuffer++;
						}
						if (strcmp(byteBuffer, username) == 0) {
							printf("%s\n", byteBuffer);
							while (*byteBuffer != ':' && *byteBuffer != ';') {
								if (*byteBuffer == '\0' && *(byteBuffer + 1) != ':' && *(byteBuffer + 1) != ';') {
									printf("%s\n", byteBuffer + 1);
								}
								byteBuffer++;
							}
							break;
						}
					}
					byteBuffer++;
				}
				break;
			}

			case 4: {
				char *byteBuffer = pBuffer + 115;
				if (*hasUser == 0) {
					printf("No users\n");
					break;
				} else {
					char *word = byteBuffer;
					printf("%s\n", word);
					
					// stop at the next semicolon, breaking if it finds any ':'

					while (*word != ':') {
						if (*word == ';') {
							printf("%s\n", word + 1);
						}
						word++;
					}
				}
				break;
			}
			case 5: {
				free(pBuffer);
				printf("Program finished!\n");
				return 0;
			}
		}
	}
}
