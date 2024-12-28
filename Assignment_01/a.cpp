#include <iostream>
using namespace std;

int removeDuplicates(int arr[], int &size) {
    int cnt = 0;
    for(int i = 0; i < size; i++) {
        bool flag = true;
        for(int j = 0; j < cnt; j++) {
            if(arr[i] == arr[j]) {
                flag = false;
                break;
            }
        }

        if(flag) {
            arr[cnt++] = arr[i];
        }
    }

    size = cnt;  
    return cnt;
}

int main(void) {
    int size = 10;
    int arr[size] = {1, 2, 4, 3, 5, 3, 17, 10, 11, 10};

    cout << "Array before removing duplicates\n";
    for(auto it: arr)
        cout << it << ' ';
    cout << '\n';

    removeDuplicates(arr, size);
    cout << "Array after removing duplicates\n";
    for(int i = 0; i < size; i++) {
        cout << arr[i] << ' ';
    } cout << '\n';

    return EXIT_SUCCESS;
}
