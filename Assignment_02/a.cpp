#include <iostream>
#include <string>
using namespace std;

// singly linked list
class Station {
    public:
        string name;
        Station* next;

        Station(string name) {
            this->name = name;
            next = nullptr;
        }
};

// doubly Linked List
class Compartment{
    public:
        string name;
        Compartment* prev;
        Compartment* next;

        Compartment(string name) {
            this->name = name;
            prev = nullptr;
            next = nullptr;
        }
};

// circular linked list
class Train {
    public:
        string name;
        Train* next;

        Train(string name) {
            this->name = name;
            next = nullptr;
        }
};

// Stationlist class. it stores the list of stations a train passes through
class StationList {
    public:
        // constructor 
        StationList(): head_station_list(nullptr) {}
        // function to add the station name in the station list
        void addStation(string station_name) {
            Station* newStation = new Station(station_name);

            // if the stationList is empty just assign the newStation to head_station_list
            if(head_station_list == nullptr) {
                head_station_list = newStation;
                cout << "Station added: " << newStation->name << '\n';
                return;
            }
            // if the stationList is not empty then we add the newStation name at the end of the list
            Station* temp_ptr = head_station_list;

            while(temp_ptr->next != nullptr) {
                temp_ptr = temp_ptr->next;
            }

            temp_ptr->next = newStation;
            cout << "Station added: " << newStation->name << '\n';
        }

        // removes the station in the station list
        void removeStation(string name) {
            // check if the station list is empty or not
            if(head_station_list == nullptr) {
                cout << "Station list is empty!\n";
                return;
            }   

            Station* curr = head_station_list;
            Station* prev = nullptr;
            while(curr != nullptr && curr->name != name) {
                prev = curr;
                curr = curr->next;
            }

            if(curr == nullptr) {
                cout << "Station not found!\n";
                return;
            }

            // removes the station from the list
            prev->next = curr->next;
            delete curr;
            cout << "Station removed Successfully!\n";
        }

        // displays the stations 
        void displayStations() {
            Station* temp_ptr = head_station_list;

            while(temp_ptr != nullptr) {
                cout << temp_ptr->name << " -> ";
                temp_ptr = temp_ptr->next;
            }
            cout << "NULL\n";
        }

    private:
        Station* head_station_list;

};

// Manages the train compartments
class CompartmentList {
    public:
    // constructor
    CompartmentList(): head_compartment_list(nullptr) {}

    // adds the compartment
    void addCompartment(string compartment_name) {
        // if the compartment list is empty
        Compartment* newCompartment = new Compartment(compartment_name);
        if(head_compartment_list == nullptr) {
            head_compartment_list = newCompartment;
            cout << "Compartment added: " << newCompartment->name << '\n';
            return;
        }

        Compartment* temp_ptr = head_compartment_list;

        while(temp_ptr->next != nullptr) {
            temp_ptr = temp_ptr->next;
        }

        temp_ptr->next = newCompartment; // added new compartment in the list
        newCompartment->prev = temp_ptr;
        cout << "Compartment added: " << newCompartment->name << '\n';

    }

    // removes the compartment
    void removeCompartment(string compartment_name) {
        // if the compartment list is empty
        if(head_compartment_list == nullptr) {
            cout << "Compartment added: " << compartment_name << '\n';
            cout << compartment_name << " is not in the Compartment list!\n";
            return;
        }


        // if compartment_name matches with first Compartment
        if(head_compartment_list->name == compartment_name) {
            Compartment* compartmentToDelete = head_compartment_list;
            head_compartment_list = head_compartment_list->next;
            if(head_compartment_list != nullptr) head_compartment_list->prev = nullptr;
            // delete the compartment
            delete compartmentToDelete;
            cout << "Compartment removed: " << compartment_name << '\n';
            return;
        }

        // if the compartment is somewhere in the middle or in the end
        Compartment* temp_ptr = head_compartment_list;

        while(temp_ptr != nullptr && temp_ptr->name != compartment_name) {
            temp_ptr = temp_ptr->next;
        }

        // temp_ptr is nullptr it means compartment is not in the compartment_list
        if(temp_ptr == nullptr) {
            cout << compartment_name << " is not in the Compartment list!\n";
            return;
        }

        // if compartment found in the compartment list
        if(temp_ptr->prev != nullptr)  
            temp_ptr->prev->next = temp_ptr->next;
        if(temp_ptr->next != nullptr) 
            temp_ptr->next->prev = temp_ptr->prev;
        // delete the compartment 
        delete temp_ptr;
        cout << "Compartment removed: " << compartment_name << '\n';

    }

    // displays the all compartments
    void displayCompartments() {
        Compartment* temp_ptr = head_compartment_list;

        while(temp_ptr != nullptr) {
            cout << temp_ptr->name << " -> ";
            temp_ptr = temp_ptr->next;
        }
        cout << "NULL\n";
    }

    private:
        Compartment* head_compartment_list;
};


// circular linked list for Train loops
class CircularRoute {
    private:
        Train* head_train_list;

    public:

        // adds the Train in the loop
        void addTrain(string train_name) {
            Train* newTrain = new Train(train_name);

            // if there's no train in the cirular loop
            if(head_train_list == nullptr) {
                head_train_list = newTrain;
                head_train_list->next = head_train_list;
                cout << "Train added in the loop: " << train_name << '\n';
                return;
            }

            // if there's already trains in the loop
            Train* temp_ptr = head_train_list;

            while(temp_ptr->next != head_train_list) {
                temp_ptr = temp_ptr->next;
            }

            temp_ptr->next = newTrain;
            newTrain->next = head_train_list;
            cout << "Train added in the loop: " << train_name << '\n';
        }

        // displays the all Trains
        void displayTrains() {
            if(head_train_list == nullptr) {
                cout << "No trains in the loop\n";
                return;
            }

            Train* temp_ptr = head_train_list;

            do {
                cout << temp_ptr->name << " -> ";
                temp_ptr = temp_ptr->next;
            } while (temp_ptr != head_train_list);
            cout << head_train_list->name << '\n';
        }
};


void displayMenu() {
    cout << "\n==========| Train Management System |==========\n";
    cout << "1. Add Station\n";
    cout << "2. Display Stations\n";
    cout << "3. Add Compartment\n";
    cout << "4. Display Compartments\n";
    cout << "5. Add Train\n";
    cout << "6. Display Trains\n";
    cout << "7. Exit\n";
    cout << "=================================================\n";
    cout << "Enter your choice: ";
}

int main() {
    StationList* stationList = new StationList();
    CompartmentList* compartmentList = new CompartmentList();
    CircularRoute* circularRoute = new CircularRoute();

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            string station;
            cout << "Enter station name: ";
            cin.ignore();
            getline(cin, station);
            stationList->addStation(station);
            break;
        }
        case 2:
            stationList->displayStations();
            break;
        case 3: {
            string compartment;
            cout << "Enter compartment name: ";
            cin.ignore();
            getline(cin, compartment);
            compartmentList->addCompartment(compartment);
            break;
        }
        case 4:
            compartmentList->displayCompartments();
            break;
        case 5: {
            string train;
            cout << "Enter train name: ";
            cin.ignore();
            getline(cin, train);
            circularRoute->addTrain(train);
            break;
        }
        case 6:
            circularRoute->displayTrains();
            break;
        case 7:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    delete stationList;
    delete compartmentList;
    delete circularRoute;

    return EXIT_SUCCESS;
}