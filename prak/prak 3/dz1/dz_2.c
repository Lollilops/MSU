// 2.
// Написать функцию вывода на экран целого числа в двоичном виде. 
// Незначащие нули тоже выводите. 
// Отрицательные числа должны выводиться в их внутреннем представлении 
// (например, -1 выводится как последовательность из единиц).
// Написать функцию, которая осуществляет циклический сдвиг беззнакового 
// целого x на n позиций вправо или влево. 
// Направление сдвига задается параметром функции. 
// Измененное число вернуть в качестве результата.
// В функции main() вводить целые числа, сдвигать, 
// печатать в двоичном виде исходное число и результат сдвига.
#include <stdio.h>

void p_bit(int num){
    for(int i=1; i<=8*sizeof(num); i++){
        if(num >> (8*sizeof(num) - i) & 1){
            printf("%d", 1);
        }
        else{
            printf("%d", 0);
        }
    }
}

int move(int num, int n){
    int ar[8*sizeof(num)], change;
    for (int i=1; i <= 8*sizeof(num); i++ ){
        if (num >>(8*sizeof(num)-i) & 1){
            ar[i-1] = 1 ;
        }
        else{
            ar[i-1] = 0;
        }
    }
    if(n >= 0){
        for(int i=0; i<n; i++){
            change = ar[8*sizeof(num) - 1];
            for (int j =8*sizeof(num) - 1; j > 0; j--){
                ar[j] = ar[j - 1];
            }
            ar[0] = change;
        }
    }
    else{
        for(int i=n; i<0; i++){
            change = ar[0];
            for (int j=0; j < 8*sizeof(num) + 1; j++){
                ar[j-1] = ar[j];
            }
            ar[8*sizeof(num) - 1] = change;
        }
    }
    num = 0;
    for (int i = 0; i <= 8*sizeof(num)-1; i++){
        num = num*2 + ar[i];
    }
    return num;
}

int main(){
    int x, n;
    printf("Введите число: ");
    scanf("%d", &x);
    printf("Введите сдвиг(число > 0 - движение по часовой): ");
    scanf("%d", &n);
    p_bit(x);
    printf(" - двоичный вид\n");
    x = move(x, n);
    p_bit(x);
    printf(" - двоичный вид после сдвига\n");

}
