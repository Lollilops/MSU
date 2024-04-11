// ДЗ-1. Срок сдачи — до 02.03.24
// Использование STL и типа string запрещено.
// Определить класс с полями разных типов, среди которых обязательно должны быть указатели. Класс должен быть АТД — все поля-данные закрыты.
// Для этого класса написать конструкторы, деструктор, оператор присваивания и произвольную функцию-член класса. В каждую из специальных функций класса включить отладочный вывод на экран, чтобы было понятно, какая функция работает.
// Это примеры данных, которые будут помещаться в список (см. п.2), вы можете написать свои:
// Элемент данных - объект, содержащий информацию о клиенте: фамилия, время добавления в очередь (целое или строка). Хранится также информация о текущем количестве клиентов в списке и об общем количестве клиентов во всех списках.
// Элемент данных – объект, содержащий информацию о заказе: название фирмы, номер телефона (целое или строка), номер заказа. Нумерация заказов единая для всех списков.
// Элемент данных – объект «банковский счет». Необходимые члены-данные: номер счета, владелец счета, дата создания счета (число или строка), сумма денег, которая на нем хранится. Нумерация счетов единая для всех списков.
// 2. АТД. Список данных.
// Класс — список (двунаправленный), в качестве элемента данных использовать тип, определенный в п.1.
// Класс список должен быть написан так, чтобы его легко было потом адаптировать для работы с данными произвольного типа.
// Определить необходимые конструкторы.
// Обеспечить корректное уничтожение объектов.
// В классе должны быть функции:
// добавления элемента в начало (push_front) и в конец (push_back),
// чтение первого элемента списка (front),
// чтение последнего элемента списка (back),
// удаление первого элемента списка (pop_front),
// удаление последнего элемента списка (pop_back),
// добавление элемента x перед позицией p ( insert(p,x)),
// удаление элемента из позиции p (erase(p))
// проверка списка на пустоту (empty),
// текущее число элементов (size),
// вывод информации об элементах списка (print).
// Функция main должна демонстрировать работу с объектами данного класса.
// Пример работы: Date d1(…); List l1; l1.push_front(d1); ... l1.print(); и т. д.
// Кузина Л.Н.


#include <iostream>
#include <cstring>
using namespace std;

class inf_cli{
    // Элемент данных – объект, содержащий информацию о заказе: название фирмы, номер телефона (целое или строка), номер заказа. 
    // Нумерация заказов единая для всех списков.
    char *firm, *phone;
    unsigned int order;
    static unsigned int count_id;
public:
    // Для этого класса написать конструкторы, деструктор, оператор присваивания и произвольную функцию-член класса.
     inf_cli(){
        firm = NULL;
        phone = NULL;
        order = count_id;
        count_id++;
        cout << "inf_cli()" << endl;
     }
     inf_cli(const char *f, const char*p){
        firm = new char[strlen(f) + 1];
        phone = new char[strlen(p) + 1];
        strcpy(firm, f);
        strcpy(phone, p);
        order = count_id;
        count_id++;
        cout << "inf_cli(const char *f, const char*p)" << endl;

     }
     inf_cli(inf_cli & a){
        firm = new char[strlen(a.firm) + 1];
        phone = new char[strlen(a.phone) + 1];
        strcpy(firm, a.firm);
        strcpy(phone, a.phone);
        order = a.order;
        cout << "inf_cli(inf_cli & a)" << endl;
     }
     ~inf_cli(){
        delete[] firm;
        delete[] phone;
        cout << "~inf_cli()" << endl;
     }
    
    inf_cli &operator=(inf_cli &a){
        if (this == &a)
            return *this;
        delete[] this->firm;
        firm = new char[strlen(a.firm) + 1];
        strcpy(firm, a.firm);
        // cout << a.firm << firm << endl;

        delete[] this->phone;
        phone = new char[strlen(a.phone) + 1];
        strcpy(phone, a.phone);
        order = a.order;
        cout << "inf_cli &operator=(inf_cli &a)" << endl;
        return *this;
    }

    void print_inf(){   cout << "print_inf():" << endl;
        cout << "order: " << order << endl;
        cout << "firm: " << firm << endl;
        cout << "phone: " << phone << endl;
        cout << endl;
        return;
    }
};

unsigned int inf_cli::count_id = 1;


class list_a{
    struct Node
    {
        Node *next;
        Node *prev;
        inf_cli data;
    };
    Node *head, *tail;
    unsigned int list_size;
    // static unsigned int id_counter;

public:
    //--------------------------------------------------------------------------------
    // конструкторы, деструкторы

    list_a(){
        head = NULL;
        tail = NULL;
        list_size = 0;
    cout << "list_a()" << endl;
    };

    ~list_a(){
        Node *tmp;
        while (head != NULL)
        {
            tmp = head->next;
            delete head;
            head = tmp;
        }
        cout << "~list_a()" << endl;
    };

    void push_front(inf_cli a){
        if (head == NULL)
        {
            head = new Node;
            head->next = NULL;
            head->prev = NULL;
            head->data = a;
            tail = head;
            list_size++;
        }
        else
        {
            Node *tmp = new Node;
            tmp->data = a;
            tmp->prev = NULL;
            tmp->next = head;
            head->prev = tmp;
            head = tmp;
            list_size++;
        }
        cout << "void push_front(inf_cli a)" << endl;
    };

    void push_back(inf_cli a){
        if (head == NULL)
        {
            head = new Node;
            head->next = NULL;
            head->prev = NULL;
            head->data = a;
            tail = head;
            list_size++;
        }
        else
        {
            Node *tmp = new Node;
            tmp->data = a;
            tmp->next = NULL;
            tmp->prev = tail;
            tail->next = tmp;
            tail = tmp;
            list_size++;
        }
        cout << "void push_back(inf_cli a)" << endl;
    };

    void insert(unsigned int p, inf_cli a){
        if (p > list_size)
        {
            cout << "ERROR: p > list_size <=> " << p << " > " << list_size << endl;
            cout << "void insert(unsigned int p, inf_cli a)" << endl;
            return;
        }
        unsigned int i = 1;
        Node *tmp = head;
        while (i < p)
        {
            tmp = tmp->next;
            i++;
        }
        Node *tmp1 = new Node;
        tmp1->next = tmp;
        tmp1->prev = tmp->prev;
        tmp1->data = a;
        tmp->prev->next = tmp1;
        tmp->prev = tmp1;
        list_size++;
        cout << "void insert(unsigned int p, inf_cli a)" << endl;
    };

    void erase(unsigned int p){
        if ((p > list_size) or (p == 0))
        {
            cout << "ERROR: p > list_size <=> " << p << " > " << list_size << endl;
            cout << "void erase(unsigned int p)" << endl;
            return;
        }
        unsigned int i = 1;
        Node *tmp = head;
        while (i < p)
        {
            tmp = tmp->next;
            i++;
        }
        if ((tmp->next == NULL) and (tmp->prev == NULL))
        {
            head = NULL;
            tail = NULL;
            cout << "Data of the deleted account:" << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            tmp->data.print_inf();
            cout << "------------------------------------------------------------------------------" << endl;
            delete tmp;
            list_size--;
            cout << "void erase(unsigned int p)" << endl;
            return;
        }
        if (tmp->prev)
        {
            tmp->prev->next = tmp->next;
        }
        else
        {
            tmp->next->prev = NULL;
            head = tmp->next;
        }
        if (tmp->next)
        {
            tmp->next->prev = tmp->prev;
        }
        else
        {
            tmp->prev->next = NULL;
            tail = tmp->prev;
        }
        cout << "Data of the deleted account:" << endl;
        cout << "------------------------------------------------------------------------------" << endl;
        tmp->data.print_inf();
        cout << "------------------------------------------------------------------------------" << endl;
        delete tmp;
        list_size--;
        cout << "void erase(unsigned int p)" << endl;
    };

    void front(){
        if (head != NULL)
        {
            head->data.print_inf();
        }
        else
        {
            cout << "head = NULL" << endl;
        }
        cout << "void front()" << endl;
    };

    void back(){
        if (tail != NULL)
        {
            tail->data.print_inf();
        }
        else
        {
            cout << "tail = NULL" << endl;
        }
        cout << "void back()" << endl;
    };

    unsigned int size(){
        cout << "void size(): " << list_size << endl;
        return list_size;
    };

    void empty(){
        if (list_size)
            cout << "The list is not empty" << endl;
        else
            cout << "The list is empty" << endl;
        cout << "void empty()" << endl;
    };

    void print(){
        if (list_size)
        {
            Node *tmp = head;
            cout << "\nInformation about all firms:" << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            while (tmp)
            {
                tmp->data.print_inf();
                tmp = tmp->next;
            }
            cout << "------------------------------------------------------------------------------" << endl;
        }
        else
            cout << "The list is empty" << endl;
        cout << "void print()" << endl;
    };

    void pop_front(){
        if (head)
        {
            Node *tmp = head;
            if ((tmp->next == NULL) and (tmp->prev == NULL))
            {
                head = NULL;
                tail = NULL;
                cout << "Data of the deleted account:" << endl;
                cout << "------------------------------------------------------------------------------" << endl;
                tmp->data.print_inf();
                cout << "------------------------------------------------------------------------------" << endl;
                delete tmp;
                list_size--;
                cout << "void pop_front()" << endl;
                return;
            }
            head = head->next;
            head->prev = NULL;
            cout << "Data of the deleted account:" << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            tmp->data.print_inf();
            cout << "------------------------------------------------------------------------------" << endl;
            delete tmp;
            list_size--;
        }
        else
        {
            cout << "The list is empty" << endl;
        }
        cout << "void pop_front()" << endl;
    };

    void pop_back(){
        if (tail)
        {
            Node *tmp = tail;
            if ((tmp->next == NULL) and (tmp->prev == NULL))
            {
                head = NULL;
                tail = NULL;
                cout << "Data of the deleted account:" << endl;
                cout << "------------------------------------------------------------------------------" << endl;
                tmp->data.print_inf();
                cout << "------------------------------------------------------------------------------" << endl;
                delete tmp;
                list_size--;
                cout << "void pop_back()" << endl;
                return;
            }
            tail = tail->prev;
            tail->next = NULL;
            cout << "Data of the deleted account:" << endl;
            cout << "------------------------------------------------------------------------------" << endl;
            tmp->data.print_inf();
            cout << "------------------------------------------------------------------------------" << endl;
            delete tmp;
            list_size--;
        }
        else
        {
            cout << "The list is empty" << endl;
        }
        cout << "void pop_front()" << endl;
    };
};

int main(){
    const char *fi1 = "firm_1\0";
    const char *fi2 = "firm_2\0";
    const char *fi3 = "firm_3\0";
    const char *fi4 = "firm_4\0";

    const char *ph1 = "+7(969)062-97-44\0";
    const char *ph2 = "+972 53-859-0804\0";
    const char *ph3 = "+7(969)062-97-45\0";
    const char *ph4 = "+7(000)000-00-00\0";

    inf_cli f1(fi1, ph1);
    inf_cli f2(fi2, ph2);
    inf_cli f3(fi3, ph3);
    inf_cli f4(fi4, ph4);

    list_a a1;

    a1.print();

    a1.push_front(f3);
    a1.push_front(f4);

    a1.print();

    a1.push_back(f1);

    a1.print();

    a1.front();

    a1.back();

    a1.size();

    a1.empty();

    a1.insert(2, f2);

    a1.print();

    a1.erase(2);
    a1.print();
    a1.pop_back();
    a1.print();
    a1.pop_front();
    a1.print();
    f1 = f2;
    f1.print_inf();
    return 0;


}