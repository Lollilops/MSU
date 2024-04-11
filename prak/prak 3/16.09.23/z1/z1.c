#include <stdio.h>

int fa(char *p, int l, int n) {
    char q, i=n/8;
    n%=8;
    if (i<l) {
        q=*(p+i);
        q=q>>n;
        q=q&1;
    }
    else {printf("wrong n");
    }
    return q;
    }

int main(){
    int ans,n,l,p=3;
    scanf("%d", &n);
    char a[]={1,2,3};
    ans=fa(a,l,n);
    for (int i=0; i<l; i++) {
        for (int j=0; i<8; i++) {
            p=a[i]&(0x80);
            p>>=7;
            printf("%d",p);
            a[i]<<=1;
    }
    }
    return 0;
}
