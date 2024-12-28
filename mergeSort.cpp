#include <iostream>
using namespace std;

void merge(int *arr, int s, int e) {
    int mid = (s + e) / 2;
    
    // Lengths of the two subarrays
    int len1 = mid - s + 1;
    int len2 = e - mid;
    
    // Create temporary arrays
    int *first = new int[len1];
    int *second = new int[len2];
    
    // Copy values into temporary arrays
    for (int i = 0; i < len1; i++) {
        first[i] = arr[s + i];
    }
    
    for (int i = 0; i < len2; i++) {
        second[i] = arr[mid + 1 + i];
    }
    
    // Merge the two sorted arrays
    int index1 = 0; // Starting index for the first array
    int index2 = 0; // Starting index for the second array
    int mainArrayIndex = s; // Starting index for the main array
    
    while (index1 < len1 && index2 < len2) {
        if (first[index1] <= second[index2]) {
            arr[mainArrayIndex++] = first[index1++];
        } else {
            arr[mainArrayIndex++] = second[index2++];
        }
    }
    
    // Copy any remaining elements of first array
    while (index1 < len1) {
        arr[mainArrayIndex++] = first[index1++];
    }
    
    // Copy any remaining elements of second array
    while (index2 < len2) {
        arr[mainArrayIndex++] = second[index2++];
    }
    
    // Free up the memory allocated for temporary arrays
    delete[] first;
    delete[] second;
}
 
void mergeSort(int *arr, int s, int e) {
    if (s >= e) return; // Base case

    int mid = (s + e) / 2;
    
    // Recursively sort the first half
    mergeSort(arr, s, mid);
    
    // Recursively sort the second half
    mergeSort(arr, mid + 1, e);
    
    // Merge the two sorted halves
    merge(arr, s, e);
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    mergeSort(arr, 0, n - 1);
    
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    
    return 0;
}
