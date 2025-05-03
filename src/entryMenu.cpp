#include "../include/entryMenu.h"

using namespace std;

entryMenu::entryMenu(unordered_set<User, User::HashFunction>& users, dbManager* database, User*& activeUser)
    : users(users), database(database), activeUser(activeUser) {
}

void entryMenu::registration() {
    string name, pass;

    do {
        cout << "\nEnter Username to register: ";
        getline(cin, name);

        while (!isValidInput(name)) {
            cout << "Invalid username! Try again: ";
            getline(cin, name);
        }

        User tempUser(name, "");

        if (users.find(tempUser) != users.end()) {
            cout << "Username already exists. Try again." << endl;
        }

    } while (users.find(User(name, "")) != users.end());

    cout << "Enter your Password: ";
    getline(cin, pass);

    while (!isValidInput(pass)) {
        cout << "Invalid password! Try again: ";
        getline(cin, pass);
    }


    std::size_t hashedPass = simpleHash(pass);
    User newUser(name, std::to_string(hashedPass));
    //User newUser(name, pass);
    users.insert(newUser);
    database->registration(newUser);

    auto it = users.find(newUser);
    if (it != users.end()) {
        User* loggedInUser = const_cast<User*>(&(*it));
        loggedInUser->setActive(true);
        activeUser = loggedInUser;
    }

    clearScreen();
    cout << "Welcome to our platform " << name << "!" << endl;
}

void entryMenu::login() {
    string name, pass;

    do {
        cout << "\nEnter your Username: ";
        getline(cin, name);

        while (!isValidInput(name)) {
            cout << "Invalid username! Try again: ";
            getline(cin, name);
        }

        User tempUser(name, "");

        if (users.find(tempUser) == users.end()) {
            cout << "Username does not exist. Try again." << endl;
        }

    } while (users.find(User(name, "")) == users.end());

    User tempUser(name, "");
    auto it = users.find(tempUser);
    int count = 4;

    do {
        cout << "Enter your Password: ";
        getline(cin, pass);

        while (!isValidInput(pass)) {
            cout << "Invalid password! Try again: ";
            getline(cin, pass);
        }

        std::size_t hashedPass = simpleHash(pass);
        pass = std::to_string(hashedPass);

        if (!it->checkPassword(pass)) {
            count--;
            if (count == 0) {
                cout << "You have entered the wrong password too many times!" << endl;
                std::exit(0);
            }
            cout << "Incorrect password! Try again, you have " << count << " attempt(s)." << endl;
        }

    } while (!it->checkPassword(pass));

    User* loggedInUser = const_cast<User*>(&(*it));
    loggedInUser->setActive(true);
    activeUser = loggedInUser;

    clearScreen();
    cout << "Login successful! Welcome " << name << "!" << endl;


}

void entryMenu::exit() {
    clearScreen();
    cout << "Until next time!" << endl;
    std::exit(0);
}

void entryMenu::displayMenu() {
    cout << "Main Menu:\n";
    cout << "\t1. Register\n";
    cout << "\t2. Log in\n";
    cout << "\t3. Exit\n";
    cout << "Choose your option: ";
    char choice;
    cin >> choice;

    while (choice != '1' && choice != '2' && choice != '3') {
        cout << "That's incorrect choice, try again: ";
        cin >> choice;
    }

    cin.ignore();

    switch (choice) {
    case '1':
        registration();
        break;
    case '2':
        login();
        break;
    case '3':
        exit();
        break;
    }
}