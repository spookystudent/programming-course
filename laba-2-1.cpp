#include <iostream>
#include <string>
#include <cmath>

using namespace std;
 
int main() {
    // Напишите программу, сортирующую символы строки, введенные с клавиатуры (в строке содержатся ТОЛЬКО английские символы; заглавные буквы имеют больший приоритет, чем прописные, т.е. заглавные буквы должны находиться в начале строки), в алфавитном порядке. Например, если введено: "СbА", в результате надо получить "ACb".

    // Входные данные
    // Строка с английскими символами (до 255 символов).
    // Выходные данные
    // Строка с отсортированным порядком символов.
    // Пример входных данных
    // ajJGFghHfGHGHffsdgfgshdgfsdgfhsdgfgsdh
    // Пример выходных данных
    // FGGGHHHJadddddfffffffggggggghhhhjsssss
    
    string str = ""; cin >> str;
    int size = str.length();

    
    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            if (str[i] > str[j]) {
                char char_i = str[i];
                str[i] = str[j];
                str[j] = char_i;
            }
        }
    }
    
    cout << str;

    return 0;
}
 
