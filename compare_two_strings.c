//
// Created by Carlo Lam on 3/9/20.
//


#define _GNU_SOURCE  //cause stdiio.h to include asprintf

#include "stopif.h"
#include "<regex.h>"
#include "regex_fns.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(void) {

    char str[]="Hello world";
    char str2[]="Hello world";

    char *PtrToken;
    char *PtrToken2;


    PtrToken = strtok_R(str, " ");
    PtrToken2 = strtok

    while(PtrToken != NULL){

        printf("%s\n", PtrToken);
        PtrToken = strtok(NULL, " ");

    }

    if(strcmp(str, "Hello world") == 0){
      //  puts("Both variables are equal");
    }


    return 0;
}
