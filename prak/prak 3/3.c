#include <stdio.h>
#include <stdlib.h>

void fun(int arr[5], int x, int n){
    int y;
    n = n %x;
    for(int j=1; j <= n; j++){
        y = arr[x-1];
        for (int i = x-1; i > 0; i--){
            arr[i]=arr[i-1];
    }
    }
    arr[0] = y;
}

int main(){
    int n, x = 5;
    scanf("%d", &n);
    int arr[5];
    for(int i = 0; i < x; i ++){
        scanf("%d", &arr[i]);
        }
    fun(arr, x, n);
    for(int i = 0; i<x; i++){
        printf("1-%d\n", arr[i]);
    }
}