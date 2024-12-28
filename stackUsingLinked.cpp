#include <iostream>
using namespace std;

// class representing a node in the linked list
template<class T>
class Node {
    public:
        T data;
        Node* next;
        Node(T data) {
            this->data = data;
            this->next = nullptr;
        }
};

// class representing stack uisng a singly linked list
template<class T>
class my_stack {
    private:
        // head of the linked list
        Node<T>* head;

    public:
        // constructor to initialize the stack
        my_stack() {
            this->head = nullptr;
        }

        // fucntion to check if the stack is empty
        bool isEmpty() {
            // if head is nullptr, the stack is empty
            return head == nullptr; 
        }

        // function to push an element onto the stack
        void push(T newData) {
            // create the new node to given data

            Node<T>* new_node = new Node<T>(newData);
            // check if the memory allocation for the new node
            // failed
            if(!new_node) {
                cout << "\nStack Overflow\n";
                return;
            }

            // link the new node to the current top node
            new_node->next = head;

            // update the top to the new node
            head = new_node;
        }

        // function to remove the top element from the stack
        void pop() {

            // check if the stack is empty
            if(this->isEmpty()) {
                cout << "\nStack is empty!\n";
                return;
            }

            // assign the current top to temporary
            Node<T>* temp = head;
            head = head->next;

            // deallocate the temp node
            delete temp;
        }

        // function to return the top element from teh stack
        T peek() {
            if(!this->isEmpty()) {
                return head->data;
            } 
            cout << "\nStack is empty!\n";
            exit(0);
        }

};


int main(void) {
    
    my_stack<int> s;
    s.push(3);
    cout << s.peek() << '\n';

    return EXIT_SUCCESS;
}



