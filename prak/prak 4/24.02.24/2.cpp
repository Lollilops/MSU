#include <iostream>
#include <cstring>
using namespace std;

class X{
    mutable int a;
public:
    static int b;
    const static int c = 5; 
    X(): a(0){}
    static void f(){ b++; cout<<"f()\n";}
    void g() const {  a--;   b--;   cout<<"g()\n";   h();}
    void h() const {cout<<"a= "<<a<<"  b="<<b<<'\n';}
    };

int main(){    
    X x1;      
    const X x2;
    X::b=1; 
    X::f();
    x1.f();
    x1.g(); 
    x1.h();
    x2.g();
    x2.h();
}