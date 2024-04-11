#include <stdio.h>

int main(){
    int a, b, n;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &n);
    for(int i=a;i<b;i++){
        if(i == a){
            printf("%*lld", (n*2)+1, (long long)i);
        }
        else{
            printf("%*lld", n+1, (long long)i);
        }

    }
    printf("\n");
    for(int i=a;i<b;i++){
        for(int j=a - 1;j<b;j++){
            if(j == a - 1){
                printf("%*lld", n, (long long)i);
            }
            else{
                if(j == b-1){
                    printf("%*lld\n",  n+1, (long long) i*j);
                }
                else{
                printf("%*lld",  n+1, (long long) i*j);
                }
            }
        }
    }
}