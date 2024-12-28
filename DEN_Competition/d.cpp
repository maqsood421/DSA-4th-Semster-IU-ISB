#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class LRUCache {
public:
    class Node {
    public:
        int key;
        string value;
        Node* next;
        Node* prev;
        Node(int key, string value) {
            this->key = key;
            this->value = value;
            next = nullptr;
            prev = nullptr;
        }
    };

    int capacity;
    unordered_map<int, Node*> mp;
    Node* head = new Node(-1, "");
    Node* tail = new Node(-1, "");

    LRUCache(int capacity) {
        this->capacity = capacity;
        head->next = tail;
        tail->prev = head;
        cout << "Initialized cache with capacity " << capacity << endl;
    }

    void deleteNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void insertAtHead(Node* node) {
        Node* temp = head->next;
        head->next = node;
        node->prev = head;
        node->next = temp;
        temp->prev = node;
    }
    
    string get(int key) {
        if (mp.find(key) == mp.end()) {
            return "-1";  // Key not found
        } else {
            Node* currNode = mp[key];
            deleteNode(currNode);
            insertAtHead(currNode);  // Move node to the head (most recently used)
            cout << "Get " << key << ": \"" << currNode->value << "\" -> Cache updated to ";
            display();
            return currNode->value;
        }
    }
    
    void put(int key, string value) {
        if (mp.find(key) != mp.end()) {
            Node* currNode = mp[key];
            currNode->value = value;
            deleteNode(currNode);
            insertAtHead(currNode);
        } else {
            Node* newNode = new Node(key, value);
            if (mp.size() == capacity) {
                Node* todel = tail->prev;
                mp.erase(todel->key);
                deleteNode(todel);
                delete todel;
            }
            insertAtHead(newNode);
            mp[key] = newNode;
        }
        cout << "Put " << key << ": Cache = ";
        display();
    }

    void display() {
        Node* temp = head->next;
        cout << "[";
        bool first = true;
        while (temp != tail) {
            if (!first) cout << ", ";
            cout << "\"" << temp->value << "\"";
            temp = temp->next;
            first = false;
        }
        cout << "]" << endl;
    }
};

int main() {
    LRUCache cache(3);

    cache.put(1, "Data1");  // Cache = ["Data1"]
    cache.put(2, "Data2");  // Cache = ["Data2", "Data1"]
    cache.get(1);           // Access "Data1", update cache to ["Data1", "Data2"]
    cache.put(3, "Data3");  // Cache = ["Data3", "Data1", "Data2"]
    cache.put(4, "Data4");  // "Data2" removed, Cache = ["Data4", "Data3", "Data1"]
    cout << "Get 2: " << cache.get(2) << endl;  // "Data2" not in cache, output -1

    cout << "Display: ";
    cache.display();  // Display current cache content

    return 0;
}
