#include "../include/adminMenu.h"
 

adminMenu::adminMenu(std::unordered_set<User, User::HashFunction>& users, dbManager* database, User*& activeUser)
    : actionMenu(users, database, activeUser) {
}

void adminMenu::viewAllUsers() {
    clearScreen();
    cout << left << setw(20) << "Username" << setw(30) << "Hashed Password" << setw(20) << "Role" << "\n\n";
    for (const auto& user : users) { 
        cout << setw(20) << user.getUsername() << setw(30) << user.getPassword() << setw(20) << user.getRole() << endl;
    }
}

void adminMenu::deleteUser() {
    clearScreen(); 
    string username;

    do {
        cout << "Enter the username of the user you want to delete: ";
        cin.ignore();
        getline(cin, username);

        while (!isValidInput(username)) {
            cout << "Invalid username! Try again: ";
            getline(cin, username);
        }

        User tempUser(username, "");

        if (users.find(tempUser) == users.end()) {
            cout << "Username does not exist. Try again." << endl;
        }

    } while (users.find(User(username, "")) == users.end());


    database->deleteUser(username);

    users.erase(User(username, ""));

    cout << "User successfully deleted.\n";
}

void adminMenu::promoteUser() {
    clearScreen();
    string username;

    do {
        cout << "Enter the username of the user you want to promote: ";
        cin.ignore();
        getline(cin, username);

        while (!isValidInput(username)) {
            cout << "Invalid username! Try again: ";
            getline(cin, username);
        }

        User tempUser(username, "");

        if (users.find(tempUser) == users.end()) {
            cout << "Username does not exist. Try again." << endl;
        }

    } while (users.find(User(username, "")) == users.end());




    auto it = users.find(User(username, ""));

    if (it != users.end()) {
        if (it->getRole() == "admin") {
            cout << "User already is an admin." << endl;
        }
        else {
            User updated = *it;
            users.erase(it);
            updated.setRole("admin");
            users.insert(updated);

            database->promoteUser(username);

            cout << "User successfully promoted.\n";
        }
    }

}

void adminMenu::demoteUser() {
    clearScreen();
    string username;

    do {
        cout << "Enter the username of the user you want to demote: ";
        cin.ignore();
        getline(cin, username);

        while (!isValidInput(username)) {
            cout << "Invalid username! Try again: ";
            getline(cin, username);
        }

        User tempUser(username, "");

        if (users.find(tempUser) == users.end()) {
            cout << "Username does not exist. Try again." << endl;
        }

    } while (users.find(User(username, "")) == users.end());

    if (username == activeUser->getUsername()) {
        cout << "You cannot demote yourself!" << endl;
        return;
    }

    auto it = users.find(User(username, ""));

    if (it != users.end()) {
        if (it->getRole() == "user") {
            cout << "User already is an user." << endl;
        }
        else {
            User updated = *it;
            users.erase(it);
            updated.setRole("user");
            users.insert(updated);

            database->demoteUser(username);

            cout << "User successfully demoted.\n";
        }
    }
     
}

void adminMenu::displayMenu() {
    cout << "\nAdmin Menu:\n";
    cout << "1. View your info\n";
    cout << "2. View all user information\n";
    cout << "3. Change password\n";
    cout << "4. Delete user\n";
    cout << "5. Promote user\n";
    cout << "6. Demote user\n";
    cout << "7. Exit profile\n";

    cout << "Your choice: ";
    char userChoice;
    cin >> userChoice;

    while (userChoice < '1' || userChoice > '7') {
        cout << "That's incorrect choice, try again: ";
        cin >> userChoice;
    }

    switch (userChoice) {
    case '1':
        viewUserInfo();
        break;
    case '2':
        viewAllUsers();
        break;
    case '3':
        changePassword();
        break;
    case '4':
        deleteUser();
        break;
    case '5':
        promoteUser();
        break;
    case '6':
        demoteUser();
        break;
    case '7':
        exitProfile();
        break;
    }
}