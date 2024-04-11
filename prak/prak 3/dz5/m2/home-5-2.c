//
//  main.c
//  home-5-2
//
//  Created by Егор Мальцев on 08.10.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   2. Для списка слов (список с полем данных char* см. ДЗ-4) написать функции
   a) insert - добавление (вставка) элемента x перед позицией p. При p == 1 , вставка должна происходить в начало списка, перед 1-ым элементом. Если задано p, большее, чем длина списка, добавить элемент в конец списка.
   b) erase - удаление элемента из позиции p (нумерация элементов списка с 1).
   Всю динамически выделенную память освободить.
 */

typedef struct Node {
    char *word;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct Word {
    char letter;
    struct Word *prev;
} Word;

void pushLetter(struct Word **word, char letter) {
    struct Word *node = malloc(sizeof(Word));
    
    node->letter = letter;
    node->prev = *word;
    *word = node;
}

void pushWord(struct Node **list, struct Word *word, int count) {
    struct Node *node = malloc(sizeof(Node));
    char *newWord = malloc(count + 1);
    struct Word *now = word;

    for (int i = 0; i < count; i++) {
        newWord[count - i - 1] = now->letter;
        now = now->prev;
    }
    newWord[count] = '\0';
   
    node->word = newWord;
    node->prev = *list;
    node->next = NULL;

    *list = node;
}

void addNexts(struct Node *list) {
    while (list->prev) {
        (list->prev)->next = list;
        list = (list->prev);
    }
}

void originalPrint(struct Node *list) {
    if (list) {
        printf("%s", list->word);
        if (list->next != NULL) {
            putchar(' ');
        }
        originalPrint(list->next);
    }
}

void delList(struct Node *list) {
    struct Node *now = list;
    struct Node *nex = NULL;

    if (now->prev != NULL) {
        nex = now->prev;
        free(now->word);
        free(now);
        now = nex;
    }
    list = NULL;
}

void delWord(struct Word *word) {
    Word *now = word;
    Word *nex = NULL;

    while (now != NULL) {
        nex = now->prev;
        free(now);
        now = nex;
    }
    word = NULL;
}


void insert(struct Node *list, char *x, int p) {
    int i = 2;
    struct Node *tmp = malloc(sizeof(Node));
    tmp->word = x;
    while (list->prev != NULL)
        list = list->prev;
    if (p < 2) {
        tmp->prev = NULL;
        tmp->next = list;
        list->prev = tmp;
        list = list->prev;
    } else {
        while ((i < p) && list->next != NULL) {
            list = list->next;
            i++;
        }
        if (list->next)
            tmp->next = list->next;
        else
            tmp->next = NULL;
        list->next = tmp;
    }
    
    while (list->next != NULL) {
        (list->next)->prev = list;
        list = (list->next);
    }
}

void eraseF(struct Node** list, int p) {
    if (*list == NULL || p <= 0)
        return;
    struct Node* current = *list;
    for (int i = 1; current != NULL && i < p; i++)
        current = current->next;
    if (current == NULL || (*list == NULL || current == NULL))  {
        printf("Элемента с таким индексом нет\n");
        return;
    }
    if (*list == current)
        *list = current->next;
    if (current->next != NULL)
        current->next->prev = current->prev;
    if (current->prev != NULL)
        current->prev->next = current->next;
    free(current);
}


int main(int argc, const char *argv[]) {
    
    char sym = ' ';
    struct Node *list = NULL;
    struct Word *word = NULL;

    int count = 0;

    printf("Введите слова через пробел(-ы):\n");

    while (!feof(stdin) && (sym != '\n')) {
        scanf("%c", &sym);
        if (sym != '\n') {
            if (sym == ' ' && sym != '\n') {
                if (word != NULL) {
                    pushWord(&list, word, count);
                    delWord(word);
                    word = NULL;
                    count = 0;
                }
                count = 0;
            } else if (sym != '\0') {
                count++;
                pushLetter(&word, sym);
            }
        }
    }
    
    if (word != NULL) {
        pushWord(&list, word, count);
    }

    
    if (list != NULL) {
        addNexts(list);
        printf("Введите слово, которое хотите вставить:\n");
        count = 0;
        sym = '0';
        while (sym != '\n' && sym != '\0' && sym != ' ') {
            scanf("%c", &sym);
            if (sym != '\n' && sym != '\0' && sym != ' ') {
                count++;
                pushLetter(&word, sym);
            }
        }
        struct Word* now = word;
        char *newWord = malloc(count + 1);
        for (int i = 0; i < count; i++) {
            newWord[count - i - 1] = now->letter;
            now = now->prev;
        }
        newWord[count] = '\0';
        if (word != NULL) {
            delWord(word);
            word = NULL;
        }
        
        int p;
        if (*newWord != '\0') {
            printf("Введите номер позиции, в которую хотите вставить %s:\n", newWord);
            scanf("%d", &p);
            printf("Преобразованный список:\n");
            
            insert(list, newWord, p);
        } else {
            printf("Введено пустое слово. Вставлять нечего\n");
        }
        while (list->prev != NULL)
            list = list->prev;
        
        originalPrint(list);
        printf("\n------------------\nВведите номер позиции, на которой хотите удалить элемент:\n");
        scanf("%d", &p);
        eraseF(&list, p);
        originalPrint(list);
        putchar('\n');
        printf("\n------------------\n");
        delWord(word);
        delList(list);
    } else {
        printf("Пустая строка - слов нет\n");
    }
    
    return 0;
}

