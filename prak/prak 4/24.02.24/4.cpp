//Исправить только класс B, чтобы main компилировался без ошибок 
//и работал верно 
#include <iostream>

using namespace std;

class A { 
public: 
    int a, b; 
    A(int x,int y) : a(x),b(y){} 
}; 
class B{ 
public: 
    A a; 
    B(int x = 0, int y = 0):a(x, y){}
}; 
int main(){ 
    B b1; 
    cout<<b1.a.a << b1.a.b<<'\n';
}