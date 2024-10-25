// Example program
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;


class BitArray
{
    public:
        // Конструктор с одним параметром - длиной массива
        // выделяет память и заполняет массив нулевыми байтами
        BitArray(int length) {
          this->length = length;
          this->array = new int [length]{0};

        }
          
        // Конструктор копий
        BitArray(const BitArray &other) {
            this->array = new int[other.size()];
        };
        
        // Операция присваивания
        BitArray& operator = (const BitArray &other) {
            if (this == &other) return *this;
            
            delete[] this->array;

            this->length = other.size(); 
            this->array = new int[this->length];
            
            for (int i = 0; i < this->length; i++) {
                this->array[i] = other[i];
            }
            
            return *this;
        };
        
        // Деструктор
        ~BitArray() {
            delete this->array;    
        };
        
        
        
        // Methods:
        // Функция, возвращающая размер массива
        int size(void) const {
            return this->length;    
        };
        
        // Присвоить i-му биту значение v (0 или 1)
        void setbit(int i, int v) {
            this->array[i] = v;
        };
        
        unsigned operator [] (const unsigned int i) {
            if (i >= this->length) throw std::out_of_range("Index is out of range!");
            
            return this->array[i];
        };
        
        // Операция индексирования
        unsigned operator [] (const unsigned int i) const {
            if (i >= this->length) throw std::out_of_range("Index is out of range!");
            
            return this->array[i];
        };

        
        // Операция вывода - выводит в одну строчку без пробелов значения в массиве - нули или единицы
        friend ostream& operator << (ostream &os, const BitArray &b) {
            for (int i = 0; i < b.size(); i++) os << b[i];
            
            return os;
        };
        
        // Операции сравнения
        bool operator == (const BitArray &other) const {
            if (this->length != other.size()){
                return false;
            }
            
            for (int i = 0; i < this->length; i++) {
                if (this->array[i] != other[i]) {
                    return false;
                }
            }
            return true;
        };
        bool operator != (const BitArray &other) const {
            return !(this == &other);
        };
 
        // Операция & - побитовое "И" двух массивов. Если длина одного массива 
        // меньше длины другого, его недостающие биты считаются равными 0
        BitArray operator &(const BitArray &other) const {
            int new_size = max(other.size(), this->length);
            
            BitArray new_array(new_size);
            
            for (int i = 0; i < new_size; i++) {
                int first = 0;
                int second = 0;
                
                if (i < this->length) first = this->array[i];
                if (i < other.size()) second = other[i];
                
                new_array.setbit(i, first&second);
            }
            
            return new_array;
        };       
        
        
        // Операция | - побитовое "ИЛИ" двух массивов. Если длина одного массива 
        // меньше длины другого, его недостающие биты считаются равными 0
        BitArray operator | (const BitArray &other) const {
            int new_size = max(other.size(), this->length);
            
            BitArray new_array(new_size);
            
            for (int i = 0; i < new_size; i++) {
                int first = 0;
                int second = 0;
                
                if (i < this->length) first = this->array[i];
                if (i < other.size()) second = other[i];
                
                new_array.setbit(i, first|second);
            }
            
            return new_array;
        };
        
        //операция ~ - инвертирование битов массива (0 на 1, 1 на 0)
        BitArray operator ~ (void) const {
            BitArray new_array(this->size());
            for (int i = 0; i < this->length; i++) {
                new_array.setbit(i, !this->array[i]);
            }
            
            return new_array;
        };
        
    private:
        int *array;
        int length;
  
};
#include "bit-array-test.h"

int main()
{
    BitArray a(50), b(80);
    for (int i=0; i<60; i++) b.setbit(i, 1);
    a=b;
    for (int i=0; i<80; i++) b.setbit(i, 0);
    cout << a << endl << b << endl;
    if (a==b) cout << "YES"; else cout << "NO"; cout << endl;
    if (a!=b) cout << "NO"; else cout << "YES"; cout << endl;
    if (a==a) cout << "YES"; else cout << "NO"; cout << endl;
    if (a!=a) cout << "NO"; else cout << "YES"; cout << endl;
    BitArray c = a & b;
    cout << c << endl;
    BitArray d(10); d.setbit(0,1); d.setbit(3,1);
    c = a | b;
    cout << c << endl;
    c = ~c;
    cout << c << endl;
    return 0;
}
