#include <stdio.h>

char fa(char a[], int l, int n) {
    char q, i;
    i=n/8;
    n%=8;
    if (i<l) {
        q=a[i]>>n;
        q=q&1;
    }
    else {printf("wrong n");
    }
    return q;
    }

char fb(char a[], int l, int n) {
    char q, i;
    i=n/8;
    n%=8;
    if (i<l) {
        q=a[i]>>(7-n);
        q=q&1;
    }
    else {printf("wrong n");
    }
    return q;
    }

int main(){
    int p,n,buf, l=3;
    scanf("%d", &n);
    char a[3];
    for (int i=0; i<l; i++) {
        scanf("%d", &buf);
        a[i]= (buf%255);
        }

    printf("Ansver1 is%d\n", fa(a, l, n));
    printf("Ansver2 is%d\n", fb(a, l, n));
    for (int i=0; i<l; i++) {
        p=a[i];
        printf(" ");
        for (int j=0; j<8; j++) {
            p=a[i]&(0x80);
            p>>=7;
            printf("%d",p);
            a[i]<<=1;
    }
    }



    printf("Ansver1 is%d\n", fa(a, l, n));
    printf("Ansver2 is%d\n", fb(a, l, n));
    for (int i=0; i<l; i++) {
        p=a[i];
        printf(" ");
        for (int j=0; j<8; j++) {
            p=a[i]&(0x80);
            p>>=7;
            printf("%d",p);
            a[i]<<=1;
    }
    }


    return 0;
}
