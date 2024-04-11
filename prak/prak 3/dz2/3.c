// Написать функцию, параметры — массив целых и размерность массива. 
// Функция должна отсортировать элементы данного массива по возрастанию 
// количества единичных бит в числе. В случае равенства количества 
// единичных бит сортировать по убыванию значения числа. 
// Пример. {1, 2, 3, 4, 5} => {4, 2, 1, 5, 3} 
// В main() задать массив, вывести массив на экран 
// как последовательность чисел в десятичном и в двоичном виде 
// (использовать Вашу функцию печати). 
// Вызвать функцию сортировки, затем вывести отсортированный массив. 
// Работает неверно см., напр. 23 121 32 54 2
#include <stdio.h>

int p_bit(int num){
    // printf("%d", num);
    int k=0;
    for(int i=1; i<=8*sizeof(num); i++){
        if(num >> (8*sizeof(num) - i) & 1){
            // printf("%d ", i);
            printf("%d", 1);
            k++;
        }
        else{
            // printf("%d ", i);
            printf("%d", 0);
        }
    }
    return k;
}

void sort_bin_ar(int ar[5],int ar1[5], int max_kol){
    int ar2[5], kol=1, num=0;
    // printf("done");
    while(kol != max_kol + 1){
        for(int i=4; i>=0; i--){
            if(ar1[i] == kol){
                ar2[num] = ar[i];
                num++;
                // printf("%d\n", ar2[num]);
            }
        }
        kol ++;
    }
    for(int i=0; i<5; i++){
        ar[i] = ar2[i];
    }
}

void sort_ar(int ar[], int ar1[]){
    int flag=0, change;
    while (flag != 1){
    flag = 1;
        for(int i=0; i<4;i++){
            if (ar[i] > ar[i + 1]){
                change = ar[i];
                ar[i] = ar[i + 1];
                ar[i + 1] = change;
                change = ar1[i];
                ar1[i] = ar1[i + 1];
                ar1[i + 1] = change;
                flag = 0;
                break;
            }
        }
    }
}

int main(){
    int ar[5]={23, 121, 32, 54, 2}, ar1[5], max_kol=0;
    for(int i=0; i<5; i++){
        printf("Десятичное представление: %d\nДвоичное представление: ", ar[i]);
        ar1[i]= p_bit(ar[i]);
        if(ar1[i] > max_kol){
            max_kol = ar1[i];
        }
        printf("\n");
    }
    // printf("done\n");
    sort_ar(ar, ar1);
    sort_bin_ar(ar, ar1, max_kol);
    printf("---------------\nОтсортированный массив: \n");
    for(int i=0;i<5;i++){
        printf("Десятичное представление: %d\nДвоичное представление: ", ar[i]);
        p_bit(ar[i]);
        printf("\n");
    }
}