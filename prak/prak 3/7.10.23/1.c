#include <stdio.h>
#include <stdlib.h>

typedef struct st { long data; struct st *next;} List;
long main(){
    long x;
    List* p = NULL;
    List* n = NULL;
    if (scanf("%ld", &x) != EOF){
        p=malloc(sizeof(struct st));
        p->next = NULL;
        p->data = x;
        // p->count = 1;
        n = p;
        while (scanf("%ld", &x) != EOF){
            n->next=(struct st*)malloc(sizeof(struct st));
            n = n->next;
            n->data=x; n->next=NULL;
            // now->next = malloc(sizeof(List));
            // now = now->next;
            // now->elem = x;
            // now->next = NULL;
            // now->count = 1;
        }
    }
    
    while(p!=NULL) { /* печать строки */
        printf("%ld\n", p->data);
        p=p->next;
    }
}
// 2 NUl / 
// struct st { char c;
//                struct st *s;
// } *p,*n;
//     p=n=NULL;
//     while((q=getchar())!=’\n’) {
//          /* построение стека */
//          n=(struct st*)malloc(sizeof(struct st));
//          n->c=q; n->s=p;
//          p=n;
//     }
//     while(n!=NULL) { /* печать строки */
//          printf(“%c”,n->c);
// n=n->s;

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
 
// typedef struct Node {
//     long int data;
//     struct Node* next;
// } Node;

// void push(Node** list, const long int data) {
//     Node* node = malloc(sizeof(Node));
//     node->data = data;
//     node->next = *list;
//     *list = node;
// }

// void print(const Node* list) {
//     if (list) {
//         printf("%ld ", list->data);
//         print(list->next);
//     }
// }

// void reverse(struct Node ** head) {
//     if (*head == NULL) return;
//     struct Node * curr, *next, *prev = NULL;
//     curr = *head;
//     while(curr) {
//         next = curr->next;
//         curr->next = prev;
//         prev = curr;
//         curr = next;
//     }
//     *head = prev;
// }

// int main(int argc, const char *argv[]) {
//     Node* list = NULL;
//     long int sym;
    
//     scanf("%ld", &sym);
    
//     while (!feof(stdin)) {
//         push(&list, sym);
//         scanf("%ld", &sym);
//     }
    
//     print(list);
//     putchar('\n');
    
//     reverse(&list);
//     print(list);
//     putchar('\n');
    
//     return 0;
// }