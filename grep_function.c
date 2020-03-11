//
// Created by Carlo Lam on 3/10/20.
//

/*
    The following example prints out all lines
    from FILE "f" that match "pattern".
*/
#include <stdio.h>
#include <regex.h>
#include <limits.h>

#define BUFFER_SIZE   512

void grep( char* pattern, FILE* f, int *rc )
{
    int t;
    regex_t re;
    char    buffer[BUFFER_SIZE];

    if ((t=regcomp( &re, pattern, REG_NOSUB )) != 0) {
        regerror(t, &re, buffer, sizeof buffer);
        fprintf(stderr,"grep: %s (%s)\n",buffer,pattern);
        return;
    }
    while( fgets( buffer, BUFFER_SIZE, f ) != NULL ) {
        if( regexec( &re, buffer, 0, NULL, 0 ) == 0 ) {
            fputs( buffer, stdout );
            *rc=1;
        }
    }
    regfree( &re );

    return;
}

int main() {

    char *SERVER= "[0-9]*.SERVER.POLL[[:blank:]]OK";
    int rc = 0;

    FILE *fpointer;

    fpointer = fopen("bacon.txt", "r");

    grep(SERVER, fpointer, &rc);

  //  int check =
    if(rc==1){
       puts("SERVER OK");
    }

    return 0;
}
