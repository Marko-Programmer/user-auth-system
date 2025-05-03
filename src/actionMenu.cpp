#include "../include/actionMenu.h"
#include <iomanip> 

using namespace std;

actionMenu::actionMenu(std::unordered_set<User, User::HashFunction>& users, dbManager* database, User*& activeUser)
    : users(users), database(database), activeUser(activeUser) {}

void actionMenu::viewUserInfo() {
    clearScreen();
    cout << "Username - " << activeUser->getUsername() << ", Hashed Password - " << activeUser->getPassword() << "." << endl;
}

void actionMenu::viewAllUsers() {
    clearScreen();

    cout << left << setw(20) << "Username" << "\n\n";
    for (const auto& user : users) {
        cout << setw(20) << user.getUsername()<< endl;
    }
}

void actionMenu::changePassword() {
    string pass;
    int passcount = 4;
    cin.ignore();

    do {
        cout << "Enter your previous Password: ";
        getline(cin, pass);

        while (!isValidInput(pass)) {
            cout << "Invalid password! Try again: ";
            getline(cin, pass);
        }

        std::size_t hashedPass = simpleHash(pass);
        pass = to_string(hashedPass);

        if (!activeUser->checkPassword(pass)) {
            passcount--;
            if (passcount == 0) {
                cout << "You have entered the wrong password too many times!" << endl;
                std::exit(0);
            }
            cout << "Incorrect password! Try again, you have " << passcount << " attempt(s)." << endl;
        }

    } while (!activeUser->checkPassword(pass));

    string newPass;
    cout << "Enter your new password: ";
    getline(cin, newPass);

    while (!isValidInput(newPass)) {
        cout << "Invalid password! Try again: ";
        getline(cin, newPass);
    }

    std::size_t hashedPass = simpleHash(newPass);
    newPass = to_string(hashedPass);

    activeUser->setPassword(newPass);
    database->changePassword(activeUser->getUsername(), newPass);

    clearScreen();
    cout << "Password successfully updated!" << endl;
}

void actionMenu::exitProfile() {
    clearScreen();
    cout << activeUser->getUsername() << ", you have successfully logged out.\n" << endl;
    activeUser = nullptr;
}

void actionMenu::displayMenu() {
    cout << "\nProgram Menu:\n";
    cout << "1. View your info\n";
    cout << "2. View all users\n";
    cout << "3. Change password\n";
    cout << "4. Exit profile\n";

    cout << "Your choice: ";
    char userChoice;
    cin >> userChoice;

    while (userChoice < '1' || userChoice > '4') {
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
        exitProfile();
        break;
    }
}