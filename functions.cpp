#include <iostream>
using namespace std;

int power(int, int);
int nCr(int n, int r);
int factorial(int n);
bool isPrime(int n);

int main(void) {

    cout << power(2, 10) << '\n';
    cout << power(10, 2) << '\n';
    cout << power(2, 4) << '\n';

    cout << nCr(8, 2) << '\n';

    if(isPrime(110)) cout << "Prime\n";
    else cout << "Not Prime\n";

    return EXIT_SUCCESS;
}

int power(int a, int b) {

    int ans = 1;
    for(int i = 1; i <= b; i++) 
        ans *= a;

    return ans;
}

int nCr(int n, int r) {
   return factorial(n) / (factorial(r) * factorial(n - r));
}

int factorial(int n) {
    if(n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

bool isPrime(int n) {
    if(n < 2) return false;

    for(int i = 2; i < n; ++i) {
        if(n % i == 0)
            return false;
    }

    return true;
}