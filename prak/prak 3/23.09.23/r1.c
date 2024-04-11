#include <stdio.h>
#include <stdlib.h>
#define piece 4

char* bin(){
    int mas = 0, len = 4;
    char x;
    char *str = NULL;
    while ((x = fgetc(stdin)) != '\n' && x != EOF){
        if (len == piece){
            str = realloc(str, mas+piece);
            mas += piece;
            if (str == NULL){
                printf("Переполнение");
            }
            len = 0;

        }
        *(str + len) = x;
        // printf("%s\n", str);
        len++;
    }
    if (len < piece){
        *(str + len) = '\0';
    }
    else{
        str = realloc(str, mas+piece);
        *(str + len) = '\0';
    }
    return str;
}

int main(){
    char*  str;
    int i;
    // printf("n");
    str = bin();
    printf("n\n");
    if(str != 0){
        printf("%s\n", str);
    while(str[i]!='\0'){
        // printf("%s", str[i]);
        i++;
    }
    }
}
// valgrind --leak-check=full -v ./your_program