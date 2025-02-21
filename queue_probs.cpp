#include <iostream>
using namespace std;

class Node {
    public:
        int data;
        Node* next;
        Node(int val) {
            this->data = val;
            this->next = NULL;
        }
};

class Queue {
    private:
        Node* front;
        Node* rear;
    public:
        Queue() : front(NULL), rear(NULL) {}

        void enqueue(int val) {
            Node* temp = new Node(val);
            
            if(!rear) {
                rear = temp;
                front = temp;
                return;
            }
            
            rear->next = temp;
            rear = temp;  // Update the rear pointer
        }

        void dequeue() {
            if(!front) {
                cout << "Queue is empty!\n";
                return;
            }

            Node* temp = front;
            front = front->next;
            delete temp;
            if (!front) rear = NULL;  // Handle case when queue becomes empty
        }

        int peek() {
            if(!front) {
                cout << "Queue is empty!\n";
                exit(0);
            }

            return front->data;
        }

        bool isEmpty() {
            return front == NULL;
        }

        void display() {
            Node* temp = front;
            while(temp) {
                cout << temp->data << ' ';
                temp = temp->next;
            }
            cout << '\n';
        }
};

void reverseQueue(Queue& q) {
    if(q.isEmpty()) return;

    int num = q.peek();
    q.dequeue();
    // Recursive call
    reverseQueue(q);
    // Enqueue after recursion to reverse order
    q.enqueue(num);
}




int main() {
    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Original Queue: ";
    q.display();
    
    reverseQueue(q);

    cout << "Reversed Queue: ";
    q.display();
    
    return EXIT_SUCCESS;
}
