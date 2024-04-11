#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
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
char *change(char *s) { 
    char *p, *s1, *s2; 
    p=malloc(strlen(s)+1); 
    s1=malloc(1); 
    s1=malloc(1); 
    int flag=0, j=0, s1f=1, s2f=1, k=0 ; 
    for (int i=0; i<strlen(s); i++) { 
        if (*(s+i)==' ') { 
            if (k!=0) { 
                s1f=0; 
                *(s1+k)='\0'; 
                } 
            if (flag) { 
            continue; 
            } 
            *(p+j)=' '; 
            flag=1; 
            j++; 
            continue; 
        } 
        if (flag) { 
        flag=0; 
        } 
        *(p+j)=*(s+i); 
        if (s1f) { 
            *(s1+k)=*(p+j); 
            k++; 
            s1=realloc(s1, k+1); 
        } 
        else {
            *(p+j)=*(s+i);
            j++;
        }

    }
    printf("\n%s\n", s1);
    return p;


}

int main(){
    char *s;
    s=read();
    printf("\n%s\n", s);
    s=change(s);
    printf("\n%s\n", s);
    free(s);
    return 0;
}
