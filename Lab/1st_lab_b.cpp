#include <iostream>
using namespace std;

int balance = 0;

void deposit() {
    int money;
    cout << "Enter money to be deposit: ";
    cin >> money;
    cout << "Your new balance is: Rs. " << (balance += money) << '\n';
}

void withdraw() {
    int money;
    cout << "Enter money to withdraw: ";
    cin >> money;
    
    if(money > balance) {
        cout << "Insufficient Balance!\n";
    } else {
        cout << "Successfully deposit :)\n";
        cout << "Your new balance is: Rs. " << (balance -= money) << '\n';
    }
}


void showBalance() {
    cout << "Your balance is: " << balance << '\n'; 
}

void menu() {
    int option;
    cout << "1 for create account\n";
    cout << "2 for Check Balance\n";
    cout << "3 for deposit money\n";
    cout << "4 for Withdrawal money\nEnter(1-4): ";
    cin >> option;
    
    switch (option)
    {
    case 1:
        cout << "Under creation\n";
        // createAccount();
        break;
    case 2:
        showBalance();
        break;
    case 3:
        deposit();
        break;
    case 4:
        withdraw();
        break;
    
    default:
        cout << "Invalid option! Try again\n";
        menu();
        break;
    }
}

int main(void) {
    char quit;
    do {
        menu();
        cout << "Wanna quit? (y/n): ";
        cin >> quit;
    } while(quit != 'y' || quit != 'Y');
    
    return EXIT_SUCCESS;
}