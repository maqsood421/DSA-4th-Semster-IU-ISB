#include <iostream>
using namespace std;

int getSum(int arr[], int size) {
    int sum = 0;
    for(int i = 0; i < size; ++i)
        sum += arr[i];


    return sum;
}

int main(void) {
    // int var = 3;
    // int *ptr = &var;
    // int *ptr2 = 0; // points to null
    
    // cout << sizeof(ptr) << " bytes\n";
    
    // cout << "var address: " << &var << '\n';
    // cout << "ptr address: "  << ptr << '\n';
    // cout << "ptr value: " << ++(*ptr) << '\n';
    // cout << "ptr2 address: "  << ptr2 << '\n';


    // // pointer to int is created, and points to some garbage address 
    // // int *p;
    // int *p = nullptr; // good practice 
    // cout << "*p value: " << *p << '\n';


    // pointers with arrays

    int arr[10] = {1, 2, 3, 4};
    cout << "Address of first memory block is: " << arr << '\n';
    cout << "Value of first memory block is: " << *arr << '\n';
    cout << "Address of arr[0] memory block is: " << &arr[0] << '\n';

    cout << "sizeof arr[0] is: " << sizeof(*arr) << '\n';
    cout << "sizeof &arr[0] is: " << sizeof(&arr) << '\n';

    cout << "Sum: " << getSum(arr+2, 4) << '\n'; // you can pass half of array

    // cout << &arr[0] << '\n'; // these are same prints the address of a first block of memory of array 
    // cout << &arr << '\n';
    // cout << arr << '\n';

    int i = 3;
    cout << "Value of index at index 3 is: " << i[arr] << '\n'; // same as arr[i]; where i = 3;

     
     char str[6] = "abcde";
     cout << str << '\n';
     cout << "address of str: " << &str << '\n';

     char *c = str;
     cout << "size of *c: " << sizeof(c) << '\n';
     cout << c << '\n'; // prints the whole string
     cout << *c << '\n'; // prints the first character
     
     char temp = 'z';
     char *pt = &temp;
     cout << pt << '\n'; // prints the random characters upto null terminated character 


     cout << "-----------------------------------------------\n";
    
    int *sptr = 0;
    int v = 2;
    sptr = &v;

    int **dptr = &sptr; // double pointer, points to pointer

    cout << "address of dptr: " << &dptr << '\n';
    cout << "address of sptr: " << dptr << '\n';
    cout << "value of dptr to sptr: " << **dptr << '\n';


    char *chr = new char;
    cout << "sizeof(*chr): " << sizeof(*chr) << '\n'; // prints 1 byte


    return EXIT_SUCCESS;
}