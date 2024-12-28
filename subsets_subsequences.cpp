#include <iostream>
#include <vector>
using namespace std;

void subsets(vector<int> arr, int index, vector<int> output, vector<vector<int>> &ans) {
     if(index >= arr.size()) {
        ans.push_back(output);
        return;
     }

    // exclude 
    subsets(arr, index + 1, output, ans);

    // inlcude
    int element = arr[index]; 
    output.push_back(element);

    subsets(arr, index + 1, output, ans);
}   

void subsetsBits(vector<int> arr) {
    int totalSubsets = 1 << arr.size(); // 2^n

    for(int mask = 0; mask < totalSubsets; ++mask) {

        for(int i = 0; i < mask; i++) {
            if(mask & (1 << i)) {
                cout << arr[i] << ' ';
            }
        } cout << "\n";
    }
}


void subsequences(string str, string output, int index, vector<string> &ans) {
    if(index >= str.size()) {
        ans.push_back(output);
        return;
    }

    // exclude
    subsequences(str, output, index + 1, ans);

    // include
    char element = str[index];
    output += element;

    subsequences(str, output, index + 1, ans);
}


void subsequencesBits(string str) {
    int totalSubsets = 1 << str.size();

    for(int mask = 0; mask < totalSubsets; mask++) {
        for(int i = 0; i < mask; i++) {
            if(mask & (1 << i)) {
                cout << str[i];
            }
        } cout << '\n';
    }
}

void phoneCombinations(string digits, string output, int index, vector<string>& ans, string phone[]) {
    if(index >= digits.size()) {
        ans.push_back(output);
        return;
    }

    int number = digits[index] - '0';
    string value = phone[number];

    for(int i = 0; i < value.size(); i++) {
        output.push_back(value[i]);
        phoneCombinations(digits, output, index + 1, ans, phone);
        output.pop_back();
    }
}


void permutations(string str, int index, vector<string>& ans) {
    if(index >= str.size()) {
        ans.push_back(str);
        return;
    }

    for(int i = index; i < str.size(); i++) {
        swap(str[index], str[i]);
        permutations(str, index + 1, ans);
        // backtrack
        swap(str[index], str[i]);
    }

}

int main(void) {

    vector<int> arr = {1, 2, 3};
    vector<vector<int>> ans;
    vector<int> output;

    subsetsBits(arr);

    for(int i = 0; i < ans.size(); i++) {
        for(int j = 0; j < ans[i].size(); ++j) {
            cout << ans[i][j] << ' ';
        } cout << '\n';
    }

    vector<string> subseq;
    string outp = "";
    subsequences("abc", outp, 0, subseq);


    for(int i = 0; i < subseq.size(); ++i) {
        for(int j = 0; j < subseq[i].size(); ++j) {
            cout << subseq[i][j];
        } cout << endl;
    }
      
    subsequencesBits("ijk");


    string phone[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> combinations;    
    vector<string> perm;    

    phoneCombinations("234", "", 0, combinations, phone);
    permutations("abc", 0, perm);
    int i = 0;

    for(string st: perm) {
        cout <<  ++i << ": ";
        for(char ch: st) {
            cout << ch;
        } cout << '\n';
    }
        
    
    return EXIT_SUCCESS;
}   