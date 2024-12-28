#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// Node structure for circular singly linked list
struct Node {
    int data;
    Node* next;
};

// Function prototypes
void insertMultiple(Node*& head, const vector<int>& values);
void deleteNode(Node*& head, int value);
int search(Node* head, int value);
void display(Node* head);
void update(Node* head, int oldValue, int newValue);

int main() {
    Node* head = nullptr; // Initialize the list as empty
    int choice, value, oldValue, newValue;
    string input;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert Multiple Values\n";
        cout << "2. Delete a Value\n";
        cout << "3. Search a Value\n";
        cout << "4. Display List\n";
        cout << "5. Update a Value\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline left in the input buffer

        switch (choice) {
            case 1: {
                cout << "Enter space-separated values to insert: ";
                getline(cin, input); // Get the entire line of values
                stringstream ss(input);
                vector<int> values;
                while (ss >> value) {
                    values.push_back(value);
                }
                insertMultiple(head, values);
                cout << "Values inserted.\n";
                break;
            }
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                deleteNode(head, value);
                break;
            case 3: {
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
            case 4:
                display(head);
                break;
            case 5:
                cout << "Enter value to update: ";
                cin >> oldValue;
                cout << "Enter new value: ";
                cin >> newValue;
                update(head, oldValue, newValue);
                break;
            case 6:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}

// Insert multiple values into the circular singly linked list
void insertMultiple(Node*& head, const vector<int>& values) {
    for (int value : values) {
        Node* newNode = new Node();
        newNode->data = value;

        if (head == nullptr) {
            head = newNode;
            newNode->next = head; // Point to itself to make it circular
        } else {
            Node* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }
}

// Delete a node with the given value from the circular singly linked list
void deleteNode(Node*& head, int value) {
    if (head == nullptr) {
        cout << "List is empty. Nothing to delete.\n";
        return;
    }

    Node* temp = head;
    Node* prev = nullptr;

    // Special case: Deleting the head node
    if (head->data == value) {
        if (head->next == head) {
            delete head;
            head = nullptr;
            cout << "Value deleted.\n";
            return;
        } else {
            while (temp->next != head) {
                temp = temp->next;
            }
            Node* toDelete = head;
            temp->next = head->next;
            head = head->next;
            delete toDelete;
            cout << "Value deleted.\n";
            return;
        }
    }

    // Search for the node to delete
    do {
        prev = temp;
        temp = temp->next;
        if (temp->data == value) {
            prev->next = temp->next;
            delete temp;
            cout << "Value deleted.\n";
            return;
        }
    } while (temp != head);

    cout << "Value not found in the list.\n";
}

// Search for a value in the circular singly linked list
int search(Node* head, int value) {
    if (head == nullptr) {
        return -1; // List is empty
    }

    Node* temp = head;
    int position = 0;

    do {
        if (temp->data == value) {
            return position;
        }
        temp = temp->next;
        position++;
    } while (temp != head);

    return -1; // Value not found
}

// Display the circular singly linked list
void display(Node* head) {
    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }

    Node* temp = head;
    cout << "List elements: ";
    do {
        cout << temp->data << " -> ";
        temp = temp->next;
    } while (temp != head);
    cout << "(back to head)\n";
}

// Update a value in the circular singly linked list
void update(Node* head, int oldValue, int newValue) {
    if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }

    Node* temp = head;

    do {
        if (temp->data == oldValue) {
            temp->data = newValue;
            cout << "Value updated successfully!\n";
            return;
        }
        temp = temp->next;
    } while (temp != head);

    cout << "Value not found in the list.\n";
}
