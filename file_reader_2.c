//
// Created by Carlo Lam on 3/5/20.
//


#include <stdio.h>
#include <stdlib.h>

int main() {

    FILE *fpointer;

    fpointer = fopen("bacon.txt", "r");
    char line[1000];
    fscanf(fpointer,"%[^\r]", line);
    printf("%s",line);
    fclose(fpointer);



    return 0;
}
