#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<int> array;
    int N;
    cin >> N;
  
    int K;
    cin >> K;
  
  
    for (int i = 1; i < N + 1; i++) {
        array.push_back(i);
    }
  
  
    int counter = 0;
    int index = 0;
  
    while (array.size() > 1) {
        if (index == N) index = 0;
        
        if(counter == K - 1) {
            array.erase(array.begin() + index);
            N--;
            counter = 0;
        } else {
            counter++;
            index++;
        }
    }
    
    for (auto element : array) cout << element;
}
