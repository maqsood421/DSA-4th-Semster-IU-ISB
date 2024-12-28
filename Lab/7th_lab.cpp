#include <iostream>
using namespace std;

// Node structure for the stack
struct Node {
    int data;
    Node* next;
};

// Stack class
class Stack {
private:
    Node* top; // Pointer to the top of the stack

public:
    Stack() {
        top = nullptr; // Initialize the stack as empty
    }

    // Push operation to add an element to the stack
    void push(int value) {
        Node* newNode = new Node(); // Create a new node
        newNode->data = value;      // Set the value
        newNode->next = top;        // Link the new node to the current top
        top = newNode;              // Update the top to the new node
        cout << "Pushed: " << value << endl;
    }

    // Pop operation to remove an element from the stack
    void pop() {
        if (top == nullptr) {
            cout << "Stack is empty. Cannot pop.\n";
            return;
        }
        Node* temp = top;  // Store the current top
        top = top->next;   // Move the top pointer to the next node
        cout << "Popped: " << temp->data << endl;
        delete temp;       // Free the memory of the popped node
    }

    // Peek operation to see the top element of the stack
    int peek() {
        if (top == nullptr) {
            cout << "Stack is empty.\n";
            return -1;
        }
        return top->data;
    }

    // Check if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Display the stack elements
    void display() {
        if (top == nullptr) {
            cout << "Stack is empty.\n";
            return;
        }

        Node* temp = top;
        cout << "Stack elements (top to bottom): ";
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    Stack stack;
    int choice, value;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Peek\n";
        cout << "4. Check if Empty\n";
        cout << "5. Display Stack\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to push: ";
                cin >> value;
                stack.push(value);
                break;
            case 2:
                stack.pop();
                break;
            case 3:
                cout << "Top element: " << stack.peek() << endl;
                break;
            case 4:
                if (stack.isEmpty()) {
                    cout << "Stack is empty.\n";
                } else {
                    cout << "Stack is not empty.\n";
                }
                break;
            case 5:
                stack.display();
                break;
            case 6:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}
