#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N, K, M; cin >> N >> K >> M;
    
    vector<int> books;
    
    for (int i = 1; i <= N; i++) books.push_back(i);
    
    for (int i = 0; i < M; i++) {
        rotate(books.begin(), books.begin() + K, books.begin() + N);
    }
    
    for (auto b:books) cout << b << " ";
}
