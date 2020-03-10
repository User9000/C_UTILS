//
// Created by Carlo Lam on 3/10/20.
//

#define _GNU_SOURCE //cause stdio.h to include asprintf
#include <stdio.h>
#include <stdlib.h> //free

void get_strings(char const *in){
    char *cmd;
    asprintf(&cmd, "strings %s", in);

    printf("%s", cmd);
 //   if (system(cmd)) {

   //     printf("something went wrong running %s\n", cmd);
    //}
    printf("\n\n");
    free(cmd);
}

int main(int argc, char **argv){
    printf("%s\n",argv[0]);
    get_strings(argv[1]);
}
