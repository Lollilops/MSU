#include <stdio.h>
#include <stdlib.h>

// int main(){
// int x;

// scanf("%d", &x);

// for(int c = 0; c < x; c++){
//     for(int a = 1; a < x; a++){
//         for(int b = 0; b < x; b++){
//             if((a*b)%x == c){
//                 printf("%d ", b);
//             }
//         }
//     }
//     printf("\n");
// }
// }

int func(unsigned char *arr, int max, int numb) {
    if (numb > max) {
        return -1;
    }

    int index = numb / 8;

    if (((char *)arr)[index] & (128u >> (numb % 8))){
        return 0;
    }

    return 1;
}

int is_free(unsigned char *BitBlocks,unsigned Max_Num, unsigned Num) {

if (Num >= Max_Num) {
    return -1;
} else {
    printf("%c\n",BitBlocks[(7 - (Num & 7u))]);
    return (BitBlocks[(7 - (Num & 7u))]) & 1;
}
}

int main(){
    unsigned char lol[8]={'b', 0, 1, 1, 0, 0, 'a', 'b'};
    printf("%d\n", func(lol, 10, 7));
    printf("%d\n", is_free(lol, 10, 7));
    return 0;
}