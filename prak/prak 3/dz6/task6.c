#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char** argv) {
    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // сохранение текущего режима
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // изменение
    FILE* file = fopen(argv[argc - 1], "r+");
    if (file == NULL) {
        printf("error\n");
        return 1;
    }
    int zeroline = 0;
    char c, sym;
    int check, flag = 0;
    int linenum = 0;
    int countlines = 10;
    int count = 0;
    switch (argc) {
    case 5:
        countlines = -atoi(argv[2]);
        linenum = atoi(argv[3]);
        flag = 1;
        break;
    case 4:
        if (strcmp(argv[1], "-s") == 0){
            flag = 1;
            check = atoi(argv[2]);
            if (check < 0) {
                countlines = -check;
            } else {
                linenum = check;
            }
        } else {
            countlines = -atoi(argv[1]);
            linenum = atoi(argv[2]);
        }
        break;
    case 3:
        if (strcmp(argv[1], "-s") == 0){
            flag = 1;
        } else {
            check = atoi(argv[1]);
            if (check < 0) {
                countlines = -check;
            } else {
                linenum = check;
            }
        }
        break;
    case 2:
    }
    // count 
    while (count < linenum - 1) {
        sym = fgetc(file);
        while ((sym != '\n')) {
            sym = fgetc(file);
        }
        count++;
    }
    while ((c = getchar()) != 'q') {
        putchar('\n');
        count = 0;
        while (count < countlines) {
            if ((check = fscanf(file, "%c", &sym)) == EOF) {
                break;
            }
            if (flag == 1) {
                if ((sym  == '\n') && (zeroline == 0)){
                    zeroline = 1;
                    putchar('\n');
                    count++;
                } else if ((sym != '\n')) {
                        zeroline = 0;
                        while ((sym != '\n')) {
                            putchar(sym);
                            sym = fgetc(file);
                        }
                        putchar('\n');
                        count++;
                }
            } else {
                while ((sym != '\n')) {
                    putchar(sym);
                    sym = fgetc(file);
                }
                putchar('\n');
                count++;
            }
        }
    }
    fclose(file);
    putchar('\n');
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // восстановление исходного режима
    return 0;
}