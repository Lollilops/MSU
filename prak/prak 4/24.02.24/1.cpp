#include <iostream>
#include <cstring>
using namespace std;

class C {
    int i;
public:
    C (int x) { i = x; }
    C (const C & y) { i = y.i; cout<<i<<" copy\n";}
    C f(const C & c) const { cout << c.i << endl;   return *this; }

        void set_i(int i){this->i=i;}
        };

    C  t1 (const C* a) { 
        const C b  = C (3);
        // const C b  = 3; 
        return a->f(b); 
        }
int main()
{
        C c(1); 
        t1(&c);

return 0; 
}