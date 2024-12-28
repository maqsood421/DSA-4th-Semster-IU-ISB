#include <iostream>
using namespace std;

class Stack {
    int top;
    int *arr;
    int size;
    public:
        Stack(int newSize) {
            this->size = newSize;
            arr = new int[size];
            top = -1;
        }
        bool push(int x);
        int pop();
        int peek();
        bool isEmpty();
};

// function to push the element to top of the stack
bool Stack::push(int x) {
    if(top >= (size - 1)) {
        cout << "\nStack Overflow!\n";
        return false;
    }
    this->arr[++top] = x;
    return true;
}

// function to return the top element and removes it from  the stack
int Stack::pop() {
    if(this->top != -1) {
        return this->arr[top--];
    } 
    // if the stack is empty
    cout << "\nStack is Empty!\n";
    exit(0);
}

// function to return the top element of the stack
int Stack::peek() {
    if(this->top < 0) {
        cout << "\nStack is Empty!\n";
        exit(0);
    } 
    return this->arr[top];
}

// function to checks the stack is empty or not
bool Stack::isEmpty() {
    return top == -1;
}


// Driver program to test above functions 
int main() 
{ 
    class Stack s(10);  // size as parameter
    s.push(10); 
    s.push(20); 
    s.push(30); 
    cout << s.pop() << " Popped from stack\n"; 
    
    //print top element of stack after popping 
    cout << "Top element is : " << s.peek() << endl; 
    
    //print all elements in stack : 
    cout <<"Elements present in stack : "; 
    while(!s.isEmpty()) 
    { 
        // print top element in stack 
        cout << s.peek() <<" "; 
        // remove top element in stack 
        s.pop(); 
    } 

    return 0; 
}