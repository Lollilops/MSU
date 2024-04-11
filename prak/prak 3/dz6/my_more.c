// 1. Написать программу, работающую подобно команде more, 
// которая осуществляет вывод файла на экран порциями по 
// нажатию клавиши <пробел> (можете выбрать любую).
// Нажатие <q> - прервать работу (дальше не выводить файл).
// more [-s] [-num] [+linenum] файл
// Опции:
// -s – предписывает заменять последовательность пустых строк одной пустой строкой.
// -num - целое число задает количество выводимых за один раз строк.
// Длина одной порции по умолчанию, т.е. 
// в том случае, если эта опция не задана, 10 строк.
// +linenum - начать вывод со строки с номером linenum (целое число >=1)
// Порядок опций определен, 
// любая из них (в том числе и все) при запуске программы может отсутствовать.
// Примеры вызова: > ./my_more -s -6 +10 file
// > ./my_more -16 file
// > ./my_more file
// Пример перевода терминала в неканонический режим, 
// чтобы нажатие клавиши передавалось в программу сразу без ввода '\n'.
//  Использовать не обязательно, но можно при желании.
// #include <stdio.h>
// #include <termios.h>
// #include <unistd.h>
// int main(int argc, char** argv) {
// static struct termios oldt, newt;
// tcgetattr(STDIN_FILENO, &oldt); // сохранение текущего режима
// newt = oldt;
// newt.c_lflag &= ~(ICANON);
// tcsetattr(STDIN_FILENO, TCSANOW, &newt); // изменение
// char c;
// while (c != 'q') {
// c = getchar();
// printf("==%c\n", c);
// }
// tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // восстановление исходного режима
// return 0;
// }
// Кузина Л.Н.

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char** argv) {
    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // сохранение текущего режима
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // изменение
    char c, *name, str;
    int s=0, num=10, linenum=1, count = 0, check, zeroline = 0;
    FILE* f1 = NULL;
    for(int i=1; i<argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 's'){
            s = 1;
        }
        else{
            if(argv[i][0] == '-'){
                int j = 1;
                num = 0;
                while (argv[i][j] != '\0'){
                    num = num*10 + (argv[i][j] - 48);
                    j++;
                }
            }
        }
        if(argv[i][0] == '+'){
            int j = 1;
            linenum = 0;
            while (argv[i][j] != '\0'){
                linenum = linenum*10 + (argv[i][j] - 48);
                j++;
            }
        }
        if(i == argc-1){
            name = argv[i];
            if ((f1 = fopen(argv[i], "r")) == NULL) {
                printf("ERROR\n");
                return 1;
            }
        }
    }
    //
    while (count < linenum - 1) {
        str = fgetc(f1);
        while ((str != '\n')) {
            str = fgetc(f1);
        }
        count++;
    }
    while ((c = getchar()) != 'q') {
        putchar('\n');
        count = 0;
        while (count < num) {
            if ((check = fscanf(f1, "%c", &str)) == EOF) {
                break;
            }
            if (s == 1) {
                if ((str  == '\n') && (zeroline == 0)){
                    zeroline = 1;
                    putchar('\n');
                    count++;
                } else if ((str != '\n')) {
                        zeroline = 0;
                        while ((str != '\n')) {
                            putchar(str);
                            str = fgetc(f1);
                        }
                        putchar('\n');
                        count++;
                }
            } else {
                while ((str != '\n')) {
                    putchar(str);
                    str = fgetc(f1);
                }
                putchar('\n');
                count++;
            }
        }
    }
    fclose(f1);
    printf("\n");
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // восстановление исходного режима
    return 0;
}