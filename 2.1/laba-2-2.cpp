#include <iostream>

using namespace std;

int main() {
    
    int size = 6;
    
    int array[size*size];
    
    int matrix[size][size];
    
    
    for (int i = 0; i < size*size; i++) {
        cin >> array[i];
    }
    
    int direction_x = 1;
    int direction_y = 1;
    bool updown = false;
    
    int line = 0;
    int row = 0;

    int target_x = size - 1;
    int target_y = size - 1;
    int spin_x = size - 1;
    int spin_y = size - 1;
    
    for (int i = 0; i < size*size; i++) {
        if (row == target_x) {
            updown = true;
            direction_x *= -1;
            
            if (direction_x < 0) {
                target_x = size - 1 - spin_x;
                spin_x -= 1;
            } else {
                target_x = spin_x;
            }
                
        } else if (line == target_y) {
            updown = false;
            direction_y *= -1;
            
            if (direction_y < 0) {
                target_y = size - 1 - spin_y + 1;
                spin_y -= 1;
            } else {
                target_y = spin_y;
            }
            
        }
        
        matrix[line][row] = array[i];
        
        if (updown) {
            line += direction_y * 1;
        } else {
            row += direction_x * 1;
        }
    }
    
    for (int line = 0; line < size; line++) {
        for (int row = 0; row < size; row++) {
            cout << matrix[line][row] << "\t";
        }
        cout << endl;
    }
    return 0;
}
