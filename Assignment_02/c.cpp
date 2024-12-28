#include <iostream>
using namespace std;

class Process {
public:
    int pid;
    Process* next;
    Process(int new_pid) {
        this->pid = new_pid;
        this->next = nullptr;
    }
};

class RoundRobinScheduler {
public:
    RoundRobinScheduler() : head(nullptr), tail(nullptr), current(nullptr) {}

    // Add a process to the schedule
    void addProcess(int new_pid) {
        Process* newProcess = new Process(new_pid);
        if (head == nullptr) {
            head = tail = current = newProcess;
            newProcess->next = newProcess; // Circular link
        } else {
            newProcess->next = head;
            tail->next = newProcess;
            tail = newProcess;
        }
        cout << "Process " << new_pid << " added to the schedule.\n";
    }

    // Execute the current process
    void executeProcess() {
        if (current == nullptr) {
            cout << "No processes in the schedule!\n";
            return;
        }
        cout << "Executing process " << current->pid << ".\n";
        current = current->next; // Move to the next process
    }

    // Remove a process from the schedule
    void removeProcess(int pidToRemove) {
        if (head == nullptr) {
            cout << "No processes in the schedule!\n";
            return;
        }

        Process* temp = head;
        Process* prev = nullptr;

        // If there's only one process
        if (head == tail && head->pid == pidToRemove) {
            delete head;
            head = tail = current = nullptr;
            cout << "Process " << pidToRemove << " removed from the schedule.\n";
            return;
        }

        // Traverse the circular linked list to find the process
        do {
            if (temp->pid == pidToRemove) {
                if (temp == head) {
                    head = head->next; // Move head to the next process
                    tail->next = head; // Maintain circularity
                } else if (temp == tail) {
                    tail = prev; // Update tail
                    tail->next = head; // Maintain circularity
                } else {
                    prev->next = temp->next; // Bypass the current process
                }

                if (current == temp) {
                    current = temp->next; // Update current
                }

                delete temp;
                cout << "Process " << pidToRemove << " removed from the schedule.\n";
                return;
            }
            prev = temp;
            temp = temp->next;
        } while (temp != head);

        cout << "Process " << pidToRemove << " not found in the schedule.\n";
    }

    // Display the schedule
    void displaySchedule() {
        if (head == nullptr) {
            cout << "No processes in the schedule!\n";
            return;
        }

        Process* temp = head;
        cout << "Processes in the schedule:\n";
        do {
            cout << temp->pid << " -> ";
            temp = temp->next;
        } while (temp != head);
        cout << "HEAD\n";
    }

    ~RoundRobinScheduler() {
        if (head == nullptr) return;

        Process* temp = head;
        do {
            Process* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        } while (temp != head);

        head = tail = current = nullptr;
    }

private:
    Process* head;    // Head of the circular linked list
    Process* tail;    // Tail of the circular linked list
    Process* current; // Current scheduled process
};

int main() {
    RoundRobinScheduler scheduler;
    int choice, pid;

    do {
        cout << "\n==============| Round-Robin Scheduler |============\n";
        cout << "1 - Add a process\n";
        cout << "2 - Execute a process\n";
        cout << "3 - Remove a process\n";
        cout << "4 - Display the schedule\n";
        cout << "5 - Exit\n";
        cout << "===================================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter process ID to add: ";
            cin >> pid;
            scheduler.addProcess(pid);
            break;
        case 2:
            scheduler.executeProcess();
            break;
        case 3:
            cout << "Enter process ID to remove: ";
            cin >> pid;
            scheduler.removeProcess(pid);
            break;
        case 4:
            scheduler.displaySchedule();
            break;
        case 5:
            cout << "Exiting the scheduler.\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
