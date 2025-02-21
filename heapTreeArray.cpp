#include <iostream>
using namespace std;

class Heap {
    public:
        int *arr;
        int size;

        Heap() {
            arr = new int[100];
            size = 0;
        }
        ~Heap() {
            delete [] arr;
        }

        void insert(int val) {
            size++;
            arr[size] = val;
            int index = size;
            while(index > 1) {
                int parent = index / 2;

                if(arr[parent] < arr[index]) {
                    swap(arr[parent], arr[index]);
                    index = parent;
                } else {
                    return;
                }
            }
        }

        // deletes the root node
        void delete_() {

            if(size == 0) {
                cout << "Nothing to delete..\n";
                return;
            }

            // put last element into first index
            arr[1] = arr[size];

            // remove last element
            size--;

            // take root node to its correct position
            int i = 1;
            while( i < size ) {
                int leftIndex = 2 * i;
                int rightIndex = 2 * i + 1;

                if(leftIndex < size && arr[i] < arr[leftIndex]) {
                    swap(arr[i], arr[leftIndex]);
                    i = leftIndex;
                } else if(rightIndex < size && arr[i] < arr[rightIndex]) {
                    swap(arr[i], arr[rightIndex]);
                    i = rightIndex;
                } else {
                    return;
                }
            }
        }

        void print() {
            for(int i = 1; i <= size; i++) {
                cout << arr[i] << ' ';
            } cout << '\n';
        }
};


void heapify(int arr[], int n, int i) {

    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if(left <= n && arr[largest] < arr[left]) {
        largest = left;
    }

    if(right <= n && arr[largest] < arr[right]) {
        largest = right;
    }

    if(largest != i) {
        swap(arr[largest], arr[i]);
        heapify(arr, n, largest);
    }

}


void heapSort(int arr[], int n) {
    int size = n;

    while( size > 1 ) {
        // swap 
        swap(arr[size], arr[1]);
        size--;
        
        heapify(arr, size, 1);
    }
}

int main(void) {

    Heap h;
    h.insert(50);
    h.insert(55);
    h.insert(53);
    h.insert(52);
    h.insert(54);

    h.print();

    h.delete_();
    h.print();
    
    int arr[] = {-1, 54, 53, 55, 52, 50};
    int size = 5;

    for(int i = size/2; i > 0; i--)
        heapify(arr, size, i);

    cout << "Printing the array\n";
    for(auto i: arr)
        cout << i << ' ';

    heapSort(arr, size);
    cout << "\nPrinting the array after heap sort\n";
    for(auto i: arr)
        cout << i << ' ';

    return EXIT_SUCCESS;
}