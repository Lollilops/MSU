#include <stdio.h>
#include <stdlib.h>

typedef struct list{
    struct list* r;
    int data;
    struct list* l;
} List;

void print_s(List* search){
    if (search->l != NULL){
        print_s(search->l);
    }
    printf("%d ", search->data);
    if(search->r != NULL){
        print_s(search->r);
    }
}

void del_tree(List* search){
    if (search->l != NULL){
        del_tree(search->l);
    }
    if(search->r != NULL){
        del_tree(search->r);
    }
    free(search);
}

int search_tree(List* search, int c){
    int flag = 0, way = 0;
    while(flag != 1){
                if(c >= search->data){
                    if(c == search->data){
                        return way;
                    }
                    if(search->r != NULL){
                        search = search->r;
                    }
                    else{
                        return -1;
                    }
                }
                else{
                    if(search->l != NULL){
                        search = search->l;
                    }
                    else{
                        return -1;
                    }
                }
            way ++;
            }
}

void add_tree(List* search, int c){
    int flag = 0;
    while(flag != 1){
                if(c >= search->data){
                    if(search->r != NULL){
                        search = search->r;
                    }
                    else{
                        search->r = malloc(sizeof(List));
                        search = search->r;
                        search->data = c;
                        search->l = NULL;
                        search->r = NULL;
                        flag = 1;
                    }
                }
                else{
                    if(search->l != NULL){
                        search = search->l;
                    }
                    else{
                        search->l = malloc(sizeof(List));
                        search = search->l;
                        search->data = c;
                        search->l = NULL;
                        search->r = NULL;
                        flag = 1;
                    }
                }
            }
}

// void del_elem_t(List* search, int c){
//     int flag = 0, flag1 = 0;
//     List* search_prev = search;
//     while(flag != 1){
//                 if(c >= search->data){
//                     if(c == search->data){
//                         List* search_del = search_prev;
//                         if(search_del->l != NULL){
//                             search_del = search_del->l;
//                             while(search_del->r != NULL){
//                                 search_del = search_del->r;
//                             }
//                             search_prev
//                         }
//                     }
//                     if(search->r != NULL){
//                         search_prev = search;
//                         search = search->r;
//                         flag1 = 1;
//                     }
//                     else{
//                         flag = 1;
//                     }
//                 }
//                 else{
//                     if(search->l != NULL){
//                         search_prev = search;
//                         search = search->l;
//                         flag1 = 0;
//                     }
//                     else{
//                         flag = 1;
//                     }
//                 }
//             }
// }

int main(){
    List* mainList;
    List* search;
    int c, x;
    printf("Введите число:\n");
    scanf("%d\n", &x);
    printf("Введите дерево:\n");
    if((scanf("%d", &c)) != EOF){
        mainList = malloc(sizeof(List));
        mainList->data = c;
        mainList->r = NULL;
        mainList->l = NULL;
        search = mainList;
        while ((scanf("%d", &c)) != EOF){
            add_tree(search, c);
            // printf("%d", search->data);
            search = mainList;
        }
        print_s(search);
        printf("\n");
        x = search_tree(search, x);
        printf("Длина:\n");
        printf("%d\n", x);

        del_tree(search);
    }
}
// 5 4 6 3 7 2 8 1 9