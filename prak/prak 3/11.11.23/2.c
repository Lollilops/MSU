#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p_bit(char num){
    // printf("%d", num);
    for(int i=1; i<=8*sizeof(num); i++){
        if(num >> (8*sizeof(num) - i) & 1){
            // printf("%d ", i);
            printf("%d", 1);
        }
        else{
            // printf("%d ", i);
            printf("%d", 0);
        }
    }
}

char *prava(int num){
    char *str = malloc(10);
    if(num <0 || num > 511){
        str = "error";
        return str;
    }
    const char *str_pr = "rwxrwxrwx";
    int i = 1;
    // printf("-----------");
    while(i<=9){
    // for(int i=1; i<9; i++){
        if(num >> (9 - i) & 1){
            // printf("%d %d\n", 1, i);
            str[i-1] = str_pr[i-1];
            // printf("%d\n", str[i-1]);
        }
        else{
            // printf("%d ", i);
            // printf("%d %d\n", 0, i);
            str[i-1] = '-';
        }
        i++;
    }
    str[i] = '\0';
    return str;
}

int main(){
    const char *str_prava = prava(256);
    printf("-----\n");
    printf("%s\n", str_prava);// 111111111 = 
}