#include <iostream>
#include <vector>
using namespace std;

void selectionSort(vector<int> &arr) {
    for(int i = 0; i < arr.size() - 1; ++i) {
        int minIndex = i;
        for(int j = i + 1; j < arr.size(); j++) {
            if(arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
}

int main(void) {

    vector<int> arr = {6, 7, 345, 0, 1, 2};
    selectionSort(arr);

    for(int i = 0; i < arr.size(); i++)
        cout << arr[i] << ' ';
    return EXIT_SUCCESS;
}