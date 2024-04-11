#include <stdio.h>
#include <stdlib.h>

int main(){
    char s;
    scanf("%c", &s);
    while(s != '\0' && s != EOF){
        printf("%c", s);
        fflush(stdout);
        scanf("%c", &s);
        if(s == '1'){
            break;
        }
    }
    printf("\n");
    return 0;
}