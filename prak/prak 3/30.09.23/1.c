#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* skleyka(char* destination, const char* source){
    char* ptr = destination + strlen(destination);
    while (*source != '\0'){
        *ptr++ = *source++;
    }
    *ptr = '\0';
    return destination;
}

int main(int argc, char **argv){
    double sum_all= 0.0, sum_x = 0.0, x;
    char *st;
    char *sum_st = calloc(argc, sizeof(argv));
    for (int i=1; i<argc; i++){
        x = strtod(argv[i], &st);
        // printf("%f\n", x);
        if ((x != 0) && (*st == '\0')){
            sum_x += x;
        }
        sum_st = skleyka(sum_st, argv[i]);
    }
    printf("%f\n", sum_x);
    printf("%s", sum_st);
    free(sum_st);
}