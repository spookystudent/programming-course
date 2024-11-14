#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Set {
    // vector<vector<T> > e;
    // e.push_back(vector<T>());
    // vector<vector<T> > set(hash, vector<T>());
    
    int table_size = 991;
    vector<vector<T>> set;
    

    public:
    
        // Custom methods
        int get_hash(const T &t) {
            int _hash = hash<T>()(t);
            
            return _hash % this->table_size;
        };
      
        // Конструкторы (если нужны)
        Set() {
            for (int index = 0; index < table_size; index++) {
                set.push_back(vector<T>());
            }

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
        Set &operator += (const T &t) {
            
            cout << t << ' ' << this->get_hash(t) << endl;
            return *this;
        };
        
        // Удаление элемента из множества
        // Set operator - (const T &t) const;
        // Set &operator -= (const T &t);
        
        // Проверка наличия элемента в множестве
        // bool exists(const T &t) const;
        
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
        // friend ostream& operator << (ostream& os, const Set &s) {
        // Поместите соответствующий код сюда
        
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