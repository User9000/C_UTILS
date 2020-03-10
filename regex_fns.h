//

#ifndef UNTITLED2_REGEX_FNS_H
#define UNTITLED2_REGEX_FNS_H

typedef struct {
    const char *string;
    const char *regex;
    char ***substrings;
    _Bool use_case;
} regex_fn_s;

#define regex_match(...) regex_match_base((regex_fn_s){__VA_ARGS__})


//int asprintf(char **str, char* fmt, ...) __attribute__ ((format (printf,2,3)));

int regex_match_base(regex_fn_s in);
char * search_and_replace(char const *base, char const*search, char const *replace);


#endif //UNTITLED2_REGEX_FNS_H
