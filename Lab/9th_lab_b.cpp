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
                cout << "Enqueued Successfully!\n";
                return;
            }
            
            rear->next = temp;
            rear = temp;  // Update the rear pointer
            cout << "Enqueued Successfully!\n";
        }

        void dequeue() {
            if(!front) {
                cout << "Queue is empty!\n";
                return;
            }

            Node* temp = front;
            front = front->next;
            delete temp;
            cout << "Dequeued successfully!\n";
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

        // For displaying the queue without modifying it
        void display() {
            Node* temp = front;
            while(temp) {
                cout << temp->data << ' ';
                temp = temp->next;
            }
            cout << '\n';
        }
};

int main(void) {

    Queue q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Queue elements: ";
    q.display(); // Display elements without dequeuing

    cout << "After displaying, is queue empty? " << (q.isEmpty() ? "Yes" : "No") << '\n';

    return EXIT_SUCCESS;
}
