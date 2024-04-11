// 1. Написать функцию, определяющую первое вхождение подстроки в строку.
// Параметры — указатели на char (строка и подстрока) .
// Строка и подстрока могут быть и пустыми, т. е. состоять из одного \0.
// Возвращать адрес начала первого вхождения, либо NULL, если подстрока в строку не входит. 
// Стандартные функции для работы со строками использовать запрещено.
// В main() ввести 2 строки (использовать вашу функцию для ввода строк), и вызывать функцию поиска, 
// чтобы найти все вхождения подстроки в строку.
// Для каждого вызова выводить на экран результат как строку - «хвост» исходной, 
// если вхождений больше нет, вывести сообщение.

#include <stdio.h>
#include <stdlib.h>
#define piece 4

char* bin(){
    int mas = 0, len = 4;
    char x;
    char *str = NULL;
    while ((x = fgetc(stdin)) != '\n' && x != EOF){
        if (len == piece){
            str = realloc(str, mas + piece);
            mas += piece;
            if (str == NULL){
                printf("Переполнение");
                return NULL;
            }
            len = 0;
            // printf("%d\n", mas);
        }
        *(str + mas + len - 4) = x;
        len++;
    }
    // printf("%d, %s\n", len, str);

    if (len < piece){
        *(str + mas + len - 4) = '\0';
    }
    else{
        str = realloc(str, mas+1);
        *(str + mas + len - 4) = '\0';
    }
    // gggg
    return str;
}

void enter(char *st,char *st_t){
    // printf("%s\n", st);
    char *ptr = NULL; // , *ptr1 = st_t;
    int flag = 0, len = 0, len1 = 0;
    while (st[len]  != '\0'){
        // printf("%d\n", st[len]);
        if(st[len] == st_t[len1]){
            len1 ++;
            // printf("n\n");
            if (st_t[len1] == '\0'){
                // flag = len - len1;
                // while (st[flag] !=  '\0'){
                //     printf
                // }
                flag = 1;
                ptr = (st + len - len1 + 1);
                printf("%s\n", ptr);
                len = len - len1 + 1;
                len1 = 0;
            }
            else{
                if(st_t[len1] != st[len + 1]){// ggfgfg
                    len1 = 0;
                }
            }
        }
        // else{
        //     len1 = 0;
        // }
        len ++;
        // printf("%d\n", st[len]);
    }
    if (flag == 0){
        printf("NULL\n");
    }
    printf("---------\nВхождений больше нет\n");
}

int main(){
    char *st = NULL, *s_st = NULL;
    printf("Введите строку:\n");
    st = bin();
    printf("Введите подстроку:\n");
    // printf("%s\n", st);
    s_st = bin();
    printf("---------\n");
    // printf("%s, %s\n", st, s_st);
    enter(st, s_st);
    free(st);
    free(s_st);
}