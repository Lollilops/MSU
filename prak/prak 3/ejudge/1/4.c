#include <stdio.h>
#include <stdlib.h>

// вместо очищениия надо делать перенос, т. к. при очищении происходит очищение и элемента

struct Node
{
    struct Node *prev, *next;
    char *elem;
};

struct List
{
    struct Node *first, *last;
};

void process(struct List *pl, const char *str){
    struct Node *mainList, *mainList_prev, *mainList_prep, *mainList_rep = pl->last, *m_p;
    int p=0, flag = 0, flag1=0;
    mainList = pl->first;
    if(mainList != NULL){
        do{
            printf("n %s\n", mainList->elem);
            mainList_prev = mainList;
            while(mainList->elem[p] != '\0' && str[p] != '\0' &&(mainList->elem[p] == str[p])){
                if(mainList->elem[p] > str[p]){
                    flag = 1;
                    break;
                }
                p++;
            }
            if(flag==1){
                printf("m1\n");
                if(mainList->prev != NULL){
                    mainList->prev->next = mainList->next;
                }
                else{
                    pl->first = pl->first->next;
                }
                if(mainList->next != NULL){
                    mainList->next->prev = mainList->prev;
                }
                mainList_prep = mainList_rep;
                mainList_rep->next=malloc(sizeof(struct Node));
                mainList_rep = mainList_rep->next;
                mainList_rep = mainList;
                mainList_prep->next = mainList_rep;
                mainList_rep->prev = mainList_prep;
                mainList_rep->next = NULL;
                flag = 0;
            }
            if(mainList->elem[p]==str[p] && flag == 0){
                printf("m2\n");
                if(mainList->prev != NULL){
                    mainList->prev->next = mainList->next;
                }
                else{
                    pl->first = pl->first->next;
                }
                if(mainList->next != NULL){
                    mainList->next->prev = mainList->prev;
                    mainList_prev = mainList->next;
                }
                free(mainList->elem);
                free(mainList);
                mainList = mainList_prev;
                m_p = mainList;
                if(m_p == pl->last){
                    flag1 = 1;
                }
                flag = 1;
            }
            if(flag == 0){
                m_p = mainList;
                mainList =  mainList->next;
                printf("nm %s %s\n", m_p->elem, m_p->elem);
            }
            flag = 0;
            p=0;
        }
        while(m_p != pl->last);
        if(flag1 == 1){
            mainList_prev = mainList;
            while(mainList->elem[p] != '\0' && str[p] != '\0' &&(mainList->elem[p] == str[p])){
                if(mainList->elem[p] > str[p]){
                    flag = 1;
                    break;
                }
                p++;
            }
            if(flag==1){
                printf("m1\n");
                if(mainList->prev != NULL){
                    mainList->prev->next = mainList->next;
                }
                else{
                    pl->first = pl->first->next;
                }
                if(mainList->next != NULL){
                    mainList->next->prev = mainList->prev;
                }
                mainList_prep = mainList_rep;
                mainList_rep->next=malloc(sizeof(struct Node));
                mainList_rep = mainList_rep->next;
                mainList_rep = mainList;
                mainList_prep->next = mainList_rep;
                mainList_rep->prev = mainList_prep;
                mainList_rep->next = NULL;
                flag = 0;
            }
            if(mainList->elem[p]==str[p] && flag == 0){
                printf("m2\n");
                if(mainList->prev != NULL){
                    mainList->prev->next = mainList->next;
                }
                else{
                    pl->first = pl->first->next;
                }
                if(mainList->next != NULL){
                    mainList->next->prev = mainList->prev;
                    mainList_prev = mainList->next;
                }
                free(mainList->elem);
                free(mainList);
                mainList = mainList_prev;
                m_p = mainList;
                if(m_p == pl->last){
                    flag1 = 1;
                }
                flag = 1;
            }
            if(flag == 0){
                m_p = mainList;
                mainList =  mainList->next;
                printf("nm %s %s\n", m_p->elem, m_p->elem);
            }
            flag = 0;
            p=0;
        }
        pl->last = mainList_rep;
    }
}

int main(){
    struct Node *mainlol=NULL, *mainlol_d=NULL, *main_ll;
    struct List *mainList_lol;
    int p=0, x;
    char* str_t;
    for(int i=48; i<53; i++){
        if(mainlol == NULL){
            str_t = malloc(8+1);
            scanf("%d", &x);
            str_t[p] = x;
            p++;
            str_t[p] = '\0';
            // p++;
            mainlol = malloc(sizeof(struct Node));
            mainlol->elem = str_t;
            // printf("%s\n", mainlol->elem);
            mainlol->prev = NULL;
            mainlol->next = NULL;
            mainlol_d = mainlol;
        }
        else{
            p = 0;
            str_t = malloc(9);
            scanf("%d", &x);
            str_t[p] = x;
            p++;
            str_t[p] = '\0';
            // p++;
            // printf("%s %d\n", mainlol_d->elem, i);
            mainlol_d->next = malloc(sizeof(struct Node));
            // main_ll = mainlol_d;
            mainlol_d->next->prev = mainlol_d;
            mainlol_d = mainlol_d->next;
            mainlol_d->elem = str_t;
            // mainlol_d->prev = main_ll;
            // printf("%s %s\n", mainlol_d->prev->elem, mainlol_d->elem);
            mainlol_d->next = NULL;
        }
    }
    // mainlol_d = mainlol;
    // while(mainlol_d != NULL){
    //     printf("%s\n", mainlol_d->elem);
    //     mainlol_d = mainlol_d->next;
    // }
    mainList_lol = malloc(sizeof(struct List));
    mainList_lol->first = mainlol;
    mainList_lol->last = mainlol_d;
    
    // str_t = malloc(8+1);
    // str_t[0] = 50;
    // str_t[1] = '\0';
    // printf("%s", str_t);
    mainlol_d = mainList_lol->first;
    while(mainlol_d != NULL){
        printf("%s\n", mainlol_d->elem);
        mainlol_d = mainlol_d->next;
    }
    str_t = malloc(8+1);
    printf("-----\n");
    scanf("%d", &x);
    str_t[0] = x;
    str_t[1] = '\0';
    // printf("%s\n", str_t);
    process(mainList_lol, str_t);
    mainlol_d = mainList_lol->first;
    while(mainlol_d != NULL){
        printf("nn %s\n", mainlol_d->elem);
        mainlol_d = mainlol_d->next;
    }
}

// if(mainList_rep == NULL){
//     mainList_rep = malloc(sizeof(struct Node));
//     // *(mainList_rep->elem) = *(mainList->elem);
//     mainList_rep->elem = mainList->elem;
//     // printf("nnn %s\n", mainList_rep->elem);
//     mainList_rep->next = NULL;
//     mainList_rep->prev = NULL;
//     mainList_prep = mainList_rep;
// }
// else{
//     printf("%s", mainList_rep->elem);
//     mainList_prep->next = malloc(sizeof(struct Node));
//     mainList_prep->next->prev = mainList_prep;
//     mainList_prep = mainList_prep->next;
//     // *(mainList_prep->elem) = *(mainList->elem);
//     mainList_prep->elem = mainList->elem;
//     // printf("nnn %s\n", mainList_prep->elem);
//     mainList_prep->next = NULL;
// }