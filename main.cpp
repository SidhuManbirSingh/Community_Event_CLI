#include <iostream>
#include <string>
using namespace std;

// Abstract Base Class (Abstraction)
class User {
protected:
    int userID;
    string name;
    string password;
public:
    User(int id, string n, string pwd) : userID(id), name(n), password(pwd) {}
    virtual void displayMenu() = 0; // pure virtual function
    int getUserID() { return userID; }
    string getName() { return name; }
    string getPassword() { return password; }
};

// Event class - with date field
class Event {
private:
    string eventName;
    string eventDate;
public:
    Event() {}
    Event(string name, string date) { 
        eventName = name; 
        eventDate = date;
    }
    void setEventName(string name) { eventName = name; }
    void setEventDate(string date) { eventDate = date; }
    string getEventName() { return eventName; }
    string getEventDate() { return eventDate; }
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
    CommunityMember() : User(0, "Unknown", "") {
        appCount = 0;
    }

    CommunityMember(int id, string n, string pwd) : User(id, n, pwd) {
        appCount = 0;
    }

    void viewEvents(Event eventList[], int eventCount) {
        cout << "\n=== Available Events ===\n";
        if (eventCount == 0) {
            cout << "No events are currently available.\n";
            return;
        }
        
        for (int i = 0; i < eventCount; i++) {
            cout << i + 1 << ". " << eventList[i].getEventName() 
                 << " | Date: " << eventList[i].getEventDate() << endl;
        }
    }

    void applyEvent(Event eventList[], int eventCount) {
        if (eventCount == 0) {
            cout << "No events are currently available to apply for.\n";
            return;
        }
        
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
        cout << "\n=== Application Status ===\n";
        if (appCount == 0) {
            cout << "You haven't applied for any events yet.\n";
            return;
        }
        
        for (int i = 0; i < appCount; i++) {
            cout << i + 1 << ". Event: " << applications[i].getEvent() << " | Status: " << applications[i].getStatus() << endl;
        }
    }

    Application* getApplications() { return applications; }
    int getAppCount() { return appCount; }

    void displayMenu() {
        cout << "\n=== Community Member Menu ===\n";
        cout << "1. View Events\n2. Apply for Event\n3. Check Application Status\n4. Logout\n";
    }
};

// Administrator class (Inheritance)
class Administrator : public User {
public:
    Administrator(int id, string n, string pwd) : User(id, n, pwd) {}

    void addEvent(Event eventList[], int &eventCount) {
        string name, date;
        cout << "Enter new event name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter event date (format: Month Day, Year): ";
        getline(cin, date);
        eventList[eventCount] = Event(name, date);
        eventCount++;
        cout << "Event added successfully.\n";
    }

    void viewApplications(CommunityMember members[], int memberCount) {
        cout << "\n=== All Applications ===\n";
        bool foundApplications = false;
        for (int i = 0; i < memberCount; i++) {
            Application* apps = members[i].getApplications();
            int appCount = members[i].getAppCount();
            for (int j = 0; j < appCount; j++) {
                cout << "Application ID: " << i*10 + j << " | Member ID: " << members[i].getUserID() 
                     << " | Name: " << members[i].getName() << " | Event: " << apps[j].getEvent() 
                     << " | Status: " << apps[j].getStatus() << endl;
                foundApplications = true;
            }
        }
        if (!foundApplications) {
            cout << "No applications have been submitted yet.\n";
        }
    }

    void updateStatus(CommunityMember members[], int memberCount) {
        viewApplications(members, memberCount);
        
        int appID;
        string decision;
        
        cout << "\nEnter Application ID to update: ";
        cin >> appID;
        
        int memberIndex = appID / 10;
        int appIndex = appID % 10;
        
        if (memberIndex >= 0 && memberIndex < memberCount) {
            Application* apps = members[memberIndex].getApplications();
            int appCount = members[memberIndex].getAppCount();
            
            if (appIndex >= 0 && appIndex < appCount) {
                cout << "Enter decision (approve/reject): ";
                cin >> decision;
                
                if (decision == "approve") {
                    apps[appIndex].approve();
                    cout << "Application approved successfully.\n";
                } else if (decision == "reject") {
                    apps[appIndex].reject();
                    cout << "Application rejected successfully.\n";
                } else {
                    cout << "Invalid decision. Please enter 'approve' or 'reject'.\n";
                }
            } else {
                cout << "Invalid application index.\n";
            }
        } else {
            cout << "Invalid member index.\n";
        }
    }
    
    void addMember(CommunityMember members[], int &memberCount) {
        int id;
        string name, password;
        
        cout << "\n=== Add New Community Member ===\n";
        cout << "Enter Member ID: ";
        cin >> id;
        
        // Check if ID already exists
        for (int i = 0; i < memberCount; i++) {
            if (members[i].getUserID() == id) {
                cout << "A member with this ID already exists.\n";
                return;
            }
        }
        
        cout << "Enter Member Name: ";
        cin.ignore();
        getline(cin, name);
        
        cout << "Enter Member Password: ";
        getline(cin, password);
        
        members[memberCount] = CommunityMember(id, name, password);
        memberCount++;
        
        cout << "Member added successfully.\n";
    }
    
    void deleteMember(CommunityMember members[], int &memberCount) {
        int id;
        
        cout << "\n=== Delete Community Member ===\n";
        cout << "Current Members:\n";
        for (int i = 0; i < memberCount; i++) {
            cout << "ID: " << members[i].getUserID() << " | Name: " << members[i].getName() << endl;
        }
        
        cout << "Enter Member ID to delete: ";
        cin >> id;
        
        int index = -1;
        for (int i = 0; i < memberCount; i++) {
            if (members[i].getUserID() == id) {
                index = i;
                break;
            }
        }
        
        if (index != -1) {
            // Shift all members after the deleted one
            for (int i = index; i < memberCount - 1; i++) {
                members[i] = members[i + 1];
            }
            memberCount--;
            cout << "Member deleted successfully.\n";
        } else {
            cout << "Member not found.\n";
        }
    }

    void displayMenu() {
        cout << "\n=== Administrator Menu ===\n";
        cout << "1. Add Event\n2. View Applications\n3. Approve/Reject Applications\n";
        cout << "4. Add Community Member\n5. Delete Community Member\n6. Logout\n";
    }
};

// Function to initialize events
void initializeEvents(Event eventList[], int &eventCount) {
    eventList[0] = Event("Community Spring Cleanup", "April 10, 2025");
    eventList[1] = Event("Tech Workshop: AI Fundamentals", "April 15, 2025");
    eventList[2] = Event("Earth Day Celebration", "April 22, 2025");
    eventList[3] = Event("Neighborhood Potluck Dinner", "April 30, 2025");
    eventCount = 4;
}

// Function to initialize test users
void initializeUsers(CommunityMember members[], int &memberCount) {
    members[0] = CommunityMember(101, "John Doe", "password123");
    members[1] = CommunityMember(102, "Jane Smith", "user456");
    members[2] = CommunityMember(103, "Alex Johnson", "secure789");
    memberCount = 3;
}

int main() {
    Event eventList[20];
    int eventCount = 0;
    
    // Initialize events
    initializeEvents(eventList, eventCount);

    CommunityMember members[20];
    int memberCount = 0;
    
    // Initialize test users
    initializeUsers(members, memberCount);

    Administrator admin(999, "Admin", "admin123");

    while (true) {
        int userType;
        cout << "\n======================================\n";
        cout << "=== Community Event Management System ===\n";
        cout << "======================================\n";
        cout << "Login As:\n1. Community Member\n2. Administrator\n3. Exit\nChoose option: ";
        cin >> userType;

        if (userType == 1) {
            int id;
            string password;
            bool validLogin = false;
            
            cout << "Enter your ID: ";
            cin >> id;
            cout << "Enter your Password: ";
            cin >> password;
            
            int index = -1;
            for (int i = 0; i < memberCount; i++) {
                if (members[i].getUserID() == id && members[i].getPassword() == password) {
                    index = i;
                    validLogin = true;
                    break;
                }
            }
            
            if (!validLogin) {
                cout << "Invalid ID or Password. Please try again.\n";
                continue;
            }
            
            cout << "\n=== Welcome, " << members[index].getName() << "! ===\n";
            
            // Show events immediately after login
            members[index].viewEvents(eventList, eventCount);
            
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
            string username, password;
            cout << "Enter Admin Username: ";
            cin >> username;
            cout << "Enter Admin Password: ";
            cin >> password;
            
            if (username != "admin" || password != "admin123") {
                cout << "Invalid admin credentials. Access denied.\n";
                continue;
            }
            
            cout << "\n=== Administrator Panel ===\n";
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
                    admin.addMember(members, memberCount);
                else if (opt == 5)
                    admin.deleteMember(members, memberCount);
                else if (opt == 6)
                    break;
                else
                    cout << "Invalid option.\n";
            }
        }
        else if (userType == 3) {
            cout << "Thank you for using the Community Event Management System.\n";
            break;
        }
        else {
            cout << "Invalid login type.\n";
        }
    }

    return 0;
}
