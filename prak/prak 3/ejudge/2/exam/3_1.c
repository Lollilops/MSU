#include <stdio.h>
#include <stdlib.h>

int main()
{
    if(1) {printf("Hello\n"); exit(0);}
    abort();
}