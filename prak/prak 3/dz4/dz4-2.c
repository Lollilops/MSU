

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elem {
    struct elem* prev;
    char* str;
    struct elem* next;
} Elem1;

typedef struct title_list {
    Elem1* head;
    Elem1* tail;
} STRI;

typedef struct elem_l {
    char sym;
    struct elem_l* next;
} ElemL;

typedef struct one_list {
    int len;
    ElemL* next;
} Olist;


STRI* createDList() {
    STRI* ans = NULL;
    ans = malloc(sizeof(STRI));
    ans->head = NULL;
    ans->tail = NULL;
    return ans;
}

void del_List(STRI *list) {
    Elem1* now = list->head;
    Elem1* next = NULL;
    while (now != NULL) {
        next = now->next;
        free(now->str);
        free(now);
        now = next;
    }
    free(list);
    list = NULL;
}

char* scanWord(char lastsym, char* sym, char* ci) {
    char s, c;
    char* word = NULL;
    Olist* list = malloc(sizeof(Olist));
    list->len = 1;
    list->next = malloc(sizeof(ElemL));
    ElemL* present = list->next;  
    ElemL* next = NULL;
    present->next = NULL;
    present->sym = lastsym;
    while ((c = scanf("%c", &s)!=  EOF) && (s != '\n') && (s != ' ')) {
        list->len++;
        present->next = malloc(sizeof(ElemL));
        present = present->next;
        present->next = NULL;
        present->sym = s;
    }
    *sym = s;
    *ci = c;
    present = list->next;
    word = malloc(sizeof(char)*(list->len + 1));
    for (int i = 0; i < list->len; i++) {
        word[i] = present->sym;
        present = present->next;
    }
    word[list->len] = '\0';
    present = list->next;
    while (present != NULL) {
        next = present->next;
        free(present);
        present = next;
    }
    free(list);    
    return word;
}



int main(void) {
    char* word;
    char c; 
    char s;
    int m=0;
    STRI* words = NULL;
    Elem1* now = NULL;
    Elem1* help = NULL;
    Elem1* p;
    Elem1* g1;
    Elem1* g2;
    words = createDList();
    words->head = malloc(sizeof(Elem1));
    words->tail = words->head;
    now = words->head;
    now->str = NULL;
    now->prev = NULL;
    now->next = NULL;
    c = scanf("%c", &s);
    while ((c != EOF) && (s != '\n')) {
        m+=1;
        while (s == ' ') {
            c = scanf("%c", &s);
        }
        if ((c == EOF) || (s == '\n')) {
            break;
        }
        now->str = scanWord(s, &s, &c);
        now->next = malloc(sizeof(Elem1));
        words->tail = now->next;
        now->next->prev = now;
        now = now->next;
        now->next = NULL;
        now->str = NULL;
    }
    if (m!=0){
    words->tail = now->prev;
    now->prev->next = NULL;
    free(now);
    now = words->head;
    printf("\nПрямой порядок слов\n");
    while (now != NULL) {
        printf("%s ", now->str);
        now = now->next;
    }
    now = words->tail;
    printf("\nОбратный порядок слов\n");
    while(now!= NULL){
        printf("%s ", now -> str);
        now= now -> prev;
    }
    now=words->head;
    if (m==1){
        printf("%s\n", words->head->str);
    }
    else{
        for(int i=1; i<m-1; i++){
            p=now;
            for(int j=i+1; j<m;j++){
                p=p->next;
                if (strcmp(now->str,p->str)>0){
                    word=now->str;
                    now->str=p->str;
                    p->str=word;
                }
            }
            now=now->next;
        }
    }
    now=words->head;
    printf("\nОтсортированный список\n");
    while(now!= NULL){
        printf("%s ", now -> str);
        now= now -> next;
    }
    del_List(words);
    }
    else{
        printf("\n");
    }

}

