#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int> &arr) {
    for(int i = 1; i < arr.size(); ++i) {
        int temp = arr[i];
        int j = i - 1;

        while(j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j]; 
            j--;
        }

        arr[j + 1] = temp;
    }
}

int main(void) {

    vector<int> arr = {6, 7, 345, 0, 1, 2};

    insertionSort(arr);
    for(int i = 0; i < arr.size(); i++)
        cout << arr[i] << ' ';

        
    return EXIT_SUCCESS;
}