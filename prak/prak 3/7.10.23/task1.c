#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    long int elem;
    int count;
    struct list* next;
} List;

List* find(List* nums, long int x, int* ans) {
    List* now = nums;
    while (now != NULL) {
        if (now->elem == x) {
            *ans = 1;
            return now;
        } 
        now = now->next;
    }
    return NULL;
}

void DelList(List* p) {
    List* now = p;
    List* nex = NULL;
    while (now != NULL) {
        nex = now->next;
        free(now);
        now = nex;
    }
    p = NULL;
}

int reverse(List** lili) {
    List* new = *lili;
    List* presub = *lili;
    List* sub = NULL;
    List* nextsub = NULL;
    while (new != NULL) {
        new = new->next;
    }
    if (presub->next == NULL) {
        return 0;
    } else {
        sub = presub->next;
        if (sub->next == NULL) {
            sub->next = presub;
            presub->next = NULL; 
        } else {
            nextsub = sub->next;
            presub->next = NULL;
            while (sub->next != NULL) {
                sub->next = presub;
                presub = sub;
                sub = nextsub;
                nextsub = nextsub->next;

            }
            sub->next = presub;
        }
    }
    *lili = sub;
}

int main() {
    List* mainList = NULL;
    List* now = NULL;
    List* sub = NULL;
    //sList* subList = NULL;
    //sList* temp = NULL;
    long int x;
    int c, max, flag = 0;
    if (c = scanf("%ld", &x)!=  EOF) {
        mainList = malloc(sizeof(List));
        mainList->next = NULL;
        mainList->elem = x;
        mainList->count = 1;
        now = mainList;
        while ((c = scanf("%ld", &x)!=  EOF)) {
            sub = find(mainList, x, &flag);
            if (flag != 1) {
                now->next = malloc(sizeof(List));
                now = now->next;
                now->elem = x;
                now->next = NULL;
                now->count = 1;
            } else {
                sub->count++;
                sub = NULL;
                flag = 0;
            }
            
        }
    }
    if (mainList == NULL) {
        return 0;
    }
    putchar('\n');
    now = mainList;
    max = mainList->count;
    while (now != NULL) {
        if (max < now->count) {
            max = now->count;
        }
        now = now->next;
    }
    now = mainList;
    while (now != NULL) {
        if (now->count == max) {
            printf("%ld ", now->elem);
        }
        now = now->next;
    }
    putchar('\n');
    reverse(&mainList);
    now = mainList;
    while (now != NULL) {
        //if (now->count == max) {
            printf("%ld ", now->elem);
        now = now->next;
    }
    now = mainList;
    putchar('\n');
    while (now != NULL) {
            printf("%ld ", now->elem);
            printf("%d", now->count);
            putchar('\n');
        now = now->next;
    }
    DelList(mainList);
}