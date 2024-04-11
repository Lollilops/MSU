// ДЗ-5 (07.10 до 21.10)

// 1. Написать макрос, который выводит на экран в двоичном виде целое число 
// (должен работать с целыми от char до long long). Оформить в виде макроса 
// с одним параметром — число, которое нужно вывести. 
// Как основу используйте функцию уже написанную.
// В main использовать макрос для вывода данных разных типов.
// Должен работать, например, такой фрагмент:
// char c=-3;
// if(c) BINPRINT(c); else printf("Zero!\n");
// BINPRINT((short)7);
// long x=15;
// if(x) BINPRINT(x); else printf("Zero!\n");
// BINPRINT((long long)x);

#include <stdio.h>
#include <stdlib.h>

#define BINPRINT(num) ({  \
    for(int i=1; i<=8*sizeof(num); i++){\
        if(num >> (8*sizeof(num) - i) & 1){\
            printf("%d", 1);\
        }\
        else{\
            printf("%d", 0);\
        }\
    }\
    printf("\n");\
    })

int main(){
    char c=-3;
    if(c) BINPRINT(c); else printf("Zero!\n");
    BINPRINT((short)7);
    long x=15;
    if(x) BINPRINT(x); else printf("Zero!\n");
    BINPRINT((long long)x);
}