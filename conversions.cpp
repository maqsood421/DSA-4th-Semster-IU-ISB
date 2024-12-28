#include <iostream>
#include <algorithm>
using namespace std;

string decToBin(int dec);
int binToDec(string bin);


int main(void)
{
    cout << decToBin(10) << "\n";
    cout << binToDec("101") << '\n';
    return EXIT_SUCCESS;
}

string decToBin(int dec)
{
    string ans;
    while (dec != 0)
    {
        if(dec & 1) ans += "1";
        else ans += "0";
        dec >>= 1;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int binToDec(string bin) {
    
    int ans = bin[bin.size() - 1] - '0';
    int pow2 = 2;
    for(int i = bin.size() - 2; i >= 0; i--) {
        if(bin[i] - '0') {
            ans += pow2;
            pow2 *= 2;
        } else {
            pow2 *= 2;
        }
    }

    return ans;
}