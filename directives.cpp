#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;

#define PI 3.141
#define SQUARE(r) (PI * (r) * (r)) // inline macro

#define MESSAGE "Hello, World"
#undef MESSAGE // remove the MESSAGE macro

#define TO_STRING(x) #x // converts macro argument into a string
#define CONCAT(x, y) x##y // Concatenates two tokens

#define TEST 10

// Define this to enable debug output
#define DEBUG

#ifdef DEBUG
    #define dbg(...) debug(__FILE__, __LINE__, #__VA_ARGS__, __VA_ARGS__)
#else
    #define dbg(...)  // No output when DEBUG is not defined
#endif

// Helper function to print arguments
template <typename T>
void debug_out(const T& t) {
    cerr << t;
}

// Overload for vector
template <typename T>
void debug_out(const vector<T>& vec) {
    cerr << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cerr << vec[i];
        if (i != vec.size() - 1) {
            cerr << ", ";
        }
    }
    cerr << "]";
}

// Overload for set
template <typename T>
void debug_out(const set<T>& s) {
    cerr << "{";
    for (auto it = s.begin(); it != s.end(); ++it) {
        cerr << *it;
        if (next(it) != s.end()) {
            cerr << ", ";
        }
    }
    cerr << "}";
}

// Overload for map
template <typename K, typename V>
void debug_out(const map<K, V>& m) {
    cerr << "{";
    for (auto it = m.begin(); it != m.end(); ++it) {
        cerr << it->first << ": " << it->second;
        if (next(it) != m.end()) {
            cerr << ", ";
        }
    }
    cerr << "}";
}

template <typename T, typename... Args>
void debug_out(const T& t, const Args&... args) {
    debug_out(t);
    cerr << ", ";
    debug_out(args...);
}

// Wrapper to handle multiple arguments and their names
template <typename... Args>
void debug(const char* file, int line, const char* names, const Args&... args) {
    cerr << "[" << file << ":" << line << "][" << names << "]: ";
    debug_out(args...);
    cerr << endl; // End the debug line
}

int main() {
    int x = 5;
    int y = 10;
    vector<int> vec = {1, 2, 3, 4, 5};
    set<int> s = {1, 2, 3};
    map<int, string> m = {{1, "one"}, {2, "two"}};

    dbg(x);                 // Prints: [filename:line][x]: 5
    dbg(x, y);              // Prints: [filename:line][x, y]: 5, 10
    dbg(vec);               // Prints: [filename:line][vec]: [1, 2, 3, 4, 5]
    dbg(s);                 // Prints: [filename:line][s]: {1, 2, 3}
    dbg(m);                 // Prints: [filename:line][m]: {1: one, 2: two}
    
    cout << SQUARE(21.4) << '\n';
    cout << TO_STRING(Maqsood) << '\n';
    int xy = 10;
    cout << CONCAT(x, y) << "\n";
    
    return 0;
}
