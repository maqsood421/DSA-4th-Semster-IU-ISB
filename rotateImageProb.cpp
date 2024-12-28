#include <iostream>
#include <vector>
using namespace std;

void rotateImage(vector<vector<int>> &arr);


int main(void) {
    vector<vector<int>> arr = {{1, 2, 3, 4},
                               {5, 6, 7, 8},
                               {9, 10, 11, 12},
                               {13, 14, 15, 16}};

    rotateImage(arr);

    
    return EXIT_SUCCESS;
}

void rotateImage(vector<vector<int>> &arr) {
    int col = arr[0].size();
    int row = arr.size();

    for(int r = 0; r < row; ++r) {
        for(int c = r + 1; c < col; ++c) {
            int temp = arr[r][c];
            arr[r][c] = arr[c][r];
            arr[c][r] = temp;
        }
    }

    for(int r = 0; r < col / 2; ++r) {
        for(int c = 0; c < row; ++c) {
            swap(arr[c][r], arr[c][col - 1 - r]);
        }
    }

}