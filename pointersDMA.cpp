#include <iostream>
using namespace std;

int main(void) {
    // Allocate a single character
    char *chr = new char;
    cout << "sizeof(*chr): " << sizeof(*chr) << '\n'; // prints 1 byte

    // Allocate an array of 5 integers
    int *ptr = new int[5];
    
    // Correct way to assign values to the array
    ptr[0] = 1;
    ptr[1] = 2;
    ptr[2] = 3;
    ptr[3] = 4;
    ptr[4] = 5;

    // Alternatively, you can use a loop to assign values
    /*
    for (int i = 0; i < 5; ++i) {
        ptr[i] = i + 1;
    }
    */

    // Print the array values
    for (int i = 0; i < 5; ++i) {
        cout << "ptr[" << i << "] = " << ptr[i] << '\n';
    }


    // 2D arrays dynamic memory allocation
    int **arr2d = new int*[5]; // created 5 rows

    for(int i = 0; i < 5; ++i) { //2d array 5x5 
        arr2d[i] = new int[5]; 
    }

    // deleting 2d array
    for(int i = 0; i < 5; i++) {
        delete []arr2d[i]; 
    } 
    delete []arr2d;


    // creating the jaggered array
    int **jaggeredArr = new int*[5];
    for(int i = 0; i < 5; i++)
        jaggeredArr[i] = new int[i + 1];

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < i + 1; j++)
            jaggeredArr[i][j] = i + 1;
    }

    
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < i + 1; j++)
            cout << jaggeredArr[i][j] << ' ';
        cout << '\n';
    }


    // releasing jaggered array
    for(int i = 0; i < 5; i++) 
        delete []jaggeredArr[i];

    delete []jaggeredArr;


    // Deallocate the dynamically allocated memory
    delete chr;      // For single char
    delete[] ptr;    // For array of ints

    return EXIT_SUCCESS;
}
