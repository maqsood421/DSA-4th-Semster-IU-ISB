#include <iostream>
#include <queue>
using namespace std;

class Node {
    public:
        int data;
        Node* left;
        Node* right;

    Node(int val) {
        this->data = val;
        this->left = nullptr;
        this->right = nullptr;
    }
    ~Node() {
        delete left;
        delete right;
    }
};


void buildTree(Node* &root) {
    int val;
    cout << "Enter data (-1 for no node): ";
    cin >> val;

    if (val == -1) return;

    root = new Node(val);
    cout << "Enter left child of " << val << endl;
    buildTree(root->left);
    cout << "Enter rightpostorder child of " << val << endl;
    buildTree(root->right);
}


void bredthFirstTraversal(Node* root) {
    if(!root) return;

    queue<Node*> queue;
    queue.push(root);

    while(!queue.empty()) {
        Node* current = queue.front();
        queue.pop();

        // Process the current node;
        cout << current->data << ' ';

        // Ensure left and right children
        if(current->left) 
            queue.push(current->left);

        if(current->right) 
            queue.push(current->right);
    }

}


void inorder(Node* &root) {
    if(!root) return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* &root) {
    if(!root) return;

    cout << root->data << ' ';
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* &root) {
    if(!root) return;

    postorder(root->left);
    postorder(root->right);
    cout << root->data << ' ';
}

int main(void) {
    
    Node* root = nullptr;
    buildTree(root);


    cout << "\nInorder Traversal: ";
    inorder(root);

    cout << "\nPreorder Traversal: ";
    preorder(root);
    
    cout << "\nPostorder Traversal: ";
    postorder(root);

    
    cout << "\nBreadth First Traversal: ";
    bredthFirstTraversal(root);


    return EXIT_SUCCESS;
}