#include <iostream>
using namespace std;


struct Node {
    char data;
    Node* next;
};

class Stack {
private:
    Node* top; 

public:
    Stack() {
        top = nullptr; 
    }

    void push(char value) {
        Node* newNode = new Node(); 
        newNode->data = value;      
        newNode->next = top;        
        top = newNode;              
        cout << "Pushed: " << value << endl;
    }

    void pop() {
        if (top == nullptr) {
            cout << "Stack is empty. Cannot pop.\n";
            return;
        }
        Node* temp = top;  
        top = top->next;   
        cout << "Popped: " << temp->data << endl;
        delete temp;       
    }

    char peek() {
        if (top == nullptr) {
            cout << "Stack is empty.\n";
            return ' ';
        }
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }

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

int precedence(char op) {
    if (op == '+' || op == '-') return 1; 
    if (op == '*' || op == '/') return 2;          
    return -1;                            
}

void infixToPostfix(string expression, string &postfixExpression) {
    Stack opstk; 
    int postfixCnt = 0;

    for (int i = 0; i < expression.length(); ++i) {
        char token = expression[i];

        if (isalpha(token)) { 
            postfixExpression[postfixCnt++] = token;
        } else if (token == '(') {
            opstk.push(token); 
        } else if (token == ')') {
            while (!opstk.isEmpty() && opstk.peek() != '(') {
                postfixExpression[postfixCnt++] = opstk.peek();
                opstk.pop();
            }
            opstk.pop(); 
        } else { 
            while (!opstk.isEmpty() && precedence(opstk.peek()) >= precedence(token)) {
                postfixExpression[postfixCnt++] = opstk.peek();
                opstk.pop();
            }
            opstk.push(token); 
        }
    }

    while (!opstk.isEmpty()) {
        postfixExpression[postfixCnt++] = opstk.peek();
        opstk.pop();
    }

    postfixExpression[postfixCnt] = '\0';
}

int main() {
    string expression = "A/B+C*D";
    string postfixExpression(expression.length() + 1, '\0'); 

    infixToPostfix(expression, postfixExpression);

    cout << "Infix Expression: " << expression << endl;
    cout << "Postfix Expression: " << postfixExpression << endl;

    return 0;
}
