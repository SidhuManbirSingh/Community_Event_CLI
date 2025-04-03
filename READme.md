Event Management System

Overview

The Event Management System is a C++ console-based application designed to manage events and user participation within a community. It implements object-oriented programming (OOP) principles such as abstraction, inheritance, and encapsulation to create a flexible and modular system. The application supports two types of users: Community Members and Administrators, each with distinct functionalities. Community Members can view events, apply to participate, and check their application status, while Administrators can add events, view applications, and approve or reject them.

This project simulates a simple event management workflow, demonstrating how OOP can be applied to real-world scenarios like community event coordination.
Features

Community Member Features

    View Events: Displays a list of available events.
    Apply for Events: Allows members to apply for an event, with a maximum of 10 applications per member.
    Check Application Status: Shows the status (Pending, Approved, or Rejected) of all submitted applications.

Administrator Features

    Add Events: Creates new events and adds them to the event list (up to 20 events).
    View Applications: Displays all applications submitted by Community Members, including member names, event names, and statuses.
    Approve/Reject Applications: Updates the status of a specific application based on member ID and event name.

General Features

    User Login: Supports login for both Community Members and Administrators, with an option to exit the program.
    Dynamic User Creation: New Community Members are created on login if their ID doesn’t exist, up to a limit of 10 members.

Project Structure

The code is organized into several classes, leveraging OOP principles:
Classes

    User (Abstract Base Class)
        Purpose: Provides a common interface for all user types.
        Attributes: userID (int), name (string).
        Methods:
            Constructor: User(int id, string n)
            Pure virtual function: virtual void displayMenu() = 0
            Getters: getUserID(), getName()
            
        OOP Principle: Abstraction (pure virtual function enforces implementation in derived classes).
        
    Event
        Purpose: Represents an event in the system.
        Attributes: eventName (string).
        Methods:
            Constructors: Default and parameterized (Event(string name)).
            Setter: setEventName(string name)
            Getter: getEventName()
        OOP Principle: Encapsulation (private attribute with public access methods).
        
    Application
        Purpose: Manages a Community Member’s application to an event.
        Attributes: eventName (string), status (string, default "Pending").
        Methods:
            Constructors: Default and parameterized (Application(string e)).
            Status updates: approve(), reject()
            Getters: getEvent(), getStatus()
            
        OOP Principle: Encapsulation.
        
    CommunityMember (Derived Class)
        Purpose: Represents a community member who can interact with events.
        Inherits: User
        Attributes: applications (array of Application, size 10), appCount (int).
        Methods:
            Constructors: Default and parameterized.
            Event interaction: viewEvents(), applyEvent(), checkStatus()
            Helpers: getApplications(), getAppCount()
            Override: displayMenu()
            
        OOP Principle: Inheritance (extends User).
        
    Administrator (Derived Class)
        Purpose: Represents an admin who manages events and applications.
        Inherits: User
        Methods:
            Constructor: Parameterized.
            Admin tasks: addEvent(), viewApplications(), updateStatus()
            Override: displayMenu()
            
        OOP Principle: Inheritance.

Main Function

    Purpose: Orchestrates the program flow, handling user login and menu navigation.
    Data Structures:
        Event eventList[20]: Array to store events (max 20).
        CommunityMember members[10]: Array to store members (max 10).
        Administrator admin: Single admin instance (ID 1, name "Admin").
    Flow: Loops through login options, directing users to their respective menus until they log out or exit.

Prerequisites

    Compiler: A C++ compiler (e.g., g++, MinGW, or any IDE like Visual Studio, Code::Blocks).
    Operating System: Compatible with any OS supporting a C++ compiler (Windows, Linux, macOS).
    Standard Library: Uses <iostream> for input/output operations.

Installation

    Clone or Download: Obtain the source code file (e.g., event_management.cpp).
    Compile: Use a C++ compiler to compile the code. For example:
    bash

    g++ event_management.cpp -o event_management

Run: Execute the compiled program:

    ./event_management   # Linux/macOS
    event_management.exe # Windows

Usage
Running the Program

    Launch the executable.
    Choose a login option:
        1: Community Member
        2: Administrator
        3: Exit

Community Member Workflow

    Login: Enter an ID (integer) and name (string). If the ID is new, a new member is created (up to 10 members).
    Menu Options:
        1: View available events.
        2: Apply for an event by entering its number.
        3: Check the status of all applications.
        4: Logout.
    Repeat until logout.

Administrator Workflow

    Login: Select option 2 (predefined admin: ID 1, name "Admin").
    Menu Options:
        1: Add a new event by entering its name (up to 20 events).
        2: View all applications from all members.
        3: Update an application status by entering member ID, event name, and decision (approve/reject).
        4: Logout.
    Repeat until logout.

Example Interaction

Login As:
1. Community Member
2. Administrator
3. Exit
Choose option: 1
Enter your ID: 101
Enter your Name: Alice

1. View Events
2. Apply for Event
3. Check Application Status
4. Logout
Choose option: 1

Available Events:
(No events yet)
Choose option: 4

Login As:
1. Community Member
2. Administrator
3. Exit
Choose option: 2

1. Add Event
2. View Applications
3. Approve/Reject Applications
4. Logout
Choose option: 1
Enter new event name: Charity Run
Event added successfully.
Choose option: 4

Limitations

    Fixed Arrays: Limited to 20 events and 10 members due to static array sizes.
    No Persistence: Data is not saved between runs (in-memory only).
    Input Validation: Minimal error checking (e.g., no handling for duplicate IDs or invalid input types).
    Single Admin: Only one hardcoded administrator (ID 1, "Admin").
    Application Limit: Each member can apply to a maximum of 10 events.

Potential Improvements

    Dynamic Memory: Use std::vector instead of fixed arrays for events and members.
    File Storage: Add file I/O to save and load events, members, and applications.
    Input Validation: Enhance error handling for invalid inputs (e.g., non-numeric IDs).
    Multiple Admins: Support multiple administrators with login credentials.
    Event Details: Expand Event class with attributes like date, location, or capacity.
    User Interface: Upgrade to a graphical UI (e.g., using Qt) instead of console-based.

Code Explanation

Key OOP Concepts

    Abstraction: User class defines a common interface with a pure virtual displayMenu() function, forcing derived classes to implement it.
    Inheritance: CommunityMember and Administrator inherit from User, sharing common attributes (userID, name) while adding specialized behavior.
    Encapsulation: Private attributes (e.g., eventName in Event) are accessed via public methods, protecting data integrity.

Main Logic

    The main() function uses a loop to handle user login and menu navigation.
    Community Members are stored in an array and identified by userID. New members are added dynamically up to the limit.
    Events and applications are managed through their respective classes, with Administrators having control over the system state.

Troubleshooting

    Compilation Error: Ensure a C++ compiler is installed and the code is saved with a .cpp extension.
    No Output: Check that input is provided correctly (e.g., no extra spaces after numbers).
    Array Overflow: Avoid adding more than 20 events or 10 members to prevent undefined behavior.

Contributing

Feel free to fork this project and submit pull requests with enhancements. Suggestions for improvement include:

    Adding unit tests using a framework like Google Test.
    Implementing data persistence with files or a database.
    Enhancing the UI for better user experience.

License

This project is open-source and available under the MIT License. You are free to use, modify, and distribute it as needed.
Author

    Name: Manbir Singh Sidhu
    Date: April 02, 2025
 

This README provides everything you need to understand, use, and extend the Event Management System. Let me know if you’d like to tweak any section further!
