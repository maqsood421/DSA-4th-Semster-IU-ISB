#include <iostream>
#include <climits>

using namespace std;

class ArrayUtility {
public:
    
    static int findMax(int A[], int i, int j) {
        int maxVal = INT_MIN;
        for (int k = i; k <= j; ++k) {
            if (A[k] > maxVal) {
                maxVal = A[k];
            }
        }
        return maxVal;
    }

    static int findMaxPos(int A[], int i, int j) {
        int maxVal = INT_MIN;
        int maxPos = -1;
        for (int k = i; k <= j; ++k) {
            if (A[k] > maxVal) {
                maxVal = A[k];
                maxPos = k;
            }
        }
        return maxPos;
    }

    static int findMin(int A[], int i, int j) {
        int minVal = INT_MAX;
        for (int k = i; k <= j; ++k) {
            if (A[k] < minVal) {
                minVal = A[k];
            }
        }
        return minVal;
    }

    static int findMinPos(int A[], int i, int j) {
        int minVal = INT_MAX;
        int minPos = -1;
        for (int k = i; k <= j; ++k) {
            if (A[k] < minVal) {
                minVal = A[k];
                minPos = k;
            }
        }
        return minPos;
    }

    static void swap(int A[], int i, int j) {
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
};


int main() {
    int arr[] = {3, 1, 7, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Max value between indices 1 and 3: " << ArrayUtility::findMax(arr, 1, 3) << endl;
    cout << "Position of max value between indices 1 and 3: " << ArrayUtility::findMaxPos(arr, 1, 3) << endl;
    cout << "Min value between indices 1 and 3: " << ArrayUtility::findMin(arr, 1, 3) << endl;
    cout << "Position of min value between indices 1 and 3: " << ArrayUtility::findMinPos(arr, 1, 3) << endl;

    cout << "Array before swap: ";
    for (int i = 0; i < n; ++i) cout << arr[i] << " ";
    cout << endl;

    ArrayUtility::swap(arr, 1, 3);

    cout << "Array after swap: ";
    for (int i = 0; i < n; ++i) cout << arr[i] << " ";
    cout << endl;

    return 0;
}
