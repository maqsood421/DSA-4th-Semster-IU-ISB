#include <iostream>
#include <cstring>    // For strlen and strcpy
using namespace std;

// Node class to represent a key-value pair in the hashmap
class Node {
public:
    char* key;      // Dynamically allocated key
    int value;      // Associated value
    Node* next;     // Pointer to the next node (for collision handling)

    // Constructor to create a new node
    Node(const char* key, int value) {
        this->key = new char[strlen(key) + 1];
        strcpy(this->key, key);
        this->value = value;
        this->next = nullptr;
    }

    // Destructor to free allocated memory
    ~Node() {
        delete[] key;
    }
};

// HashMap class
class HashMap {
private:
    Node** table;   // Array of pointers to linked list nodes
    int capacity;   // Size of the hash table
    int size;       // Number of key-value pairs

    // Custom hash function for string keys
    int hashFunction(const char* key) const {
        int hash = 0;
        int prime = 31; // A small prime number
        for (int i = 0; key[i] != '\0'; i++) {
            hash = (hash * prime + key[i]) % capacity;
        }
        return hash;
    }

public:
    // Constructor to initialize the hash table
    HashMap(int cap = 10) {
        capacity = cap;
        size = 0;
        table = new Node*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    // Destructor to clean up allocated memory
    ~HashMap() {
        for (int i = 0; i < capacity; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    // Function to insert a key-value pair
    void insert(const char* key, int value) {
        int index = hashFunction(key);
        Node* current = table[index];

        // Check if the key already exists
        while (current != nullptr) {
            if (strcmp(current->key, key) == 0) { // Key found
                current->value = value; // Update value
                return;
            }
            current = current->next;
        }

        // Insert a new node at the head of the list
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        size++;
    }

    // Function to remove a key-value pair
    void remove(const char* key) {
        int index = hashFunction(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (strcmp(current->key, key) == 0) { // Key found
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                size--;
                return;
            }
            prev = current;
            current = current->next;
        }

        cout << "Key not found: " << key << endl;
    }

    // Function to get the value associated with a key
    int get(const char* key) const {
        int index = hashFunction(key);
        Node* current = table[index];

        while (current != nullptr) {
            if (strcmp(current->key, key) == 0) { // Key found
                return current->value;
            }
            current = current->next;
        }

        cout << "Key not found: " << key << endl;
        return -1; // Indicating key not found
    }

    // Function to check if a key exists
    bool contains(const char* key) const {
        int index = hashFunction(key);
        Node* current = table[index];

        while (current != nullptr) {
            if (strcmp(current->key, key) == 0) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Function to display the hashmap
    void display() const {
        for (int i = 0; i < capacity; i++) {
            cout << "Bucket " << i << ": ";
            Node* current = table[i];
            while (current != nullptr) {
                cout << "(" << current->key << ", " << current->value << ") ";
                current = current->next;
            }
            cout << endl;
        }
    }
};

int main() {
    HashMap hashmap(7);

    hashmap.insert("apple", 10);
    hashmap.insert("banana", 20);
    hashmap.insert("orange", 30);
    hashmap.insert("grape", 40);

    hashmap.display();

    cout << "Value for 'apple': " << hashmap.get("apple") << endl;

    hashmap.remove("banana");
    hashmap.display();

    cout << "Contains 'banana': " << (hashmap.contains("banana") ? "Yes" : "No") << endl;

    return 0;
}
