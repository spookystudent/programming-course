#include <iostream>
using namespace std;

template <class T>

class Set {

    int length;

    Set* right = nullptr;
    Set* left = nullptr;
    Set* parent = nullptr;
    Set* root = nullptr;

    T value{};

    //Добавление элемента в множество (дерево)
    void _AddElement(T element, Set* current) {

        //заполняем рут, в случае его отсутствия
        if (root == nullptr) {
            root = new Set;
            root->value = element;
            ++length;
        }
        else {
            if (element < current->value) {
                //добавляем элемент влево, если место свободно
                if (current->left == nullptr) {
                    ++length;
                    current->left = new Set;
                    current->left->value = element;
                    current->left->parent = current;
                }
                //если не свободно, спускаемся на уровень ниже
                else {
                    current->left->parent = current;
                    AddElement(element, current->left);
                }
            }
            if (current->value < element) {
                //добавляем элемент вправо, если место свободно
                if (current->right == nullptr) {
                    ++length;
                    current->right = new Set;
                    current->right->value = element;
                    current->right->parent = current;
                }
                //если не свободно, спускаемся на уровень ниже
                else {
                    current->right->parent = current;
                    AddElement(element, current->right);
                }
            }
        }
    }

    //Удаление элемента из множества (дерева)
    void _DeleteElement(T element) {

        //если такого элемента нет, то ничего не удаляем
        if (!exists(element)) return;

        //уменьшаем длину множества
        --length;
        //мы удалили последний элемент
        if (length == 0) {
            root->~Set();
            root = nullptr;
            return;
        }

        //ищем удаляемый элемент
        Set* current = root;

        while (!(current->value == element)) {
            while (current->value < element) current = current->right;
            while (element < current->value) current = current->left;
        }

        if (current->right == nullptr) {
            //правого элемента нет, а левый есть
            if (current->left != nullptr) {
                //если удаляем root
                if (current == root) {
                    root->left->parent = nullptr;
                    root->~Set();
                    root = root->left;
                    return;
                }
                //current != root
                current->left->parent = current->parent;
                if (current->parent->left == current) current->parent->left = current->left;
                else current->parent->right = current->left;
                current->~Set();
                return;
            }
            //нет ни правого, ни левого
            else {
                if (current->parent->left == current) current->parent->left = nullptr;
                else current->parent->right = nullptr;
                current->~Set();
                return;
            }
        }
        if (current->left == nullptr) {
            //левого элемента нет, а правый есть
            if (current->right != nullptr) {
                if (current == root) {
                    root->right->parent = nullptr;
                    root->~Set();
                    root = root->right;
                    return;
                }
                current->right->parent = current->parent;
                if (current->parent->left == current) current->parent->left = current->right;
                else current->parent->right = current->right;
                return;
            }
            //нет ни правого, ни левого
            else {
                if (current->parent->left == current) current->parent->left = nullptr;
                else current->parent->right = nullptr;
                current->~Set();
                return;
            }
        }

        //есть и левый элемент, и правый
        Set* del_pos = current;

        //находим наименьший элемент в правой ветке
        current = current->right;
        while (current->left != nullptr) current = current->left;

        //перемещаем левую ветку в конец правой
        current->left = del_pos->left;
        del_pos->left->parent = current;

        //если удаляем root
        if (del_pos == root) {
            root->~Set();
            root = root->right;
            root->parent = nullptr;
            return;
        }

        //связываем ветку right c parent у удаляемого элемента
        del_pos->right->parent = del_pos->parent;
        if (del_pos->parent->left == del_pos) del_pos->parent->left = del_pos->right;
        else del_pos->parent->right = del_pos->right;
        current->~Set();
    }

    //Поиск следующего элемента
    T _NextElement(int i, T lastOutput) const {

        //возвращаем обратно наименьший элемент
        if (i == 0) return lastOutput;
        
        //ищем предыдущий
        Set* current = root;

        while (!(current->value == lastOutput)) {
            while (current->value < lastOutput) current = current->right;
            while (lastOutput < current->value) current = current->left;
        }

        //если правой ветки нет, то поднимаемся выше
        if (current->right == nullptr) {
            if (current->parent == nullptr) {
                return root->value;
            }
            return current->parent->value;
        }

        //вовращаем наименьший элемент в правой ветке
        current = current->right;
        while (current->left != nullptr) current = current->left;
        return current->value;
    }

    //Поиск наименьшего элемента в множестве
    T _SmallestElement() const {
        if (root == nullptr) return {};
        
        Set* small = root;

        while (small->left != nullptr) {
            small = small->left;
        }

        return small->value;
    }

public:

    //Конструктор
    Set() {
        length = 0;
    }

    //Конструктор копий
    Set(const Set& other) {
        length = 0;
        T next = other.SmallestElement();
        for (int i = 0; i < other.size(); ++i) {
            next = other.NextElement(i, next);
            AddElement(next, root);
        }
    }
    //Деструктор
    ~Set() {}

    //Вставка элемента в множество
    Set operator + (const T& element) const {
        Set other(*this);
        other.AddElement(element, other.root);
        return other;
    }
    friend Set operator + (const T& element, const Set& other) {
        Set another(other);
        another.AddElement(element, another.root);
        return another;
    }
    Set& operator +=(const T& element) {
        AddElement(element, root);
        return *this;
    }

    //Удаление элемента из множества
    Set operator - (const T& element) const {
        Set other(*this);
        other.DeleteElement(element);
        return other;
    }
    Set& operator -= (const T& element) {
        DeleteElement(element);
        return *this;
    }

    //Проверка наличия элемента в множестве
    bool exists(const T& element) const {
        if (root == nullptr) return false;

        Set* current = root;
        
        while (!(current->value == element)) {
            while (element < current->value) {
                if (current->left == nullptr) return false;
                current = current->left;
            }
            while (current->value < element) {
                if (current->right == nullptr) return false;
                current = current->right;
            }
        }
        return true;
    }

    //Объединение множеств
    Set operator + (const Set& other) const {
        Set newSet(*this);
        T next = other.SmallestElement();

        for (int i = 0; i < other.size(); ++i) {
            next = other.NextElement(i, next);
            if (!newSet.exists(next)) newSet.AddElement(next, newSet.root);
        }

        return newSet;
    }
    Set& operator += (const Set& other) {
        T next = other.SmallestElement();

        for (int i = 0; i < other.size(); ++i) {
            next = other.NextElement(i, next);
            if (!exists(next)) AddElement(next, root);
        }

        return *this;
    }

    //Разность множеств
    Set operator - (const Set& other) const {
        Set newSet(*this);

        T next = other.SmallestElement();

        for (int i = 0; i < other.size(); ++i) {
            next = other.NextElement(i, next);
            if (newSet.exists(next)) newSet.DeleteElement(next);
        }

        return newSet;
    }
    Set& operator -= (const Set& other) {
        if (root == other.root) {       
            root = nullptr;
            length = 0;
            return *this;
        }

        T next = other.SmallestElement();

        for (int i = 0; i < other.size(); ++i) {
            next = other.NextElement(i, next);
            if (exists(next)) DeleteElement(next);
        }

        return *this;
    }

    //Операции сравнения
    bool operator == (const Set& other) const {
        return !(*this != other);
    }
    bool operator != (const Set& other) const {
        if (length != other.length) return true;
        if (root == nullptr && other.root == nullptr) return false;

        T next1 = SmallestElement();
        T next2 = other.SmallestElement();

        for (int i = 0; i < length; ++i) {
            next1 = NextElement(i, next1);
            next2 = other.NextElement(i, next2);
            if (!(next1 == next2)) return true;
        }
        return false;
    }

    //Мощность множества (число элементов)
    int size(void) const {
        return length;
    }

    //Вывод элементов в порядке возрастания, разделяя их пробелом
    friend ostream& operator << (ostream& os, const Set& other) {

        T next = other.SmallestElement();

        for (int i = 0; i < other.size(); ++i) {
            next = other.NextElement(i, next);
            os << next;
            if (i != other.size()) os << " ";
        }

        return os;
    }

    void AddElement(T element, Set* current) {
        _AddElement(element, current);
    }

    void DeleteElement(T element) {
        _DeleteElement(element);
    }

    T NextElement(int i, T lastOutput) const {
        return _NextElement(i, lastOutput);
    }

    T SmallestElement() const{
        return _SmallestElement();
    }

};

//#include "set-test.h"
int main(void)
{
    Set<int> a;
    a = a + 5; a += 2;
    a -= a - 5;
    cout << a;
    /*Set<int> a;
    a += 25;
    for (int i = 50; i >= 0; i--) a += i;
    for (int i = 0; i <= 50; i += 2) a -= i;
    for (int i = 0; i <= 50; i += 3) a -= i;
    cout << a << endl;
    Set<int> b = ((a + 999) + 9999) - 89;
    cout << b.size() << endl;
    cout << b.exists(1) << b.exists(2)
        << b.exists(3) << b.exists(4)
        << b.exists(5) << endl;
    Set<int>* c = new Set<int>;
    *c += 1; *c += 5; *c += 6;  
    cout << c->size() << endl;
    cout << a - *c << endl;
    *c += 1111;
    cout << a + *c << endl;
    cout << a << endl << b << endl;
    b = b;
    b += b;
    b -= b + 1;
    b += b;
    cout << b;
    delete c;*/

    return 0;

    /*Set<double> abcd;
    for (double i = 0.0; i < 1.0; i += 0.2) abcd += i;
    cout << abcd;
    a -= b -= *c -= 5;*/
}