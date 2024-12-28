#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int countPrimes(int n);

int main(void) {
    int n; cin >> n;
    cout << "Total Prime numbers upto n are: " << countPrimes(n) << '\n';
    return EXIT_SUCCESS;
}

int countPrimes(int n) {
    if(n <= 2) return 0;

    // Step 1: Use normal sieve to find primes up to sqrt(n)
    int limit = sqrt(n) + 1;
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;

    // regular sieve of eratotheens for find primes up to sqrt(n)
    for(int i = 2; i <= limit; ++i) {
        if(isPrime[i]) {
            primes.push_back(i);

            for(int j = i*i; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }

    // segment sieve for range [2, n - 1]
    vector<bool> primeSegment(n, true);
    primeSegment[0] = primeSegment[1] = false;

    // mark mulitiples of each prime in range [2, n-1]
    for(int prime: primes) {
        int start = max(prime*prime, (2 + prime - 1) / prime*prime);
        for(int j = start; j < n; j += prime) {
            primeSegment[j] = false;
        }
    }


    // count primes in range [2, n-1]
    int totalPrimes = 0;
    for(bool prime: primeSegment) {
        if(prime)
            totalPrimes++;
    }

    return totalPrimes;
}