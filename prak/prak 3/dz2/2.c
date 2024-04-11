// Написать функцию, которая заполняет массив размерности MxN 
// числами от 1 до MxN, расположив их по спирали, 
// закрученной по часовой стрелке, так, 
// как показано в примере. 
// Пример: на входе 4 4 
// Результат: 
// 1 2 3 4 
// 12 13 14 5 
// 11 16 15 6 
// 10 9 8 7 
// В main(): 
// На стандартном потоке ввода задаются два целых числа M и N 
// ( 1<=M, N <=256) , создается и заполняется массив. 
// Массив вывести на экран.
// 1 2 3 4 5
// 16 17 18 19 6
// 15 24 25 20 7 
// 14 23 22 21 8
// 13 12 11 10 9
#include <stdio.h>

void spiral(int m, int n,int ar[][n]){
    int up=0, right=n, down=m, left=-1, st=0, kol=0, ch=0;
    int up_f=0, right_f=1, down_f=0, left_f=0;
    for(int i=1; i<=m*n; i++){
        ch = 0;
        if (up_f == 1){
                ar[kol][st] = i;
                // printf("%d %d %du\n", i, kol, st);
                kol --;
                if(kol == up){
                    kol ++;
                    st ++;
                    up_f = 0;
                    right_f = 1;
                    up ++;
                    ch = 1;
                }
        }
        if (left_f == 1){
                ar[kol][st] = i;
                // printf("%d %d %dl\n", i, kol, st);
                st --;
                if(st == left){
                    st ++;
                    kol --;
                    left_f = 0;
                    up_f = 1;
                    left ++;
                }
        }if (down_f == 1){
                ar[kol][st] = i;
                // printf("%d %d %dd\n", i, kol, st);
                kol++;
                if(kol == down){
                    kol --;
                    st --;
                    down_f = 0;
                    left_f = 1;
                    down --;
                }
        }
        if ((right_f == 1) && (ch == 0)){
                ar[kol][st] = i;
                // printf("%d %d %dr\n", i, kol, st);
                st ++;
                if(st == right){
                    st --;
                    kol ++;
                    right_f = 0;
                    down_f = 1;
                    right --;
                }
        }
    // printf("%d %d %d\n", i, kol, st);
    }
    // printf("-------\n");
    // printf("%d\n", ar[1][0]);
    // for(int i=0; i<m; i++){
    //     for(int j=0; j<n; j++){
    //         printf("%d ", ar[i][j]);
    //     }
    //     printf("\n");
    // }
    // return &ar[0][0];
}


int main(){
    int m, n;
    printf("Введите m и n:\n");
    scanf("%d%d", &m, &n);
    int ar[m][n];
    spiral(m, n, ar);
    printf("--------\n");
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            printf("%d ", ar[i][j]);
        }
        printf("\n");
    }
    return 0;
}