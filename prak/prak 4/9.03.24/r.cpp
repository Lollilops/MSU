#include<iostream>
using namespace std;
class A  {
public:
   A(){ cout<<1;}
   A(const A& r){ cout<<2;}
   A(A&& r) = delete;
   ~A() { cout<<4;}
};
 
A  f() { A a; return a;}
 
int main() { f(); cout<<5; }