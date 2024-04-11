// 2. Читать из стандартного ввода последовательность слов до ввода 
// конца строки '\n’ или до возникновения ситуации EOF. 
// Слова разделяются пробелами (количество подряд идущих пробелов >=1), 
// в начале и в конце строки пробелы тоже возможны, 
// но их наличие не обязательно.
// Длина слов не ограниченна.
// Пользоваться функцией realloc() (и функцией ввода, 
// написанной ранее) при вводе строки нельзя, 
// отрабатываем работу со списками!
// Для хранения слов использовать двунаправленный список с полем данных 
// типа char* . Для формирования отдельных слов тоже использовать список 
// (поле данных char или небольшой массив из char).
// Вывести на экран введенные слова в прямом порядке 
// (относительно порядка ввода) .
// Вывести на экран введенные слова в обратном порядке 
// (относительно порядка ввода) .
// Вывести на экран введенные слова в алфавитном порядке.
// Всю динамически выделенную память освободить.
#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    struct list* prev;
    char* count;
    struct list* next;
} List;

typedef struct list_b {
    char count;
    struct list_b* next;
} List_b;

int main(){
    char c;
    int len_w = 0, first = 0;
    List_b* first_List = NULL;
    List_b* now = NULL;
    List_b* word_s = NULL;
    List* mainList = NULL;
    List* mainList_now = NULL;
    List* mainList_prev = NULL;
    List* mainList_last = NULL;
    char* st;
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
        printf("Прямой ход:\n");
        while(mainList_now != NULL){
            printf("%s ", mainList_now->count);
            mainList_now  = mainList_now->next;
        }
        printf("\n");
        printf("Обратный ход:\n");
        mainList_now = mainList_last;
        while(mainList_now != NULL){
            printf("%s ", mainList_now->count);
            mainList_now  = mainList_now->prev;
        }
        mainList_prev = mainList;
        mainList_now = mainList->next;
        first = 0;
        printf("\n");
        while (mainList_now != NULL){
            int i = 0;
            while(((mainList_now->count)[i]!='\0' && (mainList_prev->count)[i]!='\0') && (mainList_prev->count)[i] == (mainList_now->count)[i]){
                i++;
            }
            if((mainList_now->count)[i]!='\0' && (mainList_prev->count)[i]!='\0' && ((mainList_now->count)[i] < (mainList_prev->count)[i])){
                mainList_prev->next = mainList_now->next;
                mainList_now->prev = mainList_prev->prev;
                if (mainList_prev->prev != NULL){
                    mainList_prev->prev->next = mainList_now;
                }
                if(mainList_now->next != NULL){
                mainList_now->next->prev = mainList_prev;
                }
                mainList_now->next = mainList_prev;
                mainList_prev->prev = mainList_now;

                while(mainList_prev->prev != NULL){
                mainList_prev = mainList_prev->prev;
                }
                mainList = mainList_prev;
                mainList_now = mainList->next;
            }
            else{
                mainList_now = mainList_now->next;
                mainList_prev = mainList_prev->next;
            }
        }
        
        mainList_now = mainList;
        printf("Алфавитный порядок:\n");
        while(mainList_now != NULL){
            printf("%s ", mainList_now->count);
            mainList_now  = mainList_now->next;
        }
        printf("\n");
    }
    else{
        printf("Пустая строка\n");
    }
    now = first_List;
    while(now != NULL){
        word_s = now->next;
        free(now);
        now = word_s;
    }
    // free(first_List);
    // free(now);
    // free(first_List);
    // free(word_s);
    mainList_now = mainList;
    while(mainList_now != NULL){
        mainList_prev = mainList_now->next;
        free(mainList_now->count);
        free(mainList_now);
        mainList_now = mainList_prev;
    }
    // free(mainList);
    // free(mainList);
    // free(mainList_last);
    // free(st);
}