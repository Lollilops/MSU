#include <iostream>
#include <cstring>

// Опишите один класс A с не более чем двумя явно
// описанными методами (включая специальные) так, 
// чтобы программа с данной функцией main (
// и без каких-либо директив) успешно выполнялась.


using namespace std;

class A{
public:
    A *a;
    A(A * a = 0){
        a = this;
    }
    A * operator->(){
        cout << "operator->" << endl;
        return a;
    }
};

int main(){
    A a;
    A(a->a);
    A(a->a->a);
return 0;
}