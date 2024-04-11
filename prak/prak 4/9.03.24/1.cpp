#include <iostream>
#include <cstring>

using namespace std;

class X{ 
    int  i=0;
    double d=1.5;
public:
    void print()const{
        cout<<"X::print  X::i="<<i<<"  X::d="<<d<<endl;
    }
};
class Pointer{ //объект - указатель на объект другого класса
    X* px;
    int * count = nullptr;
public: 
    Pointer( X* x):px(x){
        count = new int();
        *count = 1;
        cout<<"Pointer(X)\n";
    }
    X * operator->()const{
        cout<<"Pointer->\n"; 
        return px;
    }
    X & operator*(){
        cout<<"Pointer->\n"; 
        return *px;
    }
    ~Pointer(){
        cout<<"~Pointer\n"<<endl;
        if(*count == 1){
            delete px; // px не должен указывать на массив, иначе нужен delete[]            
            delete count;
        }
        else
            (*count)--;
    } 


    Pointer( const Pointer & p) :px(p.px), count(p.count){
        cout<<"Pointer-copy\n";
        (*count)++;
    }
};
class Pointer2{ //объект - указатель на (объект другого класса-указатель)
    Pointer pp;
public: 
    Pointer2( X* x):pp(x){
        cout<<"Pointer2(X*)\n";
    }
    Pointer  operator->()const{
        cout<<"Pointer2->\n"; 
        return pp;
    }
    Pointer & operator*(){
        cout<<"Pointer2->\n"; 
        return pp;
    }
    ~Pointer2(){cout<<"~Pointer2\n";}
};

int main(){
 Pointer p1(new X);
 p1->print();
 (*p1).print();

 Pointer2 p2(new X);
 p2->print();
 (**p2).print();
 
 return 0;
 //динамическая память, выделенная под X, освобождается автоматически, когда вызывается деструктор для объекта-указателя
}
