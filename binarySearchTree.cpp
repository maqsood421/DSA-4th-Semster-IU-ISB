#include <iostream>
using namespace std;

class Node {
    public:
        int data;
        Node* left;
        Node* right;

    // Constructor to initialize the node
    Node(int val) {
        this->data = val;
        this->left = nullptr;
        this->right = nullptr;
    }

    // Destructor to delete the subtree
    ~Node() {
        delete left;
        delete right;
    }
};

class BST {
    private:
        Node* root;

        // Helper function for insertion
        Node* insert(Node* node, int val) {
            if (node == nullptr) {
                return new Node(val);
            }
            if (val < node->data) {
                node->left = insert(node->left, val);
            } else if (val > node->data) {
                node->right = insert(node->right, val);
            }
            return node;
        }

        // Helper function for search
        bool search(Node* node, int val) {
            if (node == nullptr) {
                return false;
            }
            if (node->data == val) {
                return true;
            } else if (val < node->data) {
                return search(node->left, val);
            } else {
                return search(node->right, val);
            }
        }

        // Helper function for in-order traversal
        void inOrder(Node* node) {
            if (node == nullptr) {
                return;
            }
            inOrder(node->left);
            cout << node->data << " ";
            inOrder(node->right);
        }

        // Helper function to find the minimum node in the subtree
        Node* findMin(Node* node) {
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }

        // Helper function for deletion
        Node* remove(Node* node, int val) {
            if (node == nullptr) {
                return node;
            }

            if (val < node->data) {
                node->left = remove(node->left, val); // Traverse the left subtree
            } else if (val > node->data) {
                node->right = remove(node->right, val); // Traverse the right subtree
            } else {
                // Node with one or no child
                if (node->left == nullptr) {
                    Node* temp = node->right;
                    node->right = nullptr; // Disconnect the node to avoid deleting the subtree
                    delete node;
                    return temp;
                } else if (node->right == nullptr) {
                    Node* temp = node->left;
                    node->left = nullptr; // Disconnect the node to avoid deleting the subtree
                    delete node;
                    return temp;
                }

                // Node with two children
                Node* temp = findMin(node->right); // Find the in-order successor
                node->data = temp->data; // Replace with the in-order successor's data
                node->right = remove(node->right, temp->data); // Delete the successor
            }
            return node;
        }

    public:
        // Constructor to initialize the BST
        BST() {
            root = nullptr;
        }

        // Destructor to clean up the tree
        ~BST() {
            delete root;
        }

        // Public function to insert a value
        void insert(int val) {
            root = insert(root, val);
        }

        // Public function to search for a value
        bool search(int val) {
            return search(root, val);
        }

        // Public function to perform in-order traversal
        void inOrder() {
            inOrder(root);
            cout << endl;
        }

        // Public function to delete a value
        void remove(int val) {
            root = remove(root, val);
        }
};

int main(void) {
    BST tree;

    // Inserting nodes into the tree
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // In-order traversal
    cout << "In-order Traversal: ";
    tree.inOrder();

    // Searching for values in the tree
    int searchKey = 40;
    if (tree.search(searchKey)) {
        cout << "Found " << searchKey << " in the tree." << endl;
    } else {
        cout << searchKey << " is not in the tree." << endl;
    }

    // Deleting a node
    cout << "Deleting 50..." << endl;
    tree.remove(50);

    // In-order traversal after deletion
    cout << "In-order Traversal after Deletion: ";
    tree.inOrder();

    return EXIT_SUCCESS;
}
