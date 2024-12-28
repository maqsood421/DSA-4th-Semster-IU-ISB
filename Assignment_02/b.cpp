#include <iostream>
using namespace std;

// class for linked list
class Node {
    public:
        int score;
        Node* next;

        Node(int new_score) {
            this->score = new_score;
            this->next = nullptr;
        }
};

void removeDuplicatesScores(Node* &leaderboard_score_list) {
    // If the leaderboard list is empty or has one score, no need to remove duplicates
    if(leaderboard_score_list == nullptr || leaderboard_score_list->next == nullptr) return;

    Node* temp = leaderboard_score_list;
    while(temp != nullptr) {
        Node* curr = temp->next;
        Node* prev = temp;
        
        while(curr != nullptr) {
            if(curr->score == temp->score) {
                // Duplicate found, remove it
                prev->next = curr->next;
                delete curr;
                curr = prev->next; // move to the next node
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        temp = temp->next; // Move temp forward to check for the next unique score
    }

    cout << "Duplicate scores removed successfully!\n";
}

void addScore(Node* &leaderboard_score_list, int score) {
    Node* newScore = new Node(score);
    // if the scorelist is empty
    if(leaderboard_score_list == nullptr) {
        leaderboard_score_list = newScore;
        cout << "Score added: " << score << '\n';
        return;
    }

    Node* temp_ptr = leaderboard_score_list;
    while (temp_ptr->next != nullptr) {
        temp_ptr = temp_ptr->next;
    }

    temp_ptr->next = newScore;
    cout << "Score added: " << score << '\n';
}

void displayLeaderboardScores(Node* leaderboard) {
    cout << "\n";
    while(leaderboard != nullptr) {
        cout << leaderboard->score << " -> ";
        leaderboard = leaderboard->next;
    } cout << "NULL\n";
}

int main(void) {
    Node* leaderboard = nullptr;
    int choice;
    int score;
    
    do {
        cout << "\n=========| Leaderboard Scores |=========\n\n";
        cout << "1 - Add Score to leaderboard\n";
        cout << "2 - Remove duplicate scores\n";
        cout << "3 - Exit\n";
        cout << "\n========================================\n";
        cout << "Enter choice:  ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter score to add it in leaderboard\n>> ";
            cin >> score;
            addScore(leaderboard, score);
            cout << "\nAfter adding score the leaderboard List\n";
            displayLeaderboardScores(leaderboard);
            break;
        case 2: 
            removeDuplicatesScores(leaderboard);
            cout << "\nAfter removing duplicate scores in the leaderboard List\n";
            displayLeaderboardScores(leaderboard);
            break;
        case 3:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice!\n";
            break;
        }
    } while(choice != 3);

    delete leaderboard;

    return EXIT_SUCCESS;
}