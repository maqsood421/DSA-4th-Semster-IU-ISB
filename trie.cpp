#include <iostream>
using namespace std;

class TrieNode {
public:
    char data;
    bool isTerminal;
    TrieNode* children[26];

    TrieNode(char val) {
        this->data = val;
        this->isTerminal = false;

        for (int i = 0; i < 26; i++)
            this->children[i] = nullptr;
    }

    ~TrieNode() {
        for (int i = 0; i < 26; i++)
            delete this->children[i];
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode('\0');
    }

    // Insert word into the Trie
    void insertUtil(TrieNode* root, string word) {
        if (word.length() == 0) {
            root->isTerminal = true;
            return;
        }

        int index = word[0] - 'a';
        TrieNode* child;

        if (root->children[index] != NULL) {
            child = root->children[index];
        } else {
            child = new TrieNode(word[0]);
            root->children[index] = child;
        }

        insertUtil(child, word.substr(1));
    }

    void insertWord(string word) {
        insertUtil(root, word);
    }

    // Search for a word in the Trie
    bool searchUtil(TrieNode* root, string word) {
        if (word.length() == 0) {
            return root->isTerminal;
        }

        int index = word[0] - 'a';
        TrieNode* child;

        if (root->children[index] != NULL) {
            child = root->children[index];
        } else {
            return false;
        }

        return searchUtil(child, word.substr(1));
    }

    bool searchWord(string word) {
        return searchUtil(root, word);
    }

    // Delete a word from the Trie
    bool deleteUtil(TrieNode* root, string word) {
        if (word.length() == 0) {
            if (!root->isTerminal)
                return false; // Word does not exist
            root->isTerminal = false;
            return isEmpty(root); // Check if node can be deleted
        }

        int index = word[0] - 'a';
        TrieNode* child = root->children[index];

        if (child == NULL)
            return false; // Word does not exist

        bool shouldDeleteCurrentNode = deleteUtil(child, word.substr(1));

        if (shouldDeleteCurrentNode) {
            delete root->children[index];
            root->children[index] = NULL;

            return !root->isTerminal && isEmpty(root);
        }

        return false;
    }

    void deleteWord(string word) {
        deleteUtil(root, word);
    }

    // Helper function to check if a TrieNode is empty
    bool isEmpty(TrieNode* node) {
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != NULL)
                return false;
        }
        return true;
    }
};

int main() {
    Trie* t = new Trie();

    // Insert words
    t->insertWord("time");
    t->insertWord("timing");
    t->insertWord("tree");
    t->insertWord("trie");

    // Search for words
    cout << "Search Results:" << endl;
    cout << "Word 'time': " << (t->searchWord("time") ? "Found" : "Not Found") << endl;
    cout << "Word 'tree': " << (t->searchWord("tree") ? "Found" : "Not Found") << endl;
    cout << "Word 'trip': " << (t->searchWord("trip") ? "Found" : "Not Found") << endl;

    // Delete words
    cout << "\nDeleting 'time'..." << endl;
    t->deleteWord("time");

    cout << "\nAfter Deletion:" << endl;
    cout << "Word 'time': " << (t->searchWord("time") ? "Found" : "Not Found") << endl;
    cout << "Word 'timing': " << (t->searchWord("timing") ? "Found" : "Not Found") << endl;

    delete t; // Clean up dynamically allocated memory
    return 0;
}
