// Для приведённой ниже программы описать функцию f (), которая, получая в качестве параметра указатель на объект типа void , возвращает указатель на объект производного класса B, полученную наиболее безопасным образом, а в случае невозможности приведения типов корректно завершает программу.
struct A { virtual int z () {return 1;} };
struct B: A { int x; B (int n = 7) { x = n; } };
B* f (A *p);
int main () {
B b, * pb = f (& b);
cout << pb -> x << endl;
A a, *pa;
pb = f(& a); 
cout << pb -> x << endl;

pa=f(0);
cout << pa -> z() << endl;
return 0;
}