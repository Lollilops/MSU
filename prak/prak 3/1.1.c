#include <stdio.h>
#include <stdlib.h>

int fun(int x){
    int res = 0;
    while (x != 0){
        int c = x % 10;
        res = res * 10;
        res += c;
        x = x / 10;
    }
    return res;
}

int main(){
    int x = 2345;
    int res = fun(x);
    printf("res=%d\n", res);

}
