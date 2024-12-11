#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int lengthOfLastWord( char *s );

int main( void ) {
    char *test1 = "Hello world";
    char *test2 = "hello worlds ";

    int result = lengthOfLastWord( test1 );
    printf("result: %d\n", result);

    return 0;
}

int lengthOfLastWord( char *s ) {
    int idx = strlen(s) - 1;
    
    int cnt = 0;

    while ( idx >= 0 && s[idx] == ' ' ) {
        idx--;
    }

    while ( idx >= 0 && s[idx] != ' ' ) {
        cnt++;
        idx--;
    }

    return cnt;
}
