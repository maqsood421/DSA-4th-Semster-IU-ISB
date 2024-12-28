#include <iostream>
using namespace std;

int main(void) {

    int a = 2;
    cout << ~a << '\n';
    a <<= 1; // left shift
    cout << a << '\n'; // a = 4
    a >>= 1; // right shift
    cout << a << '\n'; // a = 2

    int b = -1;
    b <<= 2;
    cout << b << '\n'; 

    int c = 3;
    cout << (c++) + 1 << '\n';



    int f = 0; int s = 1; int next;

    for(int i = 0; i < 10; i++) {
        cout << f << ' ';
        next = f + s;
        f = s;
        s = next;
    }
    return EXIT_SUCCESS;
}