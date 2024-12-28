#include <iostream>
using namespace std;

int main(void)
{

    // int n; cin >> n;
    // char ch = 'A';
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j <= i; j++) {
    //         cout << char('A' + n - i + j -1) << ' ';
    //     } cout << '\n';
    // }
    // int n; cin >> n;

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n - i - 1; j++) {
    //         cout << ' ';
    //     }
    //     for(int k = n - i - 1; k < n; k++)
    //         cout << '*';
    //     cout << '\n';
    // }

    // int n; cin >> n;  int m = 1;
    // for(int i = 0; i < n; i++) {
    //     for(int s = 0; s < n - i; s++)
    //         cout << ' ';
    //     for(int j = 0; j <= i; j++) {
    //         cout << m++;
    //     } cout << '\n';
    // }
    // int n; cin >> n;
    // for(int i = 0; i < n; i++) {

    //     for(int space = 0; space < i; space++)
    //         cout << ' ';
    //     for(int j = 0; j < n - i; j++) {
    //         cout << i + 1;
    //     } cout << '\n';
    // }

    // int n; cin >> n;  int m = 1;
    // for(int i = 0; i < n; i++) {
    //     for(int s = 0; s < i; s++)
    //         cout << ' ';
    //     for(int j = i; j < n; j++) {
    //         cout << j + 1;
    //     } cout << '\n';
    // }

    // int n; cin >> n;  int m = 1;
    // for(int i = 0; i < n; i++) {
    //     // for(int s = 0; s < n - i; s++)
    //     //     cout << ' ';
    //     // for(int j = 0; j <= i; j++) {
    //     //     cout << j + 1;
    //     // }

    //     for(int k = 0; k <= i; k++)
    //         cout << i + 1 - k;
    //     cout << '\n';
    // }
    int n;
    cin >> n;
    int m = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            cout << j + 1;
        }
        for (int s = 0; s < 2*i; s++)
            cout << '*';

        for (int k = 0; k < n - i; k++)
            cout << n - i - k;

        cout << '\n';
    }

    //     5
    // 1234554321
    // 1234**4321
    // 123****321
    // 12******21
    // 1********1

    return EXIT_SUCCESS;
}
