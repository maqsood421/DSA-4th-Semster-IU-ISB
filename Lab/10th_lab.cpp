#include <iostream>
using namespace std;

// Recursive function to solve the problem
void moveItems(int n, char fromShelf, char toShelf, char tempShelf) {
    if (n == 1) {
        cout << "Move item from " << fromShelf << " to " << toShelf << endl;
        return;
    }
    // Step 1: Move n-1 items from 'fromShelf' to 'tempShelf' using 'toShelf' as temporary storage
    moveItems(n - 1, fromShelf, tempShelf, toShelf);

    // Step 2: Move the nth item directly from 'fromShelf' to 'toShelf'
    cout << "Move item from " << fromShelf << " to " << toShelf << endl;

    // Step 3: Move the n-1 items from 'tempShelf' to 'toShelf' using 'fromShelf' as temporary storage
    moveItems(n - 1, tempShelf, toShelf, fromShelf);
}


int main() {
    int n; // Number of items on Shelf A
    cout << "Enter the number of items: ";
    cin >> n;

    // Call the recursive function
    moveItems(n, 'A', 'C', 'B');

    return 0;
}

