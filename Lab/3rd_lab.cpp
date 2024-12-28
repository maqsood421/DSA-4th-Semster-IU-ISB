#include <iostream>
using namespace std;

// Displays the menu options for the user.
void menu() {
    cout << "\nMenu:\n"
         << "1 - Insertion\n"
         << "2 - Traversal\n"
         << "3 - Delete\n"
         << "4 - Update\n"
         << "5 - Linear Search\n"
         << "6 - Sort\n"
         << "7 - Binary Search\n"
         << "8 - Exit\n";
}

// Inserts a number at a specified index in the array.
void insertion(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        cout << "Invalid index!\n";
        return;
    }
    cout << "Enter a number to insert at index " << index << ": ";
    cin >> arr[index];
    cout << "Number inserted successfully!\n";
}

// Traverses the array and prints all elements.
void traversal(int arr[], int size) {
    cout << "Array elements: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

// Deletes a specified number from the array by marking it as -1.
void deleteElement(int arr[], int size) {
    int target;
    cout << "Enter the number to delete: ";
    cin >> target;
    bool found = false;

    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            arr[i] = -1; // Marking deleted element
            found = true;
            cout << "Number " << target << " deleted successfully!\n";
        }
    }

    if (!found) {
        cout << "Number not found in the array!\n";
    }
}

// Updates a specific index in the array with a new value.
void update(int arr[], int size) {
    int index, value;
    cout << "Enter the index to update (0 to " << size - 1 << "): ";
    cin >> index;
    if (index < 0 || index >= size) {
        cout << "Invalid index!\n";
        return;
    }
    cout << "Enter the new value: ";
    cin >> value;
    arr[index] = value;
    cout << "Element updated successfully!\n";
}

// Searches for a target number in the array using linear search.
bool linearSearch(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) 
            return true; // Target found
    }
    return false; // Target not found
}

// Sorts the array in ascending order using Bubble Sort.
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    cout << "Array sorted successfully using Bubble Sort!\n";
}

// Searches for a target in the array using Binary Search (after sorting).
bool binarySearch(int arr[], int size, int target) {
    bubbleSort(arr, size); // Ensure the array is sorted
    int start = 0, end = size - 1;

    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] == target)
            return true; // Target found
        else if (arr[mid] < target)
            start = mid + 1; // Narrow search to right half
        else
            end = mid - 1; // Narrow search to left half
    }
    return false; // Target not found
}

int main() {
    int arr[] = {3, 25, 1, 2, 100}; // Initial array
    int size = sizeof(arr) / sizeof(arr[0]);
    int choice;

    do {
        menu(); // Show menu options
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int index;
                cout << "Enter the index (0 to " << size - 1 << "): ";
                cin >> index;
                insertion(arr, size, index); // Insert element
                break;
            }
            case 2:
                traversal(arr, size); // Traverse and print array
                break;
            case 3:
                deleteElement(arr, size); // Delete an element
                break;
            case 4:
                update(arr, size); // Update an element
                break;
            case 5: {
                int target;
                cout << "Enter the number to search: ";
                cin >> target;
                cout << (linearSearch(arr, size, target) ? "Number found!\n" : "Number not found!\n");
                break;
            }
            case 6:
                bubbleSort(arr, size); // Sort the array
                break;
            case 7: {
                int target;
                cout << "Enter the number to search using Binary Search: ";
                cin >> target;
                cout << (binarySearch(arr, size, target) ? "Number found!\n" : "Number not found!\n");
                break;
            }
            case 8:
                cout << "Exiting program. Goodbye!\n"; // Exit program
                break;
            default:
                cout << "Invalid choice! Please try again.\n"; // Invalid input
        }
    } while (choice != 8); // Repeat until user exits

    return 0;
}
