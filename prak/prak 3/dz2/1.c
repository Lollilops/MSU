#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
void sum_make(int n1, int m1, int n2, int m2, int x, int y, int ar1[][m1],int ar2[][m2]){
    int i1 = 0, j1 = 0;
    for(int i=0; i<n1; i++){
        for(int j=0; j<m1; j++){
            if (((i - i1)==x && (j - j1) == y) && (i1 < n2) && (j1 < m2)){
                if ((ar1[i][j] >= 0 && ar2[i1][j1] >=0 && (ar1[i][j] > INT_MAX  - ar2[i1][j1]))||(ar1[i][j] < 0 && ar2[i1][j1] < 0 && (ar1[i][j] < INT_MIN  - ar2[i1][j1]))){
                    if(ar1[i][j] > INT_MAX  - ar2[i1][j1]){
                        ar1[i][j] = INT_MAX;
                    }
                    else{
                        ar1[i][j] = INT_MIN;
                    }
                }
                else{
                    ar1[i][j] = ar1[i][j] + ar2[i1][j1];
                }
                j1++;
                if (j+1 == m1){
                    j1 = 0;
                    i1 ++;
                }
            }
        }
        if (j1 == m2){
            j1 = 0;
            i1++;
        }        
    }
}


int main(){
    int n1, m1, n2, m2, x, y;
    int i, j;
    printf("Введите n1, m1, n2, m2, x, y:\n");
    scanf("%d%d%d%d%d%d", &n1, &m1, &n2, &m2, &x, &y);
    int ar1[n1][m1], ar2[n2][m2];
    printf("Введите массив %dx%d\n", n1, m1);
    for(i=0; i<n1; i++){
        j = 0;
        while(j < m1){
            scanf("%d", &ar1[i][j]);
            j++;
        }
    }
    printf("Введите массив %dx%d\n", n2, m2);
    for(i=0; i<n2; i++){
        j = 0;
        while(j < m2){
            scanf("%d", &ar2[i][j]);
            j++;
        }
    }
    printf("Done!\n");
    sum_make(n1, m1, n2, m2, x, y, ar1, ar2);
    printf("------\n");
    for(int i = 0; i<n1; i++){
        for(int j =0; j<m1; j++){
            printf("%d ", ar1[i][j]);
        }
        printf("\n");
    }
    return 0;
}