#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>
// #include <wait.h>
#include <time.h>


typedef struct t1{
    long mestype;
    char mes[100];
} msg;

void h(int c) {
    //signal(SIGUSR1, SIG_DFL);
}

int search_letter(char letter, char* word, char* mass) {
    int len = strlen(word);
    int ans = 0;
    for (int i = 0; i < len; i++) {
        if (word[i] == letter) {
            mass[i] = letter;
            ans = 1;
        } // else {
        //     mass[i] = '0';
        // }
    }
    return ans;
    
}

int check(char* word) {
    int len = strlen(word);
    int ans = 1;
    for (int i = 0; i < len;  i++) {
        if (word[i] == '*') {
            ans = 0;
            return ans;
        }
    }
    return ans;
}


int main() {
    key_t key;
    pid_t p1;
    key = ftok("./game.c", 'c');
    //int mesgid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);

    if ((p1 = fork()) < 0) {
        printf("error fork\n");


    } else if (p1 == 0) {
        // клиент - игрок

        int msgid, x;
        char buf[100];
        msgid = msgget(key, 0666);
        msg res, ans;
        // считали количество букв
        msgrcv(msgid, &res, 100, 2, 0);
        char count_letters = res.mes[0];
        printf("In word %d letters\n", count_letters);
        char word_now[count_letters + 1];
        word_now[count_letters] = '\0';
        // for (int i = 0; i < count_letters; i++) {
        //     word_now[i] = '*';
        // }
        
        for(;;) {
            // игрок дает ответ
            printf("Your answer: \n");
            //fgets(buf, 100, stdin);
            scanf("%s", buf);
            strcpy(ans.mes, buf);
            ans.mestype = 1;
            msgsnd(msgid, &ans, 100, 0);    //отправка ответа
            msgrcv(msgid, &res, 100, 2, 0); // приняли проверку
            if (res.mes[0] != ' ') {
                printf("Yes! You right! Your word now: %s\n", res.mes);
            } else {
                printf("%s\n", res.mes);
            }
            if(strcmp(res.mes, " Win!") == 0 || strcmp(res.mes, " Lose!") == 0) {
                break;
            }
           // интерактивный показ мест где наша буква

           // если выигрыш или проигрыш, то завршится
           //иначе дальше по циклу, проверить выводить надо слово с уже угаданами буквами или нет
        }
        exit(0);
    } 


        // сервер
        // обработка слова для загадки
        int mesgid;
        mesgid = msgget(key, 0666 | IPC_CREAT | IPC_EXCL);
        char* words[] = {"banana", "apple", "improvisator", "vodka", "tomato", "cucumber", "beer", "milk", "kazahstan", "cafe", "cheese", "vulnerability", "algebra", "geometria", "chest"};
        int stime;
        long ltime;
        ltime = time(NULL);
        stime = (unsigned int)ltime/2;
        int number_word = stime % 15;
        char* word = words[number_word];
        int len = strlen(word);
        msg answer;
        msg react;
        answer.mes[0] = len;
        int x, flag = 0;
        //printf("%s\n", word);
        printf("Start game! I generate word for you!\n");


        // отправляем игроку количество букв
        answer.mestype = 2;
        //printf("%c\n", answer.mes[0]);
        msgsnd(mesgid, &answer, 100, 0);
        
        char mass_letters[len + 1];
        mass_letters[len] = '\0';
        for (int i = 0; i < len; i++) {
            mass_letters[i] = '*';
        }

        // начинаем игру

        for(;;) {

            //обработка ответов игрока
            int y = msgrcv(mesgid, &answer, 100, 1, 0);
            
            if (strlen(answer.mes) > 1) {       // если пришло слово
                if (strcmp(word, answer.mes) == 0) {
                    strcpy(react.mes, " Win!");
                } else {
                    strcpy(react.mes, " Lose!");
                    printf("Correct answer: %s\n", word);
                }
                flag = 1;

            } else {                            // если пришла буква
                x = search_letter(answer.mes[0], word, mass_letters);
                if (x == 0) {
                    strcpy(react.mes, " There is no such letter");
                } else {
                    strcpy(react.mes, mass_letters);
                }
            }
            react.mestype = 2;
            msgsnd(mesgid, &react, 100, 0);
            if (flag) {
                break;
            }
        }
        wait(NULL);
        msgctl(mesgid, IPC_RMID, NULL);
        printf("Thank you for game!\n");
        exit(0);
    
}
