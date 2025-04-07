#include <iostream>
#include <string>
#include <cmath>

 
int main() {
    int max_sum = 27;
    int summs[max_sum + 1] = {0};
    
    // 0 0 0 0
    // 0 0 1 1
    // . . . i + j + k
    // 9 9 9 18
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                ++summs[i + j + k];
            }
        }
    }
 
    int result = 0;
    for (int i = 1; i < max_sum; ++i) {
        result += summs[i] * summs[i];
    }
 
    std::cout << result + 1;
 
    return 0;
}
