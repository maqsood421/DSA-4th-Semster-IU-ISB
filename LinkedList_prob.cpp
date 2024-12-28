#include <iostream>
using namespace std;

// linked list
template<class T>
class Node {
    public:
        T data;
        Node* next;
        // constructor
        Node(T data) {
            this->data = data;
            this->next = nullptr; 
        }
        // destructor
        ~Node() {
            if(next->next != nullptr) {
                delete next;
                next = nullptr;
            }
        }
};

void print(Node<int>* node) {
    if(!node) return;

    cout << node->data << ' ';
    print(node->next);
}

void reverseLinkedListIterative(Node<int>* &node) {
    if(!node || !node->next) return;

    Node<int>* curr =  node;
    Node<int>* prev = nullptr;
    Node<int>* next = nullptr;

    while(curr != nullptr) {
        // save the next node
        next = curr->next; 
        // reverse the link
        curr->next = prev;
        // move pointer forward
        prev = curr;
        curr = next;
    }

    // update the head
    node = prev;
}

void reverseLinkedListRecursive(Node<int>* &node) {
    // base case
    if(!node || !node->next) return;

    // store the head of the linked List
    Node<int>* newNode = node->next;
    
    // recursive call
    reverseLinkedListRecursive(newNode);

    // processing
    node->next->next = node;
    node->next = nullptr;

    node = newNode;
}


int main(void) {
    
    Node<int>* node = new Node(10);
    node->next = new Node(20);
    node->next->next = new Node(30);
    node->next->next->next = new Node(40);

    print(node); cout << '\n';

    // reverseLinkedListIterative(node);
    reverseLinkedListRecursive(node);
    print(node); cout << '\n';
    
    return EXIT_SUCCESS;
}