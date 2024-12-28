#include <iostream>
using namespace std;

// A linked list is a linear data structure consisting of nodes connected by pointers
class LinkedList {
public:
    int val;              // Node value
    LinkedList* next;     // Pointer to the next node

    // Constructor to initialize node value
    LinkedList(int val) {
        this->val = val;
        this->next = nullptr;
    }

    // Destructor to free memory
    ~LinkedList() {
        if (this->next != nullptr) {
            delete next;
            this->next = nullptr;
        }
    }
};

// Function to print the linked list
void print(LinkedList* node) {
    if (node == nullptr) return;
    cout << node->val << " ";
    print(node->next);
}

// Insert a new node at the head of the linked list
void insertAtHead(LinkedList*& node, int data) {
    LinkedList* temp = new LinkedList(data);
    temp->next = node;
    node = temp;
}

// Insert a new node at the tail of the linked list
void insertAtTail(LinkedList*& node, int data) {
    LinkedList* temp = new LinkedList(data);
    if (node == nullptr) {
        node = temp;
        return;
    }

    LinkedList* tail = node;
    while (tail->next != nullptr) {
        tail = tail->next;
    }
    tail->next = temp;
}

// Insert a new node at the middle of the linked list
void insertAtMiddle(LinkedList*& node, int data) {
    if (node == nullptr) {
        insertAtHead(node, data);
        return;
    }

    LinkedList* slow = node;
    LinkedList* fast = node;

    while (fast->next != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    LinkedList* temp = new LinkedList(data);
    temp->next = slow->next;
    slow->next = temp;
}

// Insert a new node at a specific position in the linked list
void insertAtPos(LinkedList*& node, int pos, int data) {
    if (pos == 1) {
        insertAtHead(node, data);
        return;
    }

    LinkedList* curr = node;
    int cnt = 1;
    while (cnt++ < pos - 1) {
        curr = curr->next;
    }

    LinkedList* temp = new LinkedList(data);
    temp->next = curr->next;
    curr->next = temp;
}

// Delete a node at a specific position in the linked list
void deleteNodeAtPosition(LinkedList*& node, int pos) {
    if (node == nullptr || pos < 1) {
        cout << "Invalid position or empty list.\n";
        return;
    }

    if (pos == 1) { // Deleting the head node
        LinkedList* temp = node;
        node = node->next;
        delete temp;
        return;
    }

    LinkedList* curr = node;
    LinkedList* prev = nullptr;
    int cnt = 1;

    // Traverse to the node at the given position
    while (cnt < pos && curr != nullptr) {
        prev = curr;
        curr = curr->next;
        cnt++;
    }

    if (curr == nullptr) { // Position exceeds list length
        cout << "Position exceeds the list length.\n";
        return;
    }

    // Update links and delete the node
    prev->next = curr->next;
    delete curr;
}

int main() {
    LinkedList* node = nullptr;

    // Insert elements at the tail
    cout << "Insert 1 at tail\n";
    insertAtTail(node, 1);
    print(node);
    cout << endl;

    cout << "Insert 2, 3, 4, 5 at tail\n";
    insertAtTail(node, 2);
    insertAtTail(node, 3);
    insertAtTail(node, 4);
    insertAtTail(node, 5);
    print(node);
    cout << endl;

    // Insert elements at the head
    cout << "Insert 6 at head\n";
    insertAtHead(node, 6);
    print(node);
    cout << endl;

    cout << "Insert 798 at head\n";
    insertAtHead(node, 798);
    print(node);
    cout << endl;

    // Insert at a specific position
    cout << "Insert 99 at position 7\n";
    insertAtPos(node, 7, 99);
    print(node);
    cout << endl;

    // Insert in the middle
    cout << "Insert 100 at the middle\n";
    insertAtMiddle(node, 100);
    print(node);
    cout << endl;

    // // Delete a node at a specific position
    // cout << "Delete node at position 3\n";
    // deleteNodeAtPosition(node, 3);
    // print(node);
    // cout << endl;

    return EXIT_SUCCESS;
}
