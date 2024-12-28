#include <iostream>
#include <string>
using namespace std;

class Song {
public:
    string title;
    Song* next;
    Song* prev;

    Song(string songTitle) : title(songTitle), next(nullptr), prev(nullptr) {}
};

class Playlist {
public:
    Playlist() : head(nullptr), tail(nullptr), current(nullptr) {}

    // Add a song to the playlist
    void addSong(string songTitle) {
        Song* newSong = new Song(songTitle);
        if (head == nullptr) {
            head = tail = current = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        cout << "Song \"" << songTitle << "\" added to the playlist.\n";
    }

    // Remove a song from the playlist
    void removeSong(string songTitle) {
        if (head == nullptr) {
            cout << "Playlist is empty! Cannot remove any song.\n";
            return;
        }

        Song* temp = head;

        // Traverse the playlist to find the song
        while (temp != nullptr && temp->title != songTitle) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Song \"" << songTitle << "\n not found in the playlist.\n";
            return;
        }

        // Update links to remove the song
        if (temp == head) {
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        } else if (temp == tail) {
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        // Update the current pointer if necessary
        if (current == temp) {
            current = temp->next != nullptr ? temp->next : head; // Move to next or reset
        }

        delete temp;
        cout << "Song \"" << songTitle << "\" removed from the playlist.\n";

        if (head == nullptr) {
            tail = current = nullptr; // Reset pointers if the playlist is empty
        }
    }

    // Play the next song
    void playNext() {
        if (current == nullptr) {
            cout << "Playlist is empty! No song to play.\n";
            return;
        }
        current = current->next != nullptr ? current->next : head; // Loop to the start
        cout << "Now playing: \"" << current->title << "\"\n";
    }

    // Play the previous song
    void playPrevious() {
        if (current == nullptr) {
            cout << "Playlist is empty! No song to play.\n";
            return;
        }
        current = current->prev != nullptr ? current->prev : tail; // Loop to the end
        cout << "Now playing: \"" << current->title << "\"\n";
    }

    // Display the playlist
    void displayPlaylist() {
        if (head == nullptr) {
            cout << "Playlist is empty!\n";
            return;
        }

        cout << "Songs in the playlist:\n";
        Song* temp = head;
        while (temp != nullptr) {
            cout << temp->title << (temp == current ? " [CURRENT]" : "") << "\n";
            temp = temp->next;
        }
    }

    // Destructor to clean up dynamically allocated memory
    ~Playlist() {
        while (head != nullptr) {
            Song* temp = head;
            head = head->next;
            delete temp;
        }
        tail = current = nullptr;
    }

private:
    Song* head;
    Song* tail;
    Song* current;
};

int main() {
    Playlist playlist;
    int choice;
    string songTitle;

    do {
        cout << "\n==============| Music App |============\n";
        cout << "1 - Add a song to the playlist\n";
        cout << "2 - Remove a song from the playlist\n";
        cout << "3 - Play the next song\n";
        cout << "4 - Play the previous song\n";
        cout << "5 - Display the playlist\n";
        cout << "6 - Exit\n";
        cout << "=======================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To handle newline character after choice

        switch (choice) {
        case 1:
            cout << "Enter the song title: ";
            getline(cin, songTitle);
            playlist.addSong(songTitle);
            break;
        case 2:
            cout << "Enter the song title to remove: ";
            getline(cin, songTitle);
            playlist.removeSong(songTitle);
            break;
        case 3:
            playlist.playNext();
            break;
        case 4:
            playlist.playPrevious();
            break;
        case 5:
            playlist.displayPlaylist();
            break;
        case 6:
            cout << "Exiting the Music App.\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
