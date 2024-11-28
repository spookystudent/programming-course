#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;



/*

Set tree;

tree.append(13);
tree.append(14);

struct ElementSet
    ElementSet* up;
    ElementSet* left;
    ElementSet* right;

Set tree
    ElementSet* top;
        
    append():
        
    
    
    

*/

struct ElementSet {
    ElementSet *up = nullptr;
    ElementSet *left = nullptr;
    ElementSet *right = nullptr;
    int value;
};

template <class T>
class Set {
    // vector<vector<T> > e;
    // e.push_back(vector<T>());
    // vector<vector<T> > table(hash, vector<T>());
    
    // int table_size = 10;
    // vector<vector<T>> table;
    
    

    public:
        ElementSet *top = nullptr;
    
        // Custom methods
        // int get_hash(const T &t) const {
        //     int _hash = hash<T>()(t);
            
        //     return _hash % this->table_size;
        // };
        
        ElementSet createElement(const T &t) {
            ElementSet* element ;
            
            element.value = t;
            
            return element;
        }
        
        
        void addElement(const T &t) {
            ElementSet* element = createElement(t);
            
            // cout << nullptr << endl;
            if (this->top == nullptr) {
                this->top = &element;
                cout << "create top " << this->top->value << endl;
                

            } else {
                cout << "check top " << this->top->value << ' ' << element.value << endl;
                if (element.value < this->top->value) {
                    this->top->left = &element;
                    cout << "create left " << element.value << endl;
                } else if (element.value > this->top->value) {
                    this->top->right = &element;
                    cout << "create right " << element.value << endl;
                }
                
                // cout << top->left->value << endl;
                // cout << top->right->value << endl;
            }
            
            // c
        };
        
        
        // void removeElement(const T &t) {
        //     int index = this->findIndex(t);
        //     if (index == -1) return;
            
        //     int hash_index = this->get_hash(t);
        //     vector<T> set = this->table[hash_index];
            
        //     vector<T> result;
            
        //     for (auto element : set) {
        //         if (element != t) result.push_back(element);
        //     }
            
        //     this->table[hash_index] = result;
        // };
        
        
        // int findIndex(const T &t) {
        //     if (!this->exists(t)) return -1;

        //     int hash_index = this->get_hash(t);
            
        //     for (int i = 0; i < this->table[hash_index].size(); i++) {
        //         if (t == table[hash_index][i]) return i;
        //     }
        //     return -1;
        // };
        
        // void print_fullness() const {
        //     for (int i = 0; i < table_size; i++) {
        //         cout << this->table[i].size() << ' ';
        //     }
        //     cout << endl;
        // };
        
        
      
        // Конструкторы (если нужны)
        Set() {

            cout << "Constructor\n";
        }; 
        Set(const Set &other) {
            cout << "Constructor other\n";
        };
      
        // Вставка элемента в множество
        // Set operator + (const T &t) const {
        //     cout << "+1\n";
        // };
        // friend Set operator + (const T &t, const Set &s) {
        //     cout << "+2\n";
        // };
        /*
        1 + a;
        
        */
        Set &operator += (const T &t) {
            this->addElement(t);

            return *this;
        };
        
        // Удаление элемента из множества
        // Set operator - (const T &t) const;
        Set &operator -= (const T &t) {
            this->removeElement(t);
            
            return *this;
        };
        
        // Проверка наличия элемента в множестве
        // bool exists(const T &t) const {
        //     int hash_index = this->get_hash(t);

        //     for (int i = 0; i < this->table[hash_index].size(); i++) {
        //         if (t == this->table[hash_index][i]) return true;
        //     }
            
        //     return false;
        // };
        
        // Объединение множеств
        // Set operator + (const Set &s) const;
        // Set& operator += (const Set &s);
        
        // Разность множеств
        // Set operator - (const Set &s) const;
        // Set& operator -= (const Set &s);
        
        // Операции сравнения
        // bool operator == (const Set &s) const;
        // bool operator != (const Set &s) const;
        
        // Мощность множества (число элементов)
        // int size(void) const;
        
        // Вывод элементов в порядке возрастания, разделяя их пробелом
        friend ostream& operator << (ostream &os, const Set &set) {
            vector<T> result;
            
            for (int i = 0; i < set.table_size; i++) {
                for (auto element : set.table[i]) {
                    result.push_back(element);
                }
            };
            
            // stable_sort(result.begin(), result.end());
            
            for (auto element : result) {
                os << element << ' ';
            }

            return os;
        };

        
        // Операция присваивания (если нужна)
        // Set &operator = (const Set &s);
        
        // Деструктор (если нужен)
        // ~Set();
};
int main(void)
{
    Set<int> a;
    for (int i=50; i>=0; i--) a+=i;
    
    // for (int i=0; i<=50; i+=2) a-=i;
    // for (int i=0; i<=50; i+=3) a-=i;
    // cout << a << endl;
    // for (int i=0; i<=50; i+=2) a-=i;
    // for (int i=0; i<=50; i+=3) a-=i;

//   cout << a << endl;
//   Set<int> b = ((a + 999)+9999) - 89;
//   cout << b.size() << endl;
//   cout << b.exists(1) << b.exists(2)
//     << b.exists(3) << b.exists(4)
//     << b.exists(5) << endl;
//   Set<int> *c = new Set<int>;
//   *c +=1; *c +=5; *c +=6;
//   cout << c->size() << endl;
//   cout << a-*c << endl;
//   *c += 1111;
//   cout << a+*c << endl;
//   delete c;
  return 0;
};