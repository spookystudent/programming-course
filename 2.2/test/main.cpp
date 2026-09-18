#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    int size = 100;
    int sum = 0;

    vector<int> numbers(size);
    generate(numbers.begin(), numbers.end(), []() { return rand() % 100 + 1; });

    // Выводим вектор
    for_each(numbers.begin(), numbers.end(), [](int num) { cout << num << " "; });


    cout << endl << endl;

    // Выводим числа по условию
    for_each(numbers.begin(), numbers.end(), [&sum](int num) {
        if (num % 2 == 0 && (num > 8 && num < 18)) {
            sum += num;
            cout << num << " ";
        }
    });
    cout << endl;

    cout << "Сумма: " << sum << endl;
}
