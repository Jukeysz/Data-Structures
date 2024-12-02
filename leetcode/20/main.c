#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct token_t {
	char open;
	char close;
	int countOpen;
	int countClose;
} token_t;

typedef struct node {
	struct node *next;
	token_t lastTok;
} node;

bool isValid( char* s );
bool isClose( char c );

int main( void ) {
	char *test1 = "()[]{}";
	char *test2 = "(]";

	if ( isValid( test2 ) ) {
		printf( "Correct" );
	} else {
		printf( "Incorrect" );
	}
}

bool isValid( char* s ) {
	token_t symbols[3];
	symbols[0].open = '(';
	symbols[0].close = ')';
	symbols[1].open = '[';
	symbols[1].close = ']';
	symbols[2].open = '{';
	symbols[2].close = '}';

	node *head = NULL;

	for ( int i = 0; i < strlen( s ); i++ ) {
		for ( int j = 0; j < 3; j++ ) {
			if ( s[i] == symbols[j].open ) {
				symbols[j].countOpen++;
				node *new = malloc( sizeof( node ) );
				if (new == NULL) return false;

				new->lastTok.open = symbols[j].open;
				new->lastTok.close = symbols[j].close;
				new->next = head;
				head = new;
				break;
			}
		}
		for ( int j = 0; j < 3; j++ ) {
			if ( s[i] == symbols[j].close ) {
				symbols[j].countClose++;
				if ( head == NULL || head->lastTok.close != symbols[j].close ) {
					return false;
				}		
				node *temp = head;
				head = head->next;
				free( temp );
			} 		
		}
	}
	while ( head != NULL ) {
		node *temp = head;
		head = head->next;
		free(temp);
	}

	for ( int k = 0; k < 3; k++ ) {
		if ( symbols[k].countClose != symbols[k].countOpen) {
			return false;
		}
	}
	return true;
}
