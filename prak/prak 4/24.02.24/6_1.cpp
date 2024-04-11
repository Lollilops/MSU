#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class BinaryNumber {
private:
    string binary;

public:
    BinaryNumber(const std::string &s) : binary(s) {}

    operator std::string() const {
        return binary;
    }

    const BinaryNumber &operator++() {
        // Ищем позицию последней единицы в строке
        int pos = binary.size() - 1;
        while (pos >= 0 && binary[pos] == '1') {
            binary[pos] = '0'; // Заменяем 1 на 0
            pos--;
        }
        if (pos >= 0) {
            binary[pos] = '1'; // Устанавливаем 1 на следующей позиции
        } else {
            // Если не нашли 0, значит все биты равны 1, нужно добавить еще один разряд
            binary = '1' + binary;
        }
        return *this;
    }
};


class A{ 
    int a;
    static A* instance;
    A (int i = 0): a(i){}// создание
    // A(const A& c){
    //     a = c.a;
    // }
public:
    A(const A& c){
        a = c.a;
    }
    static A getInstance(int i = 0) {
        if (instance == nullptr) {
            instance = new A(i);
        }
        return *instance;
    }
    static void clear() {
        if (instance != nullptr) {
            delete instance;
        }
    }
    void print(){ 
    std:: cout<< a << std::endl;
    }
};

A* A::instance = nullptr;

int main(){
    cout << "1-я" << endl;
    A b = A::getInstance(5);
    b.print();
    A s = A::getInstance();
    s.print();
    A::clear();
    ///
    cout << "3-я" << endl;
    std::string input;
    std::cout << "Введите число в двоичном виде: ";
    std::cin >> input;

    BinaryNumber bn(input);
    ++bn; // Увеличиваем число на 1

    std::cout << "Число после увеличения на 1: " << string(bn) << endl;

    return 0;

}
