// #include <stdio.h>
// #include <stdlib.h>

// void process(struct List *pl, const char *str){
//     struct Node *mainList, *mainList_prev, *mainList_prep, *mainList_rep = pl->last, *m_p;
//     int p=0, flag = 0, flag1=0;
//     mainList = pl->first;
//     if(mainList != NULL){
//         do{
//             mainList_prev = mainList;
//             while(mainList->elem[p] != '\0' && str[p] != '\0' &&(mainList->elem[p] == str[p])){
//                 if(mainList->elem[p] > str[p]){
//                     flag = 1;
//                     break;
//                 }
//                 p++;
//             }
//             if(flag==1){
//                 if(mainList->prev != NULL){
//                     mainList->prev->next = mainList->next;
//                 }
//                 else{
//                     pl->first = pl->first->next;
//                 }
//                 if(mainList->next != NULL){
//                     mainList->next->prev = mainList->prev;
//                 }
//                 mainList_prep = mainList_rep;
//                 mainList_rep->next=malloc(sizeof(struct Node));
//                 mainList_rep = mainList_rep->next;
//                 mainList_rep = mainList;
//                 mainList_prep->next = mainList_rep;
//                 mainList_rep->prev = mainList_prep;
//                 mainList_rep->next = NULL;
//                 flag = 0;
//             }
//             if(mainList->elem[p]==str[p] && flag == 0){
//                 if(mainList->prev != NULL){
//                     mainList->prev->next = mainList->next;
//                 }
//                 else{
//                     pl->first = pl->first->next;
//                 }
//                 if(mainList->next != NULL){
//                     mainList->next->prev = mainList->prev;
//                     mainList_prev = mainList->next;
//                 }
//                 free(mainList->elem);
//                 free(mainList);
//                 mainList = mainList_prev;
//                 m_p = mainList;
//                 if(m_p == pl->last){
//                     flag1 = 1;
//                 }
//                 flag = 1;
//             }
//             if(flag == 0){
//                 m_p = mainList;
//                 mainList =  mainList->next;
//             }
//             flag = 0;
//             p=0;
//         }
//         while(m_p != pl->last);
//         if(flag1 == 1){
//             mainList_prev = mainList;
//             while(mainList->elem[p] != '\0' && str[p] != '\0' &&(mainList->elem[p] == str[p])){
//                 if(mainList->elem[p] > str[p]){
//                     flag = 1;
//                     break;
//                 }
//                 p++;
//             }
//             if(flag==1){
//                 if(mainList->prev != NULL){
//                     mainList->prev->next = mainList->next;
//                 }
//                 else{
//                     pl->first = pl->first->next;
//                 }
//                 if(mainList->next != NULL){
//                     mainList->next->prev = mainList->prev;
//                 }
//                 mainList_prep = mainList_rep;
//                 mainList_rep->next=malloc(sizeof(struct Node));
//                 mainList_rep = mainList_rep->next;
//                 mainList_rep = mainList;
//                 mainList_prep->next = mainList_rep;
//                 mainList_rep->prev = mainList_prep;
//                 mainList_rep->next = NULL;
//                 flag = 0;
//             }
//             if(mainList->elem[p]==str[p] && flag == 0){
//                 if(mainList->prev != NULL){
//                     mainList->prev->next = mainList->next;
//                 }
//                 else{
//                     pl->first = pl->first->next;
//                 }
//                 if(mainList->next != NULL){
//                     mainList->next->prev = mainList->prev;
//                     mainList_prev = mainList->next;
//                 }
//                 free(mainList->elem);
//                 free(mainList);
//                 mainList = mainList_prev;
//                 m_p = mainList;
//                 if(m_p == pl->last){
//                     flag1 = 1;
//                 }
//                 flag = 1;
//             }
//             if(flag == 0){
//                 m_p = mainList;
//                 mainList =  mainList->next;
//             }
//             flag = 0;
//             p=0;
//         }
//         pl->last = mainList_rep;
//     }
// }

