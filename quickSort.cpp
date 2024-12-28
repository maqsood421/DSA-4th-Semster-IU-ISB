#include <iostream>
using namespace std;

int partition(int arr[], int s, int e) {
    int pivot = arr[s];

    int cnt = 0;
    for(int i = s + 1; i <= e; i++) {
         if(arr[i] <= pivot) cnt++;
    }

    // place pivot at right position
    int pivotIndex = s + cnt;
    // swap the pivot element at right position
    swap(arr[pivotIndex], arr[s]);

    int i = s;
    int j = e;

    while(i < pivotIndex && j > pivotIndex) {
         while(arr[i] < pivot) i++;
         while(arr[j] > pivot) j--;

         if(i < pivotIndex && j > pivotIndex)
            swap(arr[i++], arr[j--]);
    }

    return pivotIndex; 
}

 
void quickSort(int arr[], int s, int e) {
    if(s >= e) return;

    int pivot = partition(arr, s, e);

    // sort left part
    quickSort(arr, s, pivot - 1);
    // sort right part
    quickSort(arr, pivot + 1, e); 
}


int main(void) {
 
    int arr[] = {9, 6, 1, 2, 3, 9, 10, 10, 10};
    quickSort(arr, 0, 8);

    for(auto it: arr)
        cout << it << ' ';
    
    return EXIT_SUCCESS;  
}