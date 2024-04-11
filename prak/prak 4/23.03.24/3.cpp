// Опишите  необходимые классы так, 
// чтобы в заданной функции main () не было ошибок, 
// а на экран печаталось  310.
#include <iostream>
#include <cstring>

using namespace std;

class T{
public :
    int n;
    T(int k = 10):n(k){}
    T(T & a){
        n = a.n;
    }
    ~T(){};
};

template <typename T1>
class P{
    T1 *n;
    int flag;
public:
    P(T1 *k):n(k){
        if(k == 0){
            n = new T1;
            flag = 1;
        }
        else{
            flag = 0;
        }
    }
    T1* operator->(){
        return n;
    }
    ~P(){
        if(flag == 1){
            delete n;
        }
    }
};


int main () {
    T t(3);
    P <T> p1(&t), p2(0);
    cout  <<  p1 -> n  <<  p2 -> n  <<  endl;
    return 0; 
}