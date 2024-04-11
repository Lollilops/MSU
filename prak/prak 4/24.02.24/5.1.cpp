#include<iostream>
using namespace std;
class B {  //базовый
            private:    int x;
        protected:  int y;
        public:     int  z;
        B(const B &a){
            x = a.x;
            y = a.y;
            z = a.z;
        };
        B(int x1=0, int y1=0, int z1=0):x(x1),y(y1),z(z1) { }
        void print(){ std::cout <<"x="<<x<<" y="<<y<<" z="<<z<<endl;}
         };
//D - производный от В
class D: //Рассматриваем разные виды наследования
    public    // protected   // private
    B { 
    private:    int x1;
    protected:  int y1;
    public:     int  z1;

 public:     D(int x1=1, int y1=1, int z1=1):B(x1,y1,z1),x1(x1),y1(y1),z1(z1) { }
            D(const D &a):B(a){x1 = a.x1, y1 = a.y1, z1 =a.z1;}
 // Написать конструктор копирования
          void f_D(){ /*x += 1;*/ y+=1;  z+=1; }
         friend  void  f_friend();
                 void print(){ B::print(); std::cout <<"x1="<<x1<<" y1="<<y1<<" z1="<<z1<<endl;}
};
//DD - производный от D
class DD: public D{
public:
     void f_DD(){ D d(1,2,3); B* pb=&d;}
         void    print(){D::print();}
}; 
void  f_friend(){ D d(1,2,3); B* pb=&d;}
void  not_friend(){ D d(1,2,3); 
                    //B* pb=&d; 
                    //pb->f_D(); 
                   }

int main() { 
    D d; 
    //d.x=1; 
    //d.y=2; 
    d.z =3; 

    d.f_D();
    f_friend();
    not_friend(); 

    //DD dd(d);
    B b(d);
    b.print();

    DD dd1;
    dd1.print();
    DD dd2=dd1;
        dd2.print();
};