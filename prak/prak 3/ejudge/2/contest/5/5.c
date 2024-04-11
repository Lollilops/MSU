#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

int count = 0;
long long low, high;
long long simple = -1;

void
INT_handler(int s)
{
    if(count == 3)
    {
        _exit(0);
    }
    else
    {
        if (simple == -1)
        {
            printf("0\n");
            fflush(stdout);
        }
        else   
        {
            printf("%lld\n", simple);
            fflush(stdout);
        }
        ++count;
        
    }
}

void
TERM_handler(int s)
{
    _exit(0);
}

int
main(void)
{
    if(!((scanf("%lld", &low) == 1) && (scanf("%lld", &high) == 1)))
    {
        return 0;
    }

    printf("%d\n", getpid());
    fflush(stdout);

    sigaction(SIGINT, &(struct sigaction) {.sa_handler = INT_handler, .sa_flags = SA_RESTART}, NULL);
    sigaction(SIGTERM, &(struct sigaction) {.sa_handler = TERM_handler, .sa_flags = SA_RESTART}, NULL);

    for (long long i = low; i < high; i++)
    {
        int p = 1;
        if (i > 10)
        {
            if (i%2 == 0 || i%10 == 5)
                continue;
        }
        for (long long j = 2; j < (sqrt((long double) i) + 1); j++)
        {
            if (i%j == 0)
            {
                p = 0;
                break;
            }
        }

        if (p)
        {
            simple = i;
            // printf("%lld\n", simple);
        }
        
    }
   
    printf("-1\n");
    fflush(stdout);
    _exit(0);
    
}
