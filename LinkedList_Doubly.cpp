#include <iostream>
using namespace std;

class DoublyLinkedList {
public:
    int val;
    DoublyLinkedList* prev;
    DoublyLinkedList* next;
    
    DoublyLinkedList(int val) {
        this->val = val;
        this->prev = nullptr;
        this->next = nullptr;
    }

    ~DoublyLinkedList() {
        if(next != nullptr) {  
            delete next;
            next = nullptr;
        }
    }
};

void print(DoublyLinkedList* node) {
    if (node == nullptr) return; // base case

    // processing
    cout << node->val << ' ';

    // recursive call
    print(node->next);
}

void insertAtHead(DoublyLinkedList* &node, int data) {
    DoublyLinkedList* temp = new DoublyLinkedList(data);
    temp->next = node;
    if (node != nullptr) {
        node->prev = temp;
    }
    node = temp;
}

void insertAtTail(DoublyLinkedList* &node, int data) {
    if (node == nullptr) {
        node = new DoublyLinkedList(data);
        return;
    }

    DoublyLinkedList* curr = node;

    while (curr->next != nullptr) {
        curr = curr->next;
    }

    DoublyLinkedList* temp = new DoublyLinkedList(data);
    curr->next = temp;
    temp->prev = curr;
}

void insertAtPosition(DoublyLinkedList* &node, int pos, int data) {
    if (pos == 1) {
        insertAtHead(node, data);
        return;
    }

    DoublyLinkedList* curr = node;
    int cnt = 1;

    // Traverse to the node just before the desired position
    while (cnt++ < pos - 1 && curr != nullptr) {
        curr = curr->next;
    }
    if (curr == nullptr) {
        // If position is beyond the end of the list, insert at the tail
        insertAtTail(node, data);
        return;
    }

    DoublyLinkedList* nodeToInsert = new DoublyLinkedList(data);
    
    // If inserting at a position not at the end of the list
    if (curr->next != nullptr) {
        nodeToInsert->next = curr->next;
        curr->next->prev = nodeToInsert;
    }
    curr->next = nodeToInsert;
    nodeToInsert->prev = curr;
}

void deleteAtPosition(DoublyLinkedList* &node, int pos) {
    if (node == nullptr) return;

    // Deleting the first node
    if (pos == 1) {
        DoublyLinkedList* temp = node;
        node = node->next;

        // if there's a next node
        if (node != nullptr) {
            node->prev = nullptr;
        }
        delete temp;
        return;
    }

    DoublyLinkedList* curr = node;
    DoublyLinkedList* prev = nullptr;
    int cnt = 1;

    // Traverse to the node at the given position
    while (cnt++ < pos) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr) {
        // Position is out of bounds
        return;
    }

    curr->prev = nullptr;
    prev->next = curr->next;
    curr->next = nullptr;

    delete curr;
}

int main(void) {
    DoublyLinkedList* node = new DoublyLinkedList(1);
    insertAtHead(node, 2);
    insertAtTail(node, 3);
    insertAtTail(node, 4);
    insertAtHead(node, 10);

    // Insert at position 6
    insertAtPosition(node, 6, 100);

    // Delete at position 2
    deleteAtPosition(node, 4);

    // Print the list
    print(node);

    return EXIT_SUCCESS;
}
