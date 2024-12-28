#include <iostream>
using namespace std;

int main() {
    const int rows = 20;
    const int cols = 21;
    int rectCount = 0;

    for(int i = 0; i<21; i++){
        for(int j = 0; j<20; j++){
            if(i < 3 || i>=18 || j < 3 || j>=17) cout << "*";
            else if(i>=5 && j>=5 && i<9 && j<= 14){
                rectCount++;
                cout << "*";
            }
            if(i>=12 && j-3 >= 3)
            else cout << ' ';
        }
        cout << endl;
    }

    return 0;
}
