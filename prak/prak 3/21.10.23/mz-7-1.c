#include <stdio.h>

int main(int argc, const char *argv[]) {
    FILE *F;
    int count = 0;
    char prev, now = '\0';

    if ((F = fopen("/Users/george/Documents/c-project/mz-6-1/fileegor.txt", "r")) == NULL) {
        printf("ERROR\n");
        return 1;
    }
    
    while ((prev = fgetc(F)) != EOF) {
        now = prev;

        if (prev == '\n') {
            count++;
        }
    }

    if (now != '\n') {
        count++;
        fputc('\n', F);
    }

    printf("%d\n", count);
    return 0;
}
