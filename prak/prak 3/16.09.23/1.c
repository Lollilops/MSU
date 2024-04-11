#include <stdio.h>

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

int bit(char *p, int len, int n){
    // printf("%d", num);
    // for(int i=0; i<=8*sizeof(*p); i++){
        // printf("%l",sizeof(*p));
        if(*(p + n/8) >> (7 - n%8 ) & 1){
            return 1;
        }
        else{
            return 0; 
        }
    // }
}

int main(){
    int n = 3, x;
    char ar[] = {'1', '2', '3'};
    for(int i=0;i<n;i++){
        p_bit(ar[i]);
    }
    printf("\n");
    scanf("%d", &x);
    printf("%d\n", bit(ar, sizeof(ar), x));
}