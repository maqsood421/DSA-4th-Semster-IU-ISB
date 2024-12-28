#include <iostream>
using namespace std;

int main(void) {
    // int guessedNumber = 10;
    // int number;

    // cout << "Enter a number: ";
    // cin >> number;

    // while(number != guessedNumber) {
        
    //     if(number > guessedNumber) {
    //         cout << "Try less then " << number << '\n';
    //     } else {
    //         cout << "Try greater then " << number << '\n';
    //     }
    //     cout << "Enter a number: ";
    //     cin >> number;
    // }
    // cout << "Hurrah! you guessed the number!\n";
    

    // // 2nd program
    // int n; 
    // cout << "Enter a number: "; cin >> n;
    // if(!(n & 0x1))
    //     cout << "Even: " << n << '\n';
    // else 
    //     cout << "Odd:  " << n << '\n';
    
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < i; j++)
    //         cout << (i & 0x1 ? "#":"$");
    //     cout << '\n';
    // }

    // 3rd program
    int n;
    int fact=1;

    cout<<"enter a number: ";
    cin>>n;
    for(int i=1; i<=n; i++){
        fact*=i;
    }
    cout<<"Factorial is: "<< fact << endl;    
    return EXIT_SUCCESS;
}
