#include <iostream>
using namespace std;

// Abstract Base Class (Abstraction)
class User {
protected:
    int userID;
    string name;
public:
    User(int id, string n) : userID(id), name(n) {}
    virtual void displayMenu() = 0; // pure virtual function
    int getUserID() { return userID; }
    string getName() { return name; }
};

// Event class
class Event {
private:
    string eventName;
public:
    Event() {}
    Event(string name) { eventName = name; }
    void setEventName(string name) { eventName = name; }
    string getEventName() { return eventName; }
};

// Application class for participation
class Application {
private:
    string eventName;
    string status;
public:
    Application() {}
    Application(string e) {
        eventName = e;
        status = "Pending";
    }
    void approve() { status = "Approved"; }
    void reject() { status = "Rejected"; }
    string getEvent() { return eventName; }
    string getStatus() { return status; }
};

// Community Member class (Inheritance)
class CommunityMember : public User {
private:
    Application applications[10];
    int appCount;
public:
    CommunityMember() : User(0, "Unknown") {
        appCount = 0;
    }

    CommunityMember(int id, string n) : User(id, n) {
        appCount = 0;
    }

    void viewEvents(Event eventList[], int eventCount) {
        cout << "\nAvailable Events:\n";
        for (int i = 0; i < eventCount; i++) {
            cout << i + 1 << ". " << eventList[i].getEventName() << endl;
        }
    }

    void applyEvent(Event eventList[], int eventCount) {
        viewEvents(eventList, eventCount);
        int choice;
        cout << "Enter the number of the event to apply: ";
        cin >> choice;
        if (choice >= 1 && choice <= eventCount) {
            applications[appCount] = Application(eventList[choice - 1].getEventName());
            appCount++;
            cout << "Applied successfully for " << eventList[choice - 1].getEventName() << "\n";
        } else {
            cout << "Invalid choice\n";
        }
    }

    void checkStatus() {
        cout << "\nApplication Status:\n";
        for (int i = 0; i < appCount; i++) {
            cout << i + 1 << ". Event: " << applications[i].getEvent() << " | Status: " << applications[i].getStatus() << endl;
        }
    }

    Application* getApplications() { return applications; }
    int getAppCount() { return appCount; }

    void displayMenu() {
        cout << "\n1. View Events\n2. Apply for Event\n3. Check Application Status\n4. Logout\n";
    }
};

// Administrator class (Inheritance)
class Administrator : public User {
public:
    Administrator(int id, string n) : User(id, n) {}

    void addEvent(Event eventList[], int &eventCount) {
        string name;
        cout << "Enter new event name: ";
        cin.ignore();
        getline(cin, name);
        eventList[eventCount].setEventName(name);
        eventCount++;
        cout << "Event added successfully.\n";
    }

    void viewApplications(CommunityMember members[], int memberCount) {
        for (int i = 0; i < memberCount; i++) {
            Application* apps = members[i].getApplications();
            int appCount = members[i].getAppCount();
            for (int j = 0; j < appCount; j++) {
                cout << "Member: " << members[i].getName() << ", Event: " << apps[j].getEvent() << ", Status: " << apps[j].getStatus() << endl;
            }
        }
    }

    void updateStatus(CommunityMember members[], int memberCount) {
        int id;
        string eventName;
        string decision;
        cout << "Enter Member ID: ";
        cin >> id;
        cout << "Enter Event Name: ";
        cin.ignore();
        getline(cin, eventName);
        cout << "Enter decision (approve/reject): ";
        cin >> decision;

        for (int i = 0; i < memberCount; i++) {
            if (members[i].getUserID() == id) {
                Application* apps = members[i].getApplications();
                int appCount = members[i].getAppCount();
                for (int j = 0; j < appCount; j++) {
                    if (apps[j].getEvent() == eventName) {
                        if (decision == "approve")
                            apps[j].approve();
                        else
                            apps[j].reject();
                        cout << "Status updated.\n";
                        return;
                    }
                }
            }
        }
        cout << "Application not found.\n";
    }

    void displayMenu() {
        cout << "\n1. Add Event\n2. View Applications\n3. Approve/Reject Applications\n4. Logout\n";
    }
};

int main() {
    Event eventList[20];
    int eventCount = 0;

    CommunityMember members[10];
    int memberCount = 0;

    Administrator admin(1, "Admin");

    while (true) {
        int userType;
        cout << "\nLogin As:\n1. Community Member\n2. Administrator\n3. Exit\nChoose option: ";
        cin >> userType;

        if (userType == 1) {
            int id;
            string name;
            cout << "Enter your ID: ";
            cin >> id;
            cout << "Enter your Name: ";
            cin.ignore();
            getline(cin, name);

            int index = -1;
            for (int i = 0; i < memberCount; i++) {
                if (members[i].getUserID() == id) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                members[memberCount] = CommunityMember(id, name);
                index = memberCount;
                memberCount++;
            }

            while (true) {
                members[index].displayMenu();
                int opt;
                cout << "Choose option: ";
                cin >> opt;
                if (opt == 1)
                    members[index].viewEvents(eventList, eventCount);
                else if (opt == 2)
                    members[index].applyEvent(eventList, eventCount);
                else if (opt == 3)
                    members[index].checkStatus();
                else if (opt == 4)
                    break;
                else
                    cout << "Invalid option.\n";
            }
        }
        else if (userType == 2) {
            while (true) {
                admin.displayMenu();
                int opt;
                cout << "Choose option: ";
                cin >> opt;
                if (opt == 1)
                    admin.addEvent(eventList, eventCount);
                else if (opt == 2)
                    admin.viewApplications(members, memberCount);
                else if (opt == 3)
                    admin.updateStatus(members, memberCount);
                else if (opt == 4)
                    break;
                else
                    cout << "Invalid option.\n";
            }
        }
        else if (userType == 3) {
            break;
        }
        else {
            cout << "Invalid login type.\n";
        }
    }

    return 0;
}
