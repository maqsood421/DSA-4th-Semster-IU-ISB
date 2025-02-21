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
    cout << "Enter right child of " << val << endl;
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


// problems goes from here
int height(Node* &root) {
    if(!root) return 0;

    return max(height(root->left), height(root->right)) + 1;
}

// longest path b/w any 2 nodes
int diameter(Node* &root) {
    // base case
    if(!root) return 0;

    return max(max(diameter(root->left), diameter(root->right)), height(root->left) + height(root->right))  + 1;
}


// zig zag traversal 
void zigzagTraversal(Node* root) {
    if (!root)
        return;

    queue<Node*> q;
    q.push(root);

    bool leftToRight = true; // Flag to toggle between directions

    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> level(levelSize);

        // Process all nodes in the current level
        for (int i = 0; i < levelSize; ++i) {
            Node* current = q.front();
            q.pop();

            // Find the position to insert the current node's value
            int index = leftToRight ? i : (levelSize - 1 - i);
            level[index] = current->data;

            // Add child nodes to the queue for the next level
            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
        }

        // Print the current level
        for (int val : level) {
            cout << val << " ";
        }
        cout << endl;

        // Toggle the direction
        leftToRight = !leftToRight;
    }
}


// boundary traversal
void boundaryTraversal(Node* root) {
    if(!root) return;

    
}


int main(void) {

    Node* root;
    buildTree(root);

    // cout << "Height of the binary Tree is: " << height(root) << '\n';
    cout << "The longest path of two ending nodes is: " << diameter(root) << '\n';

    // delete allocation memory
    delete root;

    return EXIT_SUCCESS;
}