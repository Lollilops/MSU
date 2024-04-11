// #include <stdio.h>
// #include <sys/types.h>
// #include <dirent.h>
// #include <sys/types.h>
// #include <unistd.h>
// #include <sys/stat.h>
// #include <dirent.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>


// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// void p_bit(char num){
//     // printf("%d", num);
//     for(int i=1; i<=8*sizeof(num); i++){
//         if(num >> (8*sizeof(num) - i) & 1){
//             // printf("%d ", i);
//             printf("%d", 1);
//         }
//         else{
//             // printf("%d ", i);
//             printf("%d", 0);
//         }
//     }
// }

// char *prava(int num){
//     char *str = malloc(10);
//     if(num <0 || num > 511){
//         str = "error";
//         return str;
//     }
//     const char *str_pr = "rwxrwxrwx";
//     int i = 1;
//     while(i<=9){
//         if(num >> (9 - i) & 1){
//             str[i-1] = str_pr[i-1];
//         } else {
//             str[i-1] = '-';
//         }
//         i++;
//     }
//     str[i] = '\0';
//     return str;
// }



// int main() {
//     DIR *dir;
//     struct dirent *entry;
    
//     dir = opendir(".");
//     if (!dir) {
//         perror("diropen");
//         exit(1);
//     };
    
//     while ( (entry = readdir(dir)) != NULL) {
//         printf("элемент:\nиндексный дескриптор - %llu\n - название - %s\n тип - %d\n %s\n\n",
//             entry->d_ino, entry->d_name, entry->d_type, prava(entry->d_reclen));
//     };
    
//     closedir(dir);
    
//     return 0;
// };


// //  main.c
// //  mz-8-2

// //  Created by Егор Мальцев on 11.11.2023.

// #include <stdio.h>
// #include <sys/types.h>
// #include <dirent.h>
// #include <unistd.h>
// #include <sys/stat.h>
// #include <stdlib.h>
// #include <string.h>
// #include <math.h>

// void p_bit(char num){
//     for(int i=1; i<=8*sizeof(num); i++){
//         if(num >> (8*sizeof(num) - i) & 1){
//             printf("%d", 1);
//         } else {
//             printf("%d", 0);
//         }
//     }
// }

// char *prava(int num){
//     char *str = malloc(10);
//     if(num <0 || num > 511){
//         str = "error";
//         return str;
//     }
//     const char *str_pr = "rwxrwxrwx";
//     int i = 1;
//     while(i<=9){
//         if(num >> (9 - i) & 1){
//             str[i-1] = str_pr[i-1];
//         } else {
//             str[i-1] = '-';
//         }
//         i++;
//     }
//     str[i] = '\0';
//     return str;
// }

// const char *Type(unsigned char type){
//     switch (type)
//     {
//         case DT_REG:
//             return "Reg";
//         case DT_DIR:
//             return "Dir";
//         case DT_LNK:
//             return "Lnk";
//         case DT_FIFO:
//             return "Fifo";
//         case DT_SOCK:
//             return "Sock";
//         case DT_BLK:
//             return "Blk";
//         case DT_CHR:
//             return "Chr";
//         default:
//             return "Unknown";
//     }
// }

// int main() {
//     DIR *dir;
//     struct dirent *entry;
    
//     dir = opendir(".");
//     if (!dir) {
//         perror("diropen");
//         exit(1);
//     };
    
//     while ( (entry = readdir(dir)) != NULL) {
//         printf("элемент:\nиндексный дескриптор - %lu\n - название - %s\n тип - %s\n %s\n\n",
//             entry->d_ino, entry->d_name, Type(entry -> d_type), prava(entry->d_reclen));
//     };
    
//     closedir(dir);
    
//     return 0;
// };