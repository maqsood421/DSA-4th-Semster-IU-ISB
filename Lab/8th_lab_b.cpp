#include <iostream>
#include <algorithm>
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
    }

    void pop() {
        if (top == nullptr) {
            return;
        }
        Node* temp = top;  
        top = top->next;   
        delete temp;       
    }

    char peek() {
        if (top == nullptr) {
            return ' ';
        }
        return top->data;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

int precedence(char op) {
    if (op == '+' || op == '-') return 1; 
    if (op == '*' || op == '/') return 2;          
    return -1;                            
}

void infixToPrefix(string expression, string &prefixExpression) {
    reverse(expression.begin(), expression.end());

    for (char &ch : expression) {
        if (ch == '(') {
            ch = ')';
        } else if (ch == ')') {
            ch = '(';
        }
    }

    Stack opstk; 
    int prefixCnt = 0;

    for (int i = 0; i < expression.length(); ++i) {
        char token = expression[i];

        if (isalpha(token)) { 
            prefixExpression[prefixCnt++] = token;
        } else if (token == '(') {
            opstk.push(token); 
        } else if (token == ')') {
            while (!opstk.isEmpty() && opstk.peek() != '(') {
                prefixExpression[prefixCnt++] = opstk.peek();
                opstk.pop();
            }
            opstk.pop(); 
        } else { 
            while (!opstk.isEmpty() && precedence(opstk.peek()) >= precedence(token)) {
                prefixExpression[prefixCnt++] = opstk.peek();
                opstk.pop();
            }
            opstk.push(token); 
        }
    }

    while (!opstk.isEmpty()) {
        prefixExpression[prefixCnt++] = opstk.peek();
        opstk.pop();
    }

    prefixExpression[prefixCnt] = '\0';

    reverse(prefixExpression.begin(), prefixExpression.end());
}

int main() {
    string expression = "A/B+C*D";
    string prefixExpression(expression.length() + 1, '\0'); 

    infixToPrefix(expression, prefixExpression);

    cout << "Infix Expression: " << expression << endl;
    cout << "Prefix Expression: " << prefixExpression << endl;

    return 0;
}
