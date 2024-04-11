#include <iostream>
#include <cstring>

using namespace std;

class Matrix {
    int rows;
    int columns;
    int** m_matrix;
public:
    Matrix(int str = 5, int stb = 5, int elem = 0): rows(str), columns(stb) {
        m_matrix = new int*[str];
        for (int i = 0; i < str; i++) {
            m_matrix[i] = new  int[stb];
        }
        for (int i = 0; i < str; i++) {
            for (int j = 0; j < str; j++) {
                m_matrix[i][j] = elem;
            }
        }
    }
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete []m_matrix[i];
        }
        delete []m_matrix;
    }
    int get_rows() const {
        return rows;
    }
    int get_columns() const {
        return columns;
    }
    int get_elem(int i, int j) const {
        return m_matrix[i][j];
    }
    int* operator[](int x) {
        return m_matrix[x];
    }
    const int* operator[](int x) const{
        return m_matrix[x];
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
        m[3][i] = 111;
    }
    cout << m << mc;

    int x = m[2][3]; 
    
    cout << x << endl;
    
    //mc[1][1] = 100 ; // ошибка компиляции
    //cout << mc;

    cout << "===========================\n";
    Matrix M1;
    cout << M1;
    cout << M1[0][0] << endl;

}