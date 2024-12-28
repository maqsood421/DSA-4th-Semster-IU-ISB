#include <iostream>
using namespace std;

void menu() {
    cout << "Menu:\n";
    cout << "1 - Insertion\n";
    cout << "2 - Traversal\n";
    cout << "3 - Delete\n";
    cout << "4 - Update\n";
    cout << "5 - Linear Search\n";
    cout << "6 - Sort\n";
    cout << "7 - Binary Search\n";
    cout << "8 - Exit\n";
}


void insertion(int arr[], int size, int index){
    cout<<"insertion"<<endl;
    cout<<"Enter a number: ";
    cin>>arr[index];
}

void traversal(int arr[], int size){
    cout<<"traversal"<<endl;
    for(int i=0; i<size; i++){
        cout << arr[i] << ' ';
    } cout << endl;
}


void delete_(int arr[], int size){
    cout<<"delete"<<endl;
    int n;
    cout<<"Which number you want to delete"<<endl;
    cin>>n;
    for(int i=0; i<size; i++){
      if(arr[i]==n) {
        cout<<"Successfully deleted\n";
        arr[i] = -1;
        return;
      }
    } 
    cout << endl;
}

void update(int arr[], int size) {
    int elements;
    cout << "How many elements you want to update? ";
    cin >> elements;
    while(elements < size && elements-- > 0) {
        int upd;
        cout << "Enter which element index you want to update? ";
        cin >> upd;
        cout << "Enter the number: ";
        cin >> arr[upd];
    }
}

bool search(int arr[], int size, int target) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == target) 
            return true;
    }
    return false;
}


void bubbleSort(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size - i - 1; ++j) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void selectionSort(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        int minIndex = 0;
        for(int j = 0; j < size - i - 1; j++) {
            if(arr[j] < arr[j + 1]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// binary search
bool binarySearch(int arr[], int size, int target) {
    bubbleSort(arr, size); // first we have to sort the array
    int f = 0;
    int l = size - 1;

    while(f <= l) {
        int mid = (f + l)/2;
        if(arr[mid] == target) return true;
        else if(arr[mid] > target) {
            l = mid - 1;
        } else {
            f = mid + 1;
        }
    }
    return false;
}


int main(void) {
    int arr[] = {3,25, 1, 2, 100};
    // bubbleSort(arr, 5);
    // selectionSort(arr, 5);
    // for(auto it: arr) 
    //     cout << it << ' ';
    
    int choice;
    do {
        menu();
        cout<<"Enter your choice: ";
        cin>> choice;
        switch (choice)
        {
        case 1:
            insertion(arr, 5, 2);
            break;
        case 2:
            traversal(arr, 5);
            break;
        case 3:
            delete_(arr, 5);
            break;
        case 4:
            update(arr, 5);
            break;
        case 5:
            search(arr, 5, 2);
            break;
        case 6:
            bubbleSort(arr, 5);
            break;
        case 7:
            cout << (binarySearch(arr, 5, 2) ? "Found it\n": "Not Found!\n");
            break;
        
        case 8:
            cout << "Exit Successfully!\n";
            break;
        
        default:
            break;
        }
    } while(choice != 8);
    
    return EXIT_SUCCESS;
}