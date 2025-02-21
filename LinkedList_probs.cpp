#include <iostream>
using namespace std;

// linked list
class Node {
public:
    int data;
    Node *next;
    // constructor
    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }
    // destructor
    ~Node() {
        if (next != nullptr) {
            delete next;
            next = nullptr;
        }
    }
};

void print(Node *node) {
    if (!node)
        return;
    cout << node->data << ' ';
    print(node->next);
}

void func(Node *&head, int value) {
    if (!head)
        return;

    Node *lessHead = nullptr;   // Head of the "less than value" list
    Node *lessTail = nullptr;  // Tail of the "less than value" list
    Node *greaterHead = nullptr;  // Head of the "greater or equal to value" list
    Node *greaterTail = nullptr; // Tail of the "greater or equal to value" list

    Node *curr = head;

    while (curr) {
        if (curr->data < value) {
            // Add to the "less than value" list
            if (!lessHead) {
                lessHead = curr;
                lessTail = curr;
            } else {
                lessTail->next = curr;
                lessTail = curr;
            }
        } else {
            // Add to the "greater or equal to value" list
            if (!greaterHead) {
                greaterHead = curr;
                greaterTail = curr;
            } else {
                greaterTail->next = curr;
                greaterTail = curr;
            }
        }
        curr = curr->next;
    }

    // Combine the two lists
    if (lessTail) {
        lessTail->next = greaterHead;
    } else {
        lessHead = greaterHead; // If no elements are less than the value
    }

    if (greaterTail) {
        greaterTail->next = nullptr; // Mark the end of the list
    }

    head = lessHead; // Update the head pointer
}

int main(void) {
    Node *node = new Node(10);
    node->next = new Node(200);
    node->next->next = new Node(30);
    node->next->next->next = new Node(40);

    func(node, 30);
    print(node);
    cout << '\n';

    // Free the memory
    delete node;

    return EXIT_SUCCESS;
}
