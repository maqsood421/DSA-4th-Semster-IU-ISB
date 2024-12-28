#include <iostream>
using namespace std;

class CircularLinkedList {
public:
    int data;
    CircularLinkedList* next;

    CircularLinkedList(int data) {
        this->data = data;
        this->next = nullptr; 
    } 

    ~CircularLinkedList() {
        if(this->next != nullptr) {
            delete next;
            next = nullptr;
        }
    }
};

// Corrected print function to properly traverse the circular linked list
void print(CircularLinkedList* node) {
    if (node == nullptr) {
        cout << "List is empty" << endl;
        return;
    }
    
    CircularLinkedList* temp = node;
 
    do {
        cout << temp->data << ' ';
        temp = temp->next; 
    } while(temp != node); 
    cout << endl;
}

void insertNode(CircularLinkedList* &node, int element, int data) {
    // empty list
    if(node == nullptr) {
        CircularLinkedList* nodeToInsert = new CircularLinkedList(data);
        node = nodeToInsert;
        nodeToInsert->next = nodeToInsert; // Points to itself to make it circular
        return; 
    }

    // non-empty list
    CircularLinkedList* curr = node; 
    do {
        if (curr->data == element) {
            // element found, insert new node after it
            CircularLinkedList* temp = new CircularLinkedList(data);
            temp->next = curr->next;
            curr->next = temp;
            return;
        }
        curr = curr->next;
    } while(curr != node); // keep looping until we reach the starting node again
}

void deleteNode(CircularLinkedList* &node, int element) {
    if(node == nullptr) {
        cout << "List is empty!\n";
        return;
    }

    CircularLinkedList* curr = node;
    CircularLinkedList* prev = nullptr;

    do {
        if(curr->data == element) {
            if (prev == nullptr) {
                // Deleting the head node
                if (curr->next == node) {
                    // Only one node in the list
                    delete curr;
                    node = nullptr; // The list is now empty
                } else {
                    // More than one node
                    CircularLinkedList* last = node;
                    while(last->next != node) {
                        last = last->next;
                    }
                    last->next = curr->next; // Update last node's next
                    node = curr->next; // Move head to next node
                    delete curr;
                }
            } else {
                // Deleting a node other than the head
                prev->next = curr->next;
                delete curr;
            }
            return;
        }

        prev = curr;
        curr = curr->next;

    } while(curr != node);
}

int main(void) {
    CircularLinkedList* node = nullptr;

    // Insert first node (becomes circular)
    insertNode(node, 4, 100);  // Since the list is empty, it will insert the first node with data 100
    print(node);

    // Insert after node with data 100
    insertNode(node, 100, 200);
    print(node);

    // Insert another after node with data 200
    insertNode(node, 200, 300);
    print(node);

    // delete first element
    deleteNode(node, 100);
    print(node);

    return EXIT_SUCCESS;
}
