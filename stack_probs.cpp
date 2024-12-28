#include <iostream>
#include <stack>
using namespace std;

void deleteMiddleElement(stack<int>& stk, int cnt, int size) {

    if(stk.empty()) return;
    
    if(cnt == size/2) {
        stk.pop();
        return;
    }

    int num = stk.top();
    stk.pop();

    // recursive call
    deleteMiddleElement(stk, cnt + 1, size);

    stk.push(num);
}

bool isValidParenthesis(string expression) {
    stack<char> st;

    for(int i = 0; i < expression.length(); ++i) {
        char ch = expression[i];

        if(ch == '(' || ch == '{' || ch == '[') {
            st.push(ch);
        }  
        else {
            if(!st.empty()) {
                char top = st.top();
                if((ch == ')' && top == '(') || (ch == '}' && top == '{') || (ch == ']' && top == '[')) {
                    st.pop();
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
    }

    if(st.empty()) return true;
    else return false;
}


void insertAtBottom(stack<int> &st, int bottom) {
    if(st.empty()) {
        st.push(bottom);
        return;
    }

    int top = st.top();
    st.pop();
    insertAtBottom(st, bottom);

    st.push(top);
}


void reverseStack(stack<int> &st) {
    if(st.empty()) {
        return;
    }
    int top = st.top();
    st.pop();
    reverseStack(st);

    insertAtBottom(st, top);
}


void sortedInsert(stack<int>& st, int num) {
    if(st.empty() || st.top() < num) {
        st.push(num);
        return;
    }

    int top = st.top();
    st.pop();
    // recursive call
    sortedInsert(st, num);

    st.push(top);
}


void sortStack(stack<int>& st) {
    if(st.empty()) return;

    int top = st.top();
    st.pop();
    // recursive call
    sortStack(st);

    sortedInsert(st, top);
}




void display(stack<int> &st) {
    if(st.empty()) return;

    cout << st.top() << '\n';

    int num = st.top();
    st.pop();
    // recursive call
    display(st);

    st.push(num);
}

int main(void) {
    
    stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);
    display(st);
    deleteMiddleElement(st, 0, st.size());
    cout << "\nAfter deleting middle element\n";
    display(st);

    cout << "Stack start\n";
    insertAtBottom(st, 100);
    display(st);
    cout << "Stack end\n";

    cout << "Stack start\n";
    reverseStack(st);
    display(st);
    cout << "Stack end\n";

    cout << "Stack start\n";
    sortStack(st);
    display(st);
    cout << "Stack end\n";

    cout << (isValidParenthesis("({([])})") ? "Valid\n" : "Not Valid!\n");

    return EXIT_SUCCESS;
} 