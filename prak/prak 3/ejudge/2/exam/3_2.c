#include <stdio.h>
#include <stdlib.h>

int main()
{
    if (1) {printf("World\n"); exit(1);}
    abort();
}