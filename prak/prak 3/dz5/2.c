// 2. Для списка слов (список с полем данных char* см. ДЗ-4) написать функции
// a) insert - добавление (вставка) элемента x перед позицией p. При p == 1 ,
//  вставка должна происходить в начало списка, перед 1-ым элементом. 
// Если задано p, большее, чем длина списка, добавить элемент в конец списка.
// b) erase - удаление элемента из позиции p (нумерация элементов списка с 1).
// Всю динамически выделенную память освободить.

#include <stdio.h>
#include <stdlib.h>
#define piece 4

typedef struct list {
    struct list* prev;
    char* count;
    struct list* next;
} List;

typedef struct list_b {
    char count;
    struct list_b* next;
} List_b;

char* str_strem(){
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

List *insert(List* mainList, char *elem, int p){
    List *mainList_now = mainList, *mainList_rep = NULL, *mainList_next = NULL;
    int numb = 0;
    if(p >= 1){
        if (mainList == NULL){
        mainList = malloc(sizeof(List));
        mainList->count = elem;
        mainList->next = NULL;
        mainList->prev = NULL;
        }
        else{
            mainList_rep = malloc(sizeof(List));
            mainList_rep->count = elem;
            p--;
            while ((mainList_now != NULL) && (numb != p + 1)){
                if (numb == p){
                    mainList_next = mainList_now;
                    if(p != 0){
                        mainList_now = mainList_now->prev;
                        mainList_now->next = mainList_rep;
                        mainList_rep->next = mainList_next;
                        mainList_next->prev = mainList_rep;
                        mainList_rep->prev = mainList_now;
                    }
                    else{
                        mainList_rep->next = mainList_now;
                        mainList_rep->prev = NULL;
                        mainList_now->prev = mainList_rep;
                        mainList = mainList_rep;
                    }
                }
                numb ++;
                if(mainList_now->next == NULL){
                    mainList_next = mainList_now;
                }
                mainList_now = mainList_now->next;
            }
            if(numb <= p){
                mainList_now = mainList_next;
                mainList_now->next = malloc(sizeof(List));
                mainList_now = mainList_now->next;
                mainList_now->count = elem;
                mainList_now->next = NULL;
                mainList_now->prev = mainList_next;
                free(mainList_rep);
            }
        }
    }
    else{
        printf("--Invalid number--\n");
        free(elem);
    }
    return mainList;
}

List *erase(List* mainList, int p){
    List *mainList_now = mainList, *mainList_rep = NULL, *mainList_next = NULL;
    int numb = 0;
    if(p >= 1){
        p--;
        while ((mainList_now != NULL) && (numb != p + 1)){
            if (numb == p){
                if(p != 0){
                    mainList_rep = mainList_now;
                    mainList_next = mainList_now->next;
                    mainList_now = mainList_now->prev;
                    mainList_now->next = mainList_next;
                    if (mainList_next != NULL){
                        mainList_next->prev = mainList_now;
                    }
                    free(mainList_rep->count);
                    free(mainList_rep);
                }
                else{
                    mainList_rep = mainList_now;
                    if(mainList_now->next != NULL){
                        mainList_now = mainList_now->next;
                        mainList = mainList_now;
                        mainList->prev=NULL;
                        free(mainList_rep->count);
                        free(mainList_rep);
                    }
                    else{
                        mainList = mainList_now;
                        free(mainList_rep->count);
                        free(mainList_rep);
                        mainList = NULL;
                    }
                }
            }
            numb ++;
            if(mainList != NULL && mainList_now->next == NULL){
                mainList_next = mainList_now;
            }
            if(mainList != NULL){
                mainList_now = mainList_now->next;
            }
        }
        if(numb <= p){
            printf("--Invalid number(нет элемента c таким номером)--\n");
        }
    }
    else{
        printf("--Invalid number(нет элемента c таким номером)--\n");
    }
    return mainList;
}

int main(){
    char c;
    int len_w = 0, first = 0, p;
    List_b* first_List = NULL;
    List_b* now = NULL;
    List_b* word_s = NULL;
    List* mainList = NULL;
    List* mainList_now = NULL;
    List* mainList_prev = NULL;
    List* mainList_last = NULL;
    char* st, *elem = NULL;
    printf("Введите список слов:\n");
    if ((c = fgetc(stdin)) != '\n' && c!=EOF){
        first_List = malloc(sizeof(List_b));
        first_List->next = NULL;
        first_List->count = c;
        now = first_List;
        while ((c = fgetc(stdin)) != '\n' && c!=EOF){
            now->next = malloc(sizeof(List_b));
            now = now->next;
            now->next = NULL;
            now->count = c;
        }
        now = first_List;
        word_s = first_List;
        while(word_s->count == ' '){
            word_s = word_s->next;
            now = now->next;
        }
        while(now != NULL){
            len_w += 1;
            if ((now->count == ' ') || (now->next == NULL)){
                if (first == 0){
                    mainList = malloc(sizeof(List));
                    st = malloc(8 * len_w + 1);
                    int i = 0;
                    while (word_s != now){
                        st[i] = word_s->count;
                        i++;
                        word_s = word_s->next;
                    }
                    if (now->next == NULL){
                        st[i] = word_s->count;
                        i++;
                    }
                    st[i]='\0';
                    mainList->count = st;
                    mainList->next = NULL;
                    mainList->prev = mainList_prev;
                    mainList_prev = mainList;
                    mainList_now = mainList;
                    len_w = 0;
                    if(now->next != NULL){
                        while(now->next->count == ' '){
                            now = now->next;
                            word_s = word_s->next;
                        }
                        word_s = word_s->next;
                    }
                    first = 1;
                }
                else{
                    mainList_now->next = malloc(sizeof(List));
                    mainList_now = mainList_now->next;
                    st = malloc(8 * len_w + 1);
                    int i = 0;
                    while (word_s != now){
                        st[i] = word_s->count;
                        i++;
                        word_s = word_s->next;
                    }
                    if (now->next == NULL){
                        st[i] = word_s->count;
                        i++;
                    }
                    st[i]='\0';
                    mainList_now->count = st;
                    mainList_now->next = NULL;
                    mainList_now->prev = mainList_prev;
                    mainList_prev = mainList_now;
                    len_w = 0;
                    if(now->next != NULL){
                        while(now->next->count == ' '){
                            now = now->next;
                            word_s = word_s->next;
                        }
                        word_s = word_s->next;
                    }
                }
            }
            now = now->next;
        }
        mainList_last = mainList_now;
        mainList_now = mainList;
    }

    printf("Прямой ход:\n");
    while(mainList_now != NULL){
        printf("%s ", mainList_now->count);
        mainList_now  = mainList_now->next;
    }
    printf("\n");
    printf("Введите элемент:\n");
    elem =  str_strem();
    printf("Введите значение p для добавления элемента:\n");
    scanf("%d", &p);
    // printf("%s\n", elem);
    if(*elem != '\0'){
        mainList = insert(mainList, elem, p);
    }
    else{
        free(elem);
    }
    mainList_now = mainList;
    printf("Прямой ход:\n");
    while(mainList_now != NULL){
        printf("%s ", mainList_now->count);
        mainList_now  = mainList_now->next;
    }
    printf("\n");
    printf("Обратный ход:\n");
    mainList_now = mainList;
    while(mainList != NULL && mainList_now->next != NULL){
        mainList_now = mainList_now->next;
    }
    while(mainList_now != NULL){
        printf("%s ", mainList_now->count);
        mainList_now  = mainList_now->prev;
    }
    printf("\n");

    printf("Введите значение p для удаления элемента:\n");
    scanf("%d", &p);
    mainList = erase(mainList, p);
    mainList_now = mainList;
    printf("Прямой ход:\n");
    while(mainList_now != NULL){
        printf("%s ", mainList_now->count);
        mainList_now  = mainList_now->next;
    }
    printf("\n");
    printf("Обратный ход:\n");
    mainList_now = mainList;
    while(mainList != NULL && mainList_now->next != NULL){
        mainList_now = mainList_now->next;
    }
    while(mainList_now != NULL){
        printf("%s ", mainList_now->count);
        mainList_now  = mainList_now->prev;
    }
    printf("\n");

    now = first_List;
    while(now != NULL){
        word_s = now->next;
        free(now);
        now = word_s;
    }
    mainList_now = mainList;
    while(mainList_now != NULL){
        mainList_prev = mainList_now->next;
        free(mainList_now->count);
        free(mainList_now);
        mainList_now = mainList_prev;
    }
}