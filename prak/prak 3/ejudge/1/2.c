#include <stdio.h>

int main(int argc, const char * argv[]) {
    char sym;
    long long int sum = 0;
    while (!feof(stdin)) {
        scanf("%c\n", &sym);
        if (sym >= '0' && sym <= '9') {
            sum += (sym - '0');
        } else if (sym >= 'a' && sym <= 'f') {
            sum += ((sym - 'a') + 10);
        } else if (sym >= 'A' && sym <= 'F') {
            sum += ((sym - 'A') + 10);
        }
    }
    printf("%lld\n", sum);
    return 0;
}