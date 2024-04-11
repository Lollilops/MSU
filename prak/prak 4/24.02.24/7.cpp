#include <iostream>

class A {
private:
    int a;
    
public:
    A(int val = 0) : a(val) {} // открытый конструктор
    ~A(){} // открытый деструктор
    int getA() const { return a; }
};

int main() {
    const int N = 5; // количество объектов в массиве
    char* buffer = new char[N * sizeof(A)]; // выделяем память для массива из N объектов класса A

    // Создание массива объектов класса A с использованием placement new
    A* array = reinterpret_cast<A*>(buffer);
    for (int i = 0; i < N; ++i) {
        new (&array[i]) A(i); // явный вызов конструктора для инициализации объекта на предварительно выделенной памяти
    }

    // Использование массива объектов класса A
    for (int i = 0; i < N; ++i) {
        std::cout << "Element " << i << ": " << array[i].getA() << std::endl;
    }

    // Уничтожение объектов и освобождение памяти
    for (int i = 0; i < N; ++i) {
        array[i].~A(); // явный вызов деструктора
    }
    delete[] buffer; // освобождаем память

    return 0;
}
