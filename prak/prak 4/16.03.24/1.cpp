#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <iterator>

// Написать шаблонную функцию от 2ух параметров (вектор и список).
// Тип параметра шаблона — любой арифметический, т.е. функция должна работать, например, и с контейнерами из int, и из double.
// Функция должна изменить исходный вектор - добавить после четных (по номеру) элементов вектора нечетные (по номеру) элементы списка. Длины вектора и списка могут быть различны. Если список закончится раньше, чем пройден вектор, вставлять на оставшиеся места элементы со значением О.
// Нумерация элементов в векторе — с 0, в списке — с 1.
// Работа продолжается до конца вектора.
// Примеры работы функции:
// 1. V: v0-v1-v2-…..vn
// L: 11-12-...Im Vnew: v0-11-v1-v2-13-v3-v4.....
// 2. V: vO-v1-v2-...vn
// L: 11-12
// Vnew: v0-11-v1-v2-0-v3-v4-0.....

using namespace std;

template<typename T>
void PrintList(const T&a){
    typename T::const_iterator start = a.begin();
    typename T::const_iterator end = a.end();
    while(start != end){
        cout << *start << " ";
        start++;
    }
    cout << endl;
}

template<typename T>
void PrintListBack(const T&a){
    typename T::const_reverse_iterator start = a.rbegin();
    typename T::const_reverse_iterator end = a.rend();
    while(start != end){
        cout << *start << " ";
        start++;
    }
    cout << endl;
}

template<typename T>
void change_vector(list <T>&a, vector <T>&b){
    typename list<T>::const_iterator start_a = a.begin();
    typename vector<T>::const_iterator start_b = b.begin();
    typename list<T>::const_iterator end_a = a.end();
    typename vector<T>::const_iterator end_b = b.end();
    int a_idx = 0, b_idx = 0;
    b_idx++; start_b++;
    while(start_b != end_b){
        if(start_a == end_a){
            a_idx = -1;
        }
        
        if(b_idx%2 != 0){
            // cout<<b_idx << *start_b << endl;
            if(a_idx != -1){
                // cout << *start_b << endl;
                b.insert(start_b, *start_a);
                start_b++;
                end_b++;
                // b_idx--;
                // cout << *start_b << endl;
            }
            else{
                cout << *start_b << endl;
                b.insert(start_b, 0);
                start_b++;
                end_b++;
                // b_idx--;
                // cout << *start_b << endl;
            }
        }

        // cout << "Эпоха: " << b_idx << endl;
        // cout << *start_b << endl;
        if(start_a != end_a){  
            start_a++;
            a_idx++;
        }
        start_b++;
        b_idx++;
    }
}

int main(){
    vector<int> vec;
    const vector<int> c_vec = {1, 2, 3, 4, 5};
    
    const list<int> c_list = {3, 4, 5};
    list<int> list_a = {1, 2, 3, 4, 5};
    // const list<int> c_list;
    // list<int> a1;
    for(int i = 0; i < 6; i++){
        vec.push_back(i);
    }
    // const vector<int> c_vec = vec;
    PrintList(vec);
    PrintList(list_a);
    change_vector(list_a, vec);
    PrintList(vec);

    // list<double> lst = {1.1, 2.2, 3.3, 4.4, 5.5};
    return 0;
}
