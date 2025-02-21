#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <iostream>
using namespace std;

// Stack Data Structure
template<typename T>
class Node {
    public:
        T* data;
        Node<T>* next;
    Node(T Value): data(value), next(NULL) {}
};

template<typename T>
class Stack {
    private: 
        Node<T>* top;
        int size;
    public:
        Stack(): top(NULL), size(0) {}
        // destructor to deallocate the dyanamic memory
        ~Stack() {
            while(!empty()) {
                pop();
            }
        }
        // push an element on to the stack
        void push(T value) {
            Node<T>* newNode = new Node(value);
            newNode->next = top;
            top = newNode;
            size++;
        }
        // pop an element from the stack
        T pop() {
            if(isEmpty()) {
                throw runtime_error("Stack underflow! Cannot pop from an empty stack.");
            }
            Node<T>* temp = top;
            T poppedValue = top->data;
            top = top->next;
            delete temp;
            size--;
            return poppedValue;
        }
        // peek the top element of the stack
        T peek() const {
            if(empty()) {
                throw runtime_error("Stack is empty! Cannot peek.");
            }
            return top->data;
        }
        // check if the stack is empty
        bool empty() const {
            return top == NULL;
        }
        // get the stack size
        bool size() const {
            return size;
        }
};


// Singly Linked List Node
template<typename T>
class SinglyNode {
public:
    T data;
    SinglyNode<T>* next;
    // Constructor
    SinglyNode(T value) : data(value), next(nullptr) {}
    // Destructor 
    ~SinglyNode() {
        while (next != nullptr) {
            SinglyNode<T>* temp = next;
            next = next->next;
            temp->next = nullptr; // Break the chain
            delete temp;
        }
    }
};


// Doubly Linked List Node
template<typename T>
class DoublyNode {
public:
    T data;
    DoublyNode<T>* next;
    DoublyNode<T>* prev;
    // Constructor
    DoublyNode(T value) : data(value), next(nullptr), prev(nullptr) {}
    // Destructor 
    ~DoublyNode() {
        while (next != nullptr) {
            DoublyNode<T>* temp = next;
            next = next->next;
            temp->next = nullptr; 
            temp->prev = nullptr; 
            delete temp;
        }
    }
};


// Circular Linked List Node
template<typename T>
class CircularNode {
public:
    T data;
    CircularNode<T>* next;
    // Constructor
    CircularNode(T value) : data(value), next(nullptr) {}
    // Destructor
    ~CircularNode() {
        if (next != nullptr) {
            CircularNode<T>* current = next;
            next = nullptr; // Break the circular link
            // Iteratively delete remaining nodes
            while (current != this) {
                CircularNode<T>* temp = current;
                current = current->next;
                temp->next = nullptr;
                delete temp;
            }
        }
    }
};


// Queue Data Structure
template<class T>
class qNode {
    public:
        T data;
        qNode* next;
        qNode(T val): data(val), next(NULL) {} // constructor
};

template <class T>
class Queue {
    private:
        qNode<T>* front;
        qNode<T>* rear;
    public:
        // constructor
        Queue() {
            front = NULL;
            rear = NULL;
        }
        // insert the element into the queue
        void enqueue(T val) {
            qNode<T>* temp = new qNode(val);
            if(!rear) {
                rear = temp;
                front = temp;
                return;
            }
            temp->next = rear;
            rear = temp;
        }
        // delete the first element of the queue if exists
        void dequeue() {
            if(!front) return;
            
            qNode<T>* temp = front;
            front = front->next;
            delete temp;
        }
        // returns the front element            
        T peek() {
            if(!front) {
                exit(0);
            }
            return front->data;
        }
        // checks if queue is empty or not
        bool isEmpty() {
            return front == NULL;
        }
};


#endif