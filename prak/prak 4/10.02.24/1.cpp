#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class Str {
private:
    char *str;
    int len;

public:
    Str();
    Str(const char *);
    Str(const Str & a);
    Str & operator= (const Str & a) {
        if (this == &a)
            return * this; // если a = a
        if (str != NULL && len > 0) {
        delete[] str;
        }
        str = new char [ (len = a.len) + 1];
        strcpy (str, a.str);
        cout << "> Работает Оператор присваивания" << endl;
        return *this;
    }
    ~Str();
    void Getstr() {
        cout << "Работает get: " << str << endl;
    }
    void Setstr(const char* st){
        if (str != NULL && len > 0) {
        delete[] str;
        }
        strcpy(str, st);
        len = strlen(st);
    }
};

Str::Str() {
    str = "\0";
    len = 0;
    cout << "> Работает Str()" << endl;
   
}

Str::Str(const char *a) {
    len = strlen(a);
    str = new char[len];
    strcpy(str, a);
    cout << "> Работает Str(const char *a)" << endl;
    
}

Str::Str(const Str &a) {
    len = a.len;
    str = new char[len];
    strcpy(str, a.str);
    cout << "> Работает Str(const Str &a)" << endl;
    
}

Str::~Str() {
    if (str != NULL && len > 0) {
        delete[] str;
    }

    cout << "> Сработал ~Str()" << endl;
}

int main()
{
    Str a1, a2("pop"), a3 = a2;
    Str a4, a5;
    a4 = a3;
    a5.Setstr("lolpop");
    a5.Getstr();
}