#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prava(const char *str){
    const char *str_pr = "rwxrwxrwx";
    int len_str = strlen(str), sum_str = 0, flag = 0;
    if(len_str != 9){
        return -1;
    }
    for(int j=0; j<9; j++){
        if(str[j] == str_pr[j] || str[j] == '-' && flag == 0){
            if (str[j] == '-'){
                sum_str = (sum_str*2) + 0;

                // printf("0\n");
            }
            else{
                sum_str = (sum_str*2) + 1;
                // printf("1\n");
            }
        }
        else{
            flag = 1;
            sum_str = -1;
        }
    }
    return sum_str;
}

int main(){
    int int_prava = prava("rrrrrrrrr");
    if (int_prava != -1){
        // printf("%d\n", int_prava);
        printf("%o\n", int_prava);// 111111111 = 
    }
    else{
        printf("eror\n");
    }
}