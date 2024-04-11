#include <iostream>

using namespace std;

struct A {
       int n = 0;
       static int k; 
       A (const A& a)
       {n = a.n;}
       static int f() 
       { return k;}
       A(int a = 3) 
       { n = a;}
       };
int A::k = 5;

int main () {
       A a = A(1), b;
       cout << A::f()<<" "<<a.k<<b.n<< endl;
       return 0;
        }