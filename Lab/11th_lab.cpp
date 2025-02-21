#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    // book attributes
    int book_id;
    string title;
    string author;
    string genre;

    Node* left;
    Node* right;

    Node(int book_id, string title, string author, string genre) {
        this->book_id = book_id;
        this->title = title;
        this->author = author;
        this->genre = genre;
        this->left = nullptr;
        this->right = nullptr;
    }

    ~Node() {
        delete left;
        delete right;
    }
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int book_id, string title, string author, string genre) {
        if (node == nullptr) {
            return new Node(book_id, title, author, genre);
        }
        if (book_id < node->book_id) {
            node->left = insert(node->left, book_id, title, author, genre);
        } else if (book_id > node->book_id) {
            node->right = insert(node->right, book_id, title, author, genre);
        }        return node;
    }

    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* deleteNode(Node* node, int book_id) {
        if (node == nullptr) return node;

        if (book_id < node->book_id) {
            node->left = deleteNode(node->left, book_id);
        } else if (book_id > node->book_id) {
            node->right = deleteNode(node->right, book_id);
        } else {
            // Node to be deleted found
            if (node->left == nullptr) {
                Node* temp = node->right;
                node->right = nullptr;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                node->left = nullptr;
                delete node;
                return temp;
            }
            // Node with two children
            Node* temp = findMin(node->right);
            node->book_id = temp->book_id;
            node->title = temp->title;
            node->author = temp->author;
            node->genre = temp->genre;
            node->right = deleteNode(node->right, temp->book_id);
        }
        return node;
    }

    Node* search(Node* node, int book_id) {
        if (node == nullptr || node->book_id == book_id) {
            return node;
        }
        if (book_id < node->book_id) {
            return search(node->left, book_id);
        }
        return search(node->right, book_id);
    }

    void display(Node* node) {
        if (node != nullptr) {
            display(node->left);
            cout << "Book ID: " << node->book_id
                 << ", Title: " << node->title
                 << ", Author: " << node->author
                 << ", Genre: " << node->genre << endl;
            display(node->right);
        }
    }

public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        delete root;
    }

    void insert(int book_id, string title, string author, string genre) {
        root = insert(root, book_id, title, author, genre);
    }

    void deleteNode(int book_id) {
        root = deleteNode(root, book_id);
    }

    void search(int book_id) {
        Node* result = search(root, book_id);
        if (result != nullptr) {
            cout << "Book found!\n"
                 << "Book ID: " << result->book_id
                 << ", Title: " << result->title
                 << ", Author: " << result->author
                 << ", Genre: " << result->genre << endl;
        } else {
            cout << "Book with ID " << book_id << " not found." << endl;
        }
    }

    void display() {
        if (root == nullptr) {
            cout << "The library is empty." << endl;
        } else {
            display(root);
        }
    }
};

int main() {
    BST library;

    library.insert(101, "The Great Gatsby", "F. Scott Fitzgerald", "Fiction");
    library.insert(102, "1984", "George Orwell", "Dystopian");
    library.insert(103, "To Kill a Mockingbird", "Harper Lee", "Fiction");
    library.insert(104, "How to hide your self", "Maqsood", "Scifi");

    cout << "\nLibrary contents:" << endl;
    library.display();

    cout << "\nSearching for book with ID 102:" << endl;
    library.search(102);

    cout << "\nDeleting book with ID 102." << endl;
    library.deleteNode(102);

    cout << "\nLibrary contents after deletion:" << endl;
    library.display();

    return EXIT_SUCCESS;
}
