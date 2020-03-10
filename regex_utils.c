//
// Created by Carlo Lam on 3/9/20.
//

#define _GNU_SOURCE

//#include "stopif.h"
#include <regex.h>
#include "regex_fns.h"
#include <string.h> //strlen
#include <stdlib.h> //malloc, memcpy

#include <stdio.h>
#include <stdarg.h> //va_start et al



static int count_parens(const char *string) {

    int out = 0;
    int last_was_backslash = 0;

    for(const char *step=string; *step !='\0'; step++) {

        if (*step == '\\' && !last_was_backslash){
                last_was_backslash = 1;
                continue;
        }
        if (*step == ')' && !last_was_backslash) {
            out++;
        }
         last_was_backslash = 0;
        }
    return out;
}


int regex_match_base(regex_fn_s in) {

      //  printf("%s\n", "CALLING REGEX_MATCH_BASE");
    if(!in.string){

        return -1;
    }
    if(!in.regex){return -2;}

    regex_t re;
    int matchcount = 0;

    if (in.substrings) {matchcount = count_parens(in.regex);}

    regmatch_t result[matchcount+1];

    int compiled_ok = !regcomp(&re, in.regex, REG_EXTENDED + (in.use_case ? 0 : REG_ICASE) + (in.substrings ? 0 : REG_NOSUB) );
    if(!compiled_ok) {
        //printf("%s", in.regex);

     return -3;
    }



    int found = !regexec(&re, in.string, matchcount+1, result, 0);
    if(!found) {return 0;}
   //
  // regexec(&re, in.string, matchcount+1, result, 0);

    if (in.substrings){
        *in.substrings = malloc(sizeof(char*) * matchcount);
        char **substrings = *in.substrings;
        //match zero is the whole string; ignore it.
        for (int i=0; i< matchcount; i++) {
            if (result[i+1].rm_eo > 0) {  //GNU peculiarity: match-to-empty marked with -1.
                int length_of_match = result[i+1].rm_eo - result[i+1].rm_so;
                substrings[i] = malloc(strlen(in.string)+1);
                memcpy(substrings[i], in.string + result[i+1].rm_so,length_of_match);
                substrings[i][length_of_match] = '\0';
            }
            else { //empty match
                substrings[i] = malloc(1);
                substrings[i][0] = '\0';
            }
        }
        in.string += result[0].rm_eo; //end of whole match;
    }
    regfree(&re);

    return matchcount;
}

char * search_and_replace(char const *base, char const*search, char const *replace){
    char *regex = NULL;
    char *out = NULL;
   asprintf(&regex, "(.*)(%s)(.*)", search);
    char **substrings;
    int match_ct =  regex_match(base, regex, &substrings);
    if(match_ct < 3) return NULL;
   asprintf(&out, "%s%s%s", substrings[0], replace, substrings[2]);
    for (int i=0; i< match_ct; i++)
        free(substrings[i]);
    free(substrings);
    return out;
}


int main(){
    char **substrings;

    int match_ct = regex_match("Hedonism by the alps, savory foods at every meal.", "([He]*)do.*a(.*)s, (.*)or.* ([em]*)al", &substrings);
    printf("%i matches:\n", match_ct);
    for (int i=0; i< match_ct; i++){
        printf("[%s] ", substrings[i]);
        free(substrings[i]);
    }
    free(substrings);
    printf("\n\n");

    match_ct = regex_match("", "([[:alpha:]]+) ([[:alpha:]]+)", &substrings);
    //Stopif(match_ct != 0, return 1, "Error: matched a blank");
     if (match_ct != 0 ){
         return 1;
     }
    printf("Without the L, Plants are: %s",
             search_and_replace("Plants\n", "l", ""));
}
