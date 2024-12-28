#include <iostream>
using namespace std;

// Node structure for doubly linked list
struct Node {
    int data;
    Node* next;
    Node* prev;
};

// Function prototypes
void insertAtHead(Node*& head, int value);
void insertAtTail(Node*& head, int value);
void deleteNode(Node*& head, int value);
int search(Node* head, int value);
void display(Node* head);
void update(Node* head, int oldValue, int newValue);


int main() {
    Node* head = nullptr; // Initialize the list as empty
    int choice, value, oldValue, newValue;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. InsertAtHead\n";
        cout << "2. InsertAtTail\n";
        cout << "3. Delete\n";
        cout << "4. Search\n";
        cout << "5. Display\n";
        cout << "6. Update\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                insertAtHead(head, value);
                cout << "Value inserted.\n";
                break;
            case 2:
                cout << "Enter value to insert: ";
                cin >> value;
                insertAtTail(head, value);
                cout << "Value inserted.\n";
                break;
            case 3:
                cout << "Enter value to delete: ";
                cin >> value;
                deleteNode(head, value);
                break;
            case 4: {
                cout << "Enter value to search: ";
                cin >> value;
                int position = search(head, value);
                if (position != -1) {
                    cout << "Value found at position: " << position << endl;
                } else {
                    cout << "Value not found in the list.\n";
                }
                break;
            }
            case 5:
                display(head);
                break;
            case 6:
                cout << "Enter value to update: ";
                cin >> oldValue;
                cout << "Enter new value: ";
                cin >> newValue;
                update(head, oldValue, newValue);
                break;
            case 7:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

// Insert a new node at the beginning of the doubly linked list
void insertAtHead(Node*& head, int value) {
    Node* newNode = new Node(); // Create a new node
    newNode->data = value;      // Set data for the new node
    newNode->next = head;       // Point new node's next to current head
    newNode->prev = nullptr;    // Set new node's prev to nullptr

    if (head != nullptr) {
        head->prev = newNode; // Update head's prev to the new node
    }
    head = newNode; // Update head to the new node
}

// Insert a new node at the end of teh doubly linked list
void insertAtTail(Node*& head, int value) {

    Node* newNode = new Node();
    newNode->data = value;

    if(head == nullptr) {
        newNode->prev = nullptr;
        head = newNode;
        return;
    }

    Node* temp = head;
    while(temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

// Delete a node with the given value from the doubly linked list
void deleteNode(Node*& head, int value) {
    Node* temp = head;

    // Search for the node with the given value
    while (temp != nullptr && temp->data != value) {
        temp = temp->next;
    }

    // If value is not found
    if (temp == nullptr) {
        cout << "Value not found in the list.\n";
        return;
    }

    // If the node to be deleted is the head
    if (temp == head) {
        head = temp->next; // Update head to the next node
        if (head != nullptr) {
            head->prev = nullptr; // Update the new head's prev to nullptr
        }
        delete temp;
        cout << "Value deleted.\n";
        return;
    }

    // If the node to be deleted is in the middle or end
    if (temp->next != nullptr) {
        temp->next->prev = temp->prev; // Update the next node's prev
    }
    if (temp->prev != nullptr) {
        temp->prev->next = temp->next; // Update the previous node's next
    }

    delete temp; // Free the memory of the node
    cout << "Value deleted.\n";
}

// Search for a value in the doubly linked list
int search(Node* head, int value) {
    Node* temp = head;
    int position = 0;

    while (temp != nullptr) {
        if (temp->data == value) {
            return position; // Return the position if value is found
        }
        temp = temp->next;
        position++;
    }
    return -1; // Value not found
}

// Display the doubly linked list
void display(Node* head) {
    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }

    Node* temp = head;
    cout << "List elements (Forward): ";
    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}

// Update a value in the doubly linked list
void update(Node* head, int oldValue, int newValue) {
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == oldValue) {
            temp->data = newValue; // Update the data if oldValue is found
            cout << "Value updated successfully!\n";
            return; // Exit after updating
        }
        temp = temp->next; // Move to the next node
    }
    cout << "Value not found in the list.\n";
}
