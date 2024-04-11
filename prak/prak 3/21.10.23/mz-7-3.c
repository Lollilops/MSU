//
//  main.c
//  mz-7-1
//
//  Created by Егор Мальцев on 21.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 50

typedef void(*PF) (int, char*);

void f1(int N, char* name) {
    FILE* f1 = fopen(name, "r+");
    FILE* f2 = fopen("f2.txt", "w+");
    if (f1 == NULL || f2 == NULL) {
        printf("ОШИБКА\n");
    } else {
        char* str = malloc(MAXLEN + 1);
        while (fgets(str, MAXLEN+1, f1) != NULL) {
            if ((strlen(str)-1) <= N) {
                fputs(str, f2);
            }
        }
        fclose(f1);
        fclose(f2);
        free(str);
        remove(name);
        rename("f2.txt", name);
    }
}

void f2(int N, char* name) {
    FILE* f1 = fopen(name, "r+");
    FILE* f2 = fopen("f2.txt", "w+");
    FILE* f3 = fopen("f3.txt", "w+");
    if (f1 == NULL || f2 == NULL || f3 == NULL) {
        printf("ОШИБКА\n");
    } else {
        char* str = malloc(MAXLEN + 1);
        int count = 0;
        while (fgets(str, MAXLEN+1, f1) != NULL) {
            
            if (count >= N)
                fputs(str, f2);
            else
                fputs(str, f3);
            count++;
        }
        fclose(f3);
        f3 = fopen("f3.txt", "r+");
        while (fgets(str, MAXLEN+1, f3) != NULL) {
            fputs(str, f2);
        }
        free(str);
        remove(name);
        remove("f3.txt");
        fclose(f1);
        fclose(f2);
        fclose(f3);
        rename("f2.txt", name);
    }
}

void f3(int N, char* name) {
    FILE* f1 = fopen(name, "r+");
    FILE* f2 = fopen("f2.txt", "w+");
    FILE* f3 = fopen("f3.txt", "w+");
    if (f1 == NULL || f2 == NULL || f3 == NULL) {
        printf("ОШИБКА\n");
    } else {
        char* str = malloc(MAXLEN + 1);
        int count = 0;
        int fileCount = 0;
        
        while (fgets(str, MAXLEN+1, f1) != NULL) {
            fileCount++;
        }
        fclose(f1);
        f1 = fopen(name, "r+");
        while (fgets(str, MAXLEN+1, f1) != NULL) {
            
            if (count >= (fileCount - N))
                fputs(str, f2);
            else
                fputs(str, f3);
            count++;
        }
        fclose(f3);
        f3 = fopen("f3.txt", "r+");
        while (fgets(str, MAXLEN+1, f3) != NULL) {
            fputs(str, f2);
        }
        free(str);
        remove(name);
        remove("f3.txt");
        fclose(f1);
        fclose(f2);
        fclose(f3);
        rename("f2.txt", name);
    }
}

int main(int argc, char **argv) {
    int N, f;
    PF functions[3];
    functions[0] = f1;
    functions[1] = f2;
    functions[2] = f3;
    printf("Введите номер функции (первые 2 я успел сдать на паре. Вы не проверили только 3-ю):\n");
    scanf("%d", &f);
    while (f!=0) {
        printf("Введите N\n");
        scanf("%d", &N);
        functions[f-1](N, argv[1]);
        printf("Введите номер функции: (если хотите закончить, введите 0):\n");
        scanf("%d", &f);
    }
    
    return 0;
}
