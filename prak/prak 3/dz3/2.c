// Написать функцию удаления из строки S1 подстроки S2.
// Пример: S1: «string1+string2+string3» S2: «string» => S1: «1+2+3»
// В main() ввести строки, вызвать функцию изменения строки, 
// вывести результат на экран.

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

char  *enter(char *st,char *st_t){
    // printf("%s\n", st);
    char *ptr1 = NULL;
    int flag = 0, len_0 = 0, len1 = 0, mas = 0, len = 4;;
    while (st[len_0]  != '\0'){
        // printf("%d %d\n", st[len_0], st_t[len1]);
        if(st[len_0] == st_t[len1]){
            len1 ++;
            // printf("n\n");
            if (st_t[len1] == '\0'){
                // flag = len - len1;
                // while (st[flag] !=  '\0'){
                //     printf
                // }
                flag = 1;
                len1 = 0;
            }
            else{
                if(st_t[len1] != st[len_0 + 1]){// str1+str2+str3
                    len1 = 0;
                }
            }
        }
        else{
            len1 = 0;
            if (len == piece){
                ptr1 = realloc(ptr1, mas + piece);
                mas += piece;
                len = 0;
            // printf("%d\n", mas);
            }
            *(ptr1 + mas + len - 4) = st[len_0];
            len++;
        }
        len_0 ++;
        // printf("%d\n", st[len]);
    }
    free(st);
    if (flag == 0){
        // printf("NULL\n");
        return NULL;
    }
    else{
        if (len < piece){
            *(ptr1 + mas + len - 4) = '\0';
        }
        else{
            ptr1 = realloc(ptr1, mas+1);
            *(ptr1 + mas + len - 4) = '\0';
        }
        return ptr1;
    }
}


int main(){
    char *st = NULL, *st_t = NULL;
    printf("Введите строку:\n");
    st = bin();
    printf("Введите подстроку:\n");
    st_t = bin();
    // printf("%s %s", st, st_t);
    printf("---------\n");
    if (st[0] != '\0' && st_t[0] != '\0'){
        st = enter(st, st_t);
        printf("%s\n", st);
    }
    else{
        printf("NULL\n");
    }
    free(st);
    free(st_t);
}
