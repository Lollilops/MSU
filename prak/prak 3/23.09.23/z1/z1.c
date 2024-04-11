#include <stdio.h> 
#include <stdlib.h> 
#define n 4 
char *read( ) { 
    char *p; 
    int i=0; 
    p=malloc(n); 
    while (((*(p+i))=getchar())!='\n' && (*(p+i))!=EOF) { 
        i++; 
        if (i%4==0) {
            p=realloc(p,n*((i/4)+1));
            if (p==NULL) {
            return 0;
            }
        }
    }
    *(p+i)='\0';
    return p;
    }

int main(){
    char *s;
    s=read();
    printf("%s\n", s);

    return 0;
}                                                                            
