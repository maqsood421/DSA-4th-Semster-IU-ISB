#include <iostream>
using namespace std;

bool binarySearch(int arr[], int target, int size) {
    int s = 0;
    int e = size - 1;

    while(s < e) {
        int mid = (s + e) / 2;
        // int mid = s + (e - s) / 2; // best condition for worst cases
        if(arr[mid] == target) { 
            return true;
        } else if(arr[mid] > target) {
            e = mid - 1;
        } else {
            s = mid + 1;
        } 
    }

    return false;
}


int main(void) {

    int arr[] = {1, 3, 5, 6, 7, 8};
    cout << (binarySearch(arr, 1, 6) ? "Found":"Not Found") << '\n';
    return EXIT_SUCCESS;
}