//1. Задача 3 из МЗ.
// Написать функцию, которая меняет в строке порядок слов на обратный.
// Применить ее к строке, полученной в п.2.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* skleyka(char* destination, const char* source){
    char* ptr = destination + strlen(destination);
    while (*source != '\0'){
            *ptr++ = *source++;
    }
    return destination;
}

char* razdel(char *destination, int argc, char **argv){
    char *ptr = calloc(argc, sizeof(argv));
    int stime, r_i, i = 0, j = 0;
    long ltime;
    ltime = time(NULL);
    stime = (unsigned int) ltime/2;
    srand(stime);
    r_i = rand() % 5;
    printf("%d ", r_i);
    while (destination[j] != '\0'){
        if (r_i == 0){
            ptr[i] = ' ';
            i++;
            r_i = rand() % 6;
            printf("%d ", r_i);
        }
        else{
            ptr[i] = destination[j];
            i++;
            j++;
            r_i--;
        }
    }
    ptr[i] = '\0';
    printf("\n----------------\n");
    free(destination);
    return ptr;
}

char* reverse(char *destination, int argc, char **argv){
    char *ptr = calloc(argc, sizeof(argv));
    int stime, r_i, len = 0, j_u= 0, j_d = 0, j = 0, i = 0;
    for(len; destination[len] != '\0'; len++){}
    len--;
    j_u = -1;// 654 4563 484
    // printf("%s %d\n", destination, len);
    while (j != len + 1){
        // printf("%d n\n", destination[len - j]);
        if ((destination[len - j] == ' ')||(j == len)){
            // printf("%d\n", destination[len - j]);
            j_d = j;
            if(j != len){
                j--;
            }
            // if (j != j_u){
                while(j != j_u){
                    ptr[i] = destination[len - j];
                    // printf("%d\n", i);
                    i++;
                    j--;
                }
            // }
            ptr[i] = ' ';
            i++;
            // printf("%d %s\n", i, ptr); // 2 3432 g5/ 5  
            j_u = j_d;
            j = j_u;
            // printf("%s\n", ptr);
        }
        j++;
    }
    ptr[i] = '\0';
    printf("----------------\n");
    free(destination);
    return ptr;
}
// 1001 1010 20239 djf3
int main(int argc, char **argv){
    double sum_all= 0.0, sum_x = 0.0, x;
    char *st, *sum_st = calloc(argc, sizeof(argv));
    for (int i=1; i<argc; i++){
        x = strtod(argv[i], &st);
        if ((x != 0) && (*st == '\0')){
            sum_x += x;
        }
        sum_st = skleyka(sum_st, argv[i]);
    }
    sum_st = razdel(sum_st, argc, argv);
    printf("%f\n", sum_x);
    printf("%s\n", sum_st);
    sum_st = reverse(sum_st, argc, argv);
    printf("%s\n", sum_st);
    free(sum_st);
}