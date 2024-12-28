#include <iostream>
using namespace std; 

string digits[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int factorial(int n) {
    // base case
    if(n == 0 || n == 1) 
        return 1;

    // recursive relation 
    return n * factorial(n - 1);
}

int power2(int n) {
    //  base case
    if(n == 0) return 1;

    return 2 * power2(n - 1);
}

void print(int n) { 
    // base case
    if(n == 0) 
         return;
    
    // processing
    cout << n << '\n';

    // recursive relation
    print(n - 1);
}

int fibonacci(int n) {
    // base cases
    if(n == 0) return 0;
    if(n == 1) return 1;

    // recursive relation
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void sayDigits(int n) {
    if (n < 0) {
        cout << "negative" << '\n';
        n = -n;
    }

    if (n == 0) return;

    // recursive call
    sayDigits(n / 10);

    // process the current digit
    cout << digits[n % 10] << '\n';
}


void reverseInteger(int n) {
    // base case 
    if(n == 0) return;

    // processing ; it prints the last digit
    cout << n % 10; 

    // recursive call
    reverseInteger(n / 10);
}

bool isSorted(int arr[], int size) {
    // base call
    if(size == 1 || size == 0) return true;
    
    if(arr[0] > arr[1]) return false;
    else {
        bool ans = isSorted(arr + 1, size - 1);
        return ans;
    }
}


int sum(int arr[], int size) {
    if(size == 0) {
        return 0;
    }

    return arr[0] + sum(arr + 1, size - 1);
}


bool linearSearch(int arr[], int size, int target) {
    if(size == 0) return false;

    if(arr[0] == target) return true;
    else {
        return linearSearch(arr + 1, size - 1, target);
    }
}

bool binarySearch(int arr[], int s, int e, int target) {
    if(s > e) {
        return false;
    } 

    int mid = s + (e - s) / 2;
    if(arr[mid] == target) {
        return true;
    } else if(target > arr[mid]) {
        s = mid + 1;
        return binarySearch(arr, s, e, target);
    } else {
        e = mid - 1;
        return binarySearch(arr, s, e, target);
    } 
}

 
void reverseString(string &str, int s, int e) {    
    if(s > e) return;

    swap(str[s], str[e]);
    reverseString(str, s + 1, e - 1);
}

bool checkPalindrome(string str, int s, int e) {    
    if(s > e) return false;

    if(str[s] != str[e]) return false;
    checkPalindrome(str, s + 1, e - 1);

    return true;
}


int power(int base, int exponent) {
    
    if(exponent == 0) return 1;
    if(exponent == 1) return base;

    if(exponent & 0x1) {
        return base * power(base, exponent / 2) *  power(base, exponent / 2);
    } else {
        return power(base, exponent / 2) * power(base, exponent / 2);
        
    }
}


void bubbleSort(int arr[], int size) {
    if(size == 1) return;


    for(int i = 0; i < size - 1; i++) {
        if(arr[i] > arr[i + 1]) {
            swap(arr[i], arr[i + 1]);
        }
    }

    bubbleSort(arr, size - 1);

}

void selectionSort(int arr[], int size) {
    if(size <= 1) return;

    int minIndex = 0;
    for(int i = 1; i < size; i++) {
        if(arr[i] < arr[minIndex]) {
            minIndex = i;
        }
    }

    swap(arr[0], arr[minIndex]);

    selectionSort(arr + 1, size - 1);
}

void insertionSort(int arr[], int size) {
    if(size <= 1) {
        return;
    }

    insertionSort(arr, size - 1);

    int temp = arr[size - 1];
    int j = size - 2;

    while(j >= 0 && arr[j] > temp) {
        arr[j + 1] = arr[j];
        j--;
    }

    arr[j + 1] = temp;
}


int main(void) {
    cout << "Factorial of 5 is: " << factorial(5) << '\n';
    cout << "2^5 is: " << power2(5) << '\n';
    print(10);

    sayDigits(12340);

    reverseInteger(12345);

    int arr[] = {1, 5, 4, 10, 2};


    cout << "\nSorted ? " << isSorted(arr, 5) << '\n';
    cout << "\nSum is: " << sum(arr, 5) << '\n';
    cout << "\n4 is Present? : " << linearSearch(arr, 5, 4) << '\n';

    cout << binarySearch(arr, 0, 4, 8) << '\n';

    string str = "abcde";
    reverseString(str, 0, 4);

    cout << str << '\n';

    if(checkPalindrome("abcdcbc", 0, 6)) cout << "It is palindrome\n";
    else cout << "It is not palindrome\n";

    cout << power(2, 10) << '\n';

    // bubbleSort(arr, 5);
    // selectionSort(arr, 5);
    insertionSort(arr, 5);
    for(int i = 0; i < 5; i++)
        cout << arr[i] << ' ';

    return EXIT_SUCCESS;
}
