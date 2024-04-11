#include <iostream>
using namespace std;
class Circle{
    int x;
    int y;
    int rad;
public:
    Circle(int cx = 1, int cy = 1, int crad = 1): x(cx),y(cy),rad(crad) {count++;};
    int get_r(){
        return rad;
    }
    int get_x(){
        return x;
    }
    int get_y(){
        return y;
    }
    void set_r(int r){ rad = r; }

    virtual void big(int k){
        rad *= k;
    }

    virtual int area() { return 3.14 * rad * rad;}
    virtual void print_inf(){
    cout << "r = "<< rad<< endl;
    cout << "x = "<< x<< endl;
    cout << "y = "<< y<< endl;
    }
    static int count;
};
class Ring: public Circle{
    int in_rad;
public:
    static int r_count;
    Ring( int cx = 1, int cy = 1, int crad = 1, int ir =0): Circle(cx,cy,crad){
        try{
            if(ir > crad){
                throw -1;
            }
            in_rad = ir;
        }
        catch (int){
            in_rad = crad;
        }
        r_count++;
    }
    virtual int area(){ return 3.14 * get_r() * get_r() - 3.14 * in_rad * in_rad;}
    virtual void big(int k){
        set_r(get_r() * k);
        in_rad *= k;
    }
    virtual void print_inf(){
    cout << "r = "<< in_rad<< endl;
    cout << "ir = "<<get_r()<<endl;
    cout << "x = "<< get_x()<< endl;
    cout << "y = "<< get_y()<< endl;
    }

};
void Ring_count(){
    cout<<Ring::r_count<< endl;
}
void Circle_count(){
    cout<< Circle::count - Ring::r_count<<endl;
}
const char* ptr_to(Circle* ptr)
{
    return typeid(*ptr).name();
}
class f{
public:
    void operator()(Circle &obj, double k){
        obj.big(k); 
    }
};
int Circle:: count = 0;
int Ring:: r_count = 0;
int main(){
    Circle c1;
    Circle c2(2,3,4);
    c1.print_inf();
    c2.print_inf();
    Ring r1;
    cout<< "ring"<<endl;
    r1.print_inf();
    Ring r2(2, 2, 3, 4);
    r2.print_inf();
    Ring_count();
    Circle_count();
    f f1;
    f1(r2, 2);
    r2.print_inf();
    Circle* pc1 = &c2;
    Circle* pc2 = &r2;
    cout <<ptr_to(pc1) << " " << ptr_to(pc2) <<endl;
    cout << c2.area()<<endl;
    cout << r2.area()<<endl;
    return 0;
}