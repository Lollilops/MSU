class B{...    };// a)полиморфный  b)неполиморфный
class D:public B{...    };
int main(){    B b; D d; 
        B* pb = <?> &d;              // 1
D* pd = <?> pb;              // 2
char* pc = <?> pb;           // 3
void* pv = <?> pc;              // 4
pb = <?> pv;                 // 5
return 0;
    }