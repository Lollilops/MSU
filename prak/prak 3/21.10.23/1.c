#include <stdio.h>
#include <stdlib.h>

typedef struct Word {
    char *count;
    struct Word *next;
} List;

// FILE *change_f(FILE*F, int n){

// }

FILE *del_f(FILE *F, int n){
    n++;
    List *mainlist = NULL, *help_list = NULL;
    int maxlen = 80, flag = 0, prev;
    int count = 0, len_n = 0;
    char  now = '\0';
    char* list_count = malloc(8*maxlen + 1);
    // printf("%c\n",fgetc(F));
    while ((prev = fgetc(F)) != EOF) {
        // printf("%c", prev);
        if (prev == '\n') {
            // printf("n %s, %d, %d, %d", list_count, len_n, count, flag);
            if (count ==  0 && flag == 0){
                mainlist = malloc(sizeof(List));
                mainlist->count = list_count;
                mainlist->next = NULL;
                help_list = mainlist;
                count++;
            }
            else{
                if (flag == 0){
                    // printf("nnnnnnnn\n");
                    help_list->next = malloc(sizeof(List));
                    // printf("n\n");
                    help_list = help_list->next;
                    help_list->count = list_count;
                    // printf("%s\n", list_count);
                    help_list->next = NULL;
                    count++;
                }
            }
            len_n = 0;
            flag = 0;
            list_count = malloc(8*maxlen + 1);
        }
        else{
            // printf("%c, %d, %d, %d\n", prev, len_n, count, flag);
            list_count[len_n] = prev;
            len_n ++;
            if (len_n == n){
                flag = 1;
            }
        }
    }
    // printf("n %s, %d, %d, %d", list_count, len_n, count, flag);
    if (count ==  0 && flag == 0){
        mainlist = malloc(sizeof(List));
        mainlist->count = list_count;
        mainlist->next = NULL;
        help_list = mainlist;
    }
    else{
        if (flag == 0){
            // printf("nnnnnnnn\n");
            help_list->next = malloc(sizeof(List));
            // printf("n\n");
            help_list = help_list->next;
            help_list->count = list_count;
            // printf("%s\n", list_count);
            help_list->next = NULL;
        }
        else{
            free(list_count);
        }
    }
    count++;
    len_n = 0;
    flag = 0;
    fclose(F);
    F = fopen("/media/psf/Home/VisualcodeProjects /prak/21.10.23/file.txt", "w");
    help_list = mainlist;
    while(help_list != NULL){
        fputs(help_list->count, F);
        if(help_list->next != NULL){
            fputc('\n', F);
        }
        help_list = help_list->next;
    }
    fclose(F);
    List *help2 = NULL;
    help_list = mainlist;
    while(help_list != NULL){
        help2 = help_list->next;
        free(help_list->count);
        free(help_list);
        help_list= help2;
    }
}

int main(int argc, const char *argv[]) {
    FILE *F;
    int n = 5;

    if ((F = fopen("/media/psf/Home/VisualcodeProjects /prak/21.10.23/file.txt", "r")) == NULL) {
        printf("ERROR\n");
        return 1;
    }

    F = del_f(F, n);

    return 0;
}
