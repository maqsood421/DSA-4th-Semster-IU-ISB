#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size - i- 1; ++j) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}


int main(void) {

    int arr[] = {1, 10, 6, 76, 2, 3, 4, 20, 1, 0};
    for(int it: arr)
        cout << it << " ";
    cout << '\n';

    bubbleSort(arr, 10);

    for(int it: arr)
        cout << it << ' ';

    return 0;
}