#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>> &arr, vector<vector<bool>>& isVisited, int i, int j, int r, int c) {
    return (i >= 0 && i <= r && j >= 0 && j <= c && arr[i][j] == 1 && !isVisited[i][j]);
}

string ratInMaze (vector<vector<int>> arr) {
    string path = "";
     // Create visited array
    vector<vector<bool>> isVisited(arr.size(), vector<bool>(arr[0].size(), false));

    int r = arr.size() - 1;
    int c = arr[0].size() - 1;

    int i = 0;
    int j = 0;

    while(i != r || j != c) {
        // call for down
        isVisited[i][j] = 1;
        if(isSafe(arr, isVisited, i + 1, j, r, c)) {
            path += "D";
            i++;
        }
        // call for left
        else if(isSafe(arr, isVisited, i, j - 1, r, c)) {
            path += "L";
            j--;
        }
        // call for right
        else if(isSafe(arr, isVisited, i, j + 1, r, c)) {
            path += "R";
            j++;
        }
        // call for up
        else if(isSafe(arr, isVisited, i - 1, j, r, c)) {
            path += "U";
            i--;
        } else {
            return "No path found!";
        }
    } 

    return path;
}


void rateInMazeFindPaths(vector<vector<int>> &arr, vector<vector<bool>>& isVisited, vector<string> &ans, string path, int i, int j, int r, int c) {
    // Base case: Reached the destination
    if(i == r && j == c) {
        ans.push_back(path);
        return;
    }
    
    // Mark the current cell as visited
    isVisited[i][j] = true;

    // Move Down
    if(isSafe(arr, isVisited, i + 1, j, r, c)) {
        path.push_back('D');
        rateInMazeFindPaths(arr, isVisited, ans, path, i + 1, j, r, c);
        path.pop_back(); // Backtrack
    }

    // Move Left
    if(isSafe(arr, isVisited, i, j - 1, r, c)) {
        path.push_back('L');
        rateInMazeFindPaths(arr, isVisited, ans, path, i, j - 1, r, c);
        path.pop_back(); // Backtrack
    }

    // Move Right
    if(isSafe(arr, isVisited, i, j + 1, r, c)) {
        path.push_back('R');
        rateInMazeFindPaths(arr, isVisited, ans, path, i, j + 1, r, c);
        path.pop_back(); // Backtrack
    }

    // Move Up
    if(isSafe(arr, isVisited, i - 1, j, r, c)) {
        path.push_back('U');
        rateInMazeFindPaths(arr, isVisited, ans, path, i - 1, j, r, c);
        path.pop_back(); // Backtrack
    }

    // Unmark the current cell to allow other paths
    isVisited[i][j] = false;
}


int main(void) {
    
    vector<vector<int>> arr = {{1, 0, 0, 0},
                               {1, 1, 0, 0},
                               {1, 1, 0, 0},
                               {0, 1, 1, 1},
    };

    cout << ratInMaze(arr) << '\n';

    vector<vector<bool>> isVisited(arr.size(), vector<bool>(arr[0].size(), false));
    vector<string> ans;

    rateInMazeFindPaths(arr, isVisited, ans, "", 0, 0, arr.size() - 1, arr[0].size() - 1);

    for(string str: ans)
        cout << str << ' ';

    return EXIT_SUCCESS;
}