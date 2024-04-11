#include <stdio.h>

int binary(int n){
    int num;
    for (int i=1; i <= 8*sizeof(n); i++ ){
        num = n;
        if (num >>(8*sizeof(n)-i) & 1){
            printf("%d",1);
        }
        else{
            printf("%d",0);
        }
           
    }   
    putchar('\n');
    return 0; 
}
int roll(unsigned int x, int n, char side){
    int arr[sizeof(x)*8], num, transfer, transfer2, length;
    for (int i=1; i <= 8*sizeof(x); i++ ){
        num = x;
        if (num >>(8*sizeof(x)-i) & 1){
            arr[i-1] = 1 ;
        }
        else{
            arr[i-1] = 0;
        }
           
    }
    length = 8*sizeof(x);
    if (side == 'r'){
        for (int i = 1; i <= n; i++){
            transfer = arr[length-1];
            for (int j = 0; j <= length-1; j++){
                transfer2 = arr[j];
                arr[j] = transfer;
                transfer = transfer2;

            }  
        }
    }
    else{
        for (int i = 1; i <= n; i++){
            transfer = arr[0];
            for (int j = length-1; j >= 0; j--){
                transfer2 = arr[j];
                arr[j] = transfer;
                transfer = transfer2;
            
            }
        }

    }
    num = 0;
    for (int i = 0; i <= length-1; i++){
        num = num*2 + arr[i];
    }
    return num;
}
int main(void){
    int n, x;
    char side;
    printf("Введите число X, n кол-во позиций сдвига, влево или вправо (l или r) \n");
    scanf("%d\t%d\t%c", &x, &n, &side);
    printf("Двоичный вид числа X\n");
    binary(x);
    printf("Результат сдвига\n");
    binary(roll(x, n, side));

    return 0;
}