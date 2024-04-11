// Ваш Староста наконец-то разобрался с Google Api и создал табличку в гугл доке прогой, и в честь такого события ДЗ3 Кузиной
// ДЗ-3. Перегрузка операций. Срок сдачи — до 16.03.24
// Написать класс Матрица таким образом, чтобы к объектам этого типа была применима двойная индексация.

// Должен быть верным, например, следующий фрагмент программы:



// Matrix m; // возможно задание с параметрами по желанию

// const Matrix mc;

// … m[1][2] = 5;

// cout « m «mc;

// int x = m[2][3]; cout«x«endl;

// cout« mc[1][1];

// // mc[1][1] =100 ; // ошибка компиляции



// Кузина Л.Н.

#include <iostream>
#include <cstring>

using namespace std;

class Matrix{
    int rows, columns, **matr;
public:
    Matrix(int sr = 5, int sb = 5, int elem = 0): rows(sr), columns(sb){
        matr = new int*[sr];
        for(int i = 0; i<sb; i++){
            matr[i] = new int[sb];
        }
        for(int i = 0; i<sr; i++){
            for(int j = 0; j < sb; j++){
                matr[i][j] = elem;
            }
        }
    }
    ~Matrix(){
        for(int i = 0; i<rows; i++){
            delete []matr[i];
        }
        delete []matr;
    }
    int get_rows() const {
        return rows;
    }
    int get_columns() const {
        return columns;
    }
    int get_elem(int i, int j) const {
        return matr[i][j];
    }
    int* operator[](int x) {
        return matr[x];
    }
    const int* operator[](int x) const{
        return matr[x];
    }
};

ostream& operator<< (ostream &os, const Matrix &m) {
        int str, stb;
        str = m.get_rows();
        stb = m.get_columns();
        for (int i = 0; i < str; i++) {
            for (int j = 0; j < str; j++) {
                os << m.get_elem(i, j)<< ' ';
            }
            os << '\n';
        }
        return os;
}

int main() {
    Matrix m(5,5,10); // возможно задание с параметрами по желанию

    const Matrix mc(3,3,1);

    m[1][2] = 5;
    for (int i = 0; i < m.get_columns(); i++) {
        m[3][i] = 111 - i;
    }
    // cout << "===========================\n";
    cout << m << "===========================\n" << mc;

    int x = m[2][3];
    cout << "===========================\n";
    cout << x << endl;
    
    //mc[1][1] = 100 ; // ошибка компиляции
    //cout << mc;

    cout << "===========================\n";
    Matrix M1;
    cout << M1;
    cout << "===========================\n";
    cout << M1[0][0] << endl;

}