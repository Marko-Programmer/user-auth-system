#include <iostream>
#include <string>
#include <unordered_set>

#include "../include/actionMenu.h"
#include "../include/adminMenu.h"
#include "../include/dbManager.h"
#include "../include/entryMenu.h"
#include "../include/user.h"
#include "../include/utils.h" 

using namespace std;


int main(){

    auto config = loadConfig("config.txt");

    const string SERVER = config["SERVER"];
    const string DB_USERNAME = config["DB_USERNAME"];
    const string DB_PASSWORD = config["DB_PASSWORD"];
    const string DB_NAME = config["DB_NAME"];


    User* activeUser = nullptr;
    unordered_set<User, User::HashFunction> users; 
    dbManager* database = new dbManager(SERVER, DB_USERNAME, DB_PASSWORD, DB_NAME);

    users = database->getAllUsers();


    while(true) {
      
        entryMenu mainMenu(users, database, activeUser);
        mainMenu.displayMenu();

        while(activeUser != nullptr) { 
            if (activeUser->getRole() == "admin") {
                adminMenu admin(users, database, activeUser);
                admin.displayMenu(); 
            }
            else {
                actionMenu user(users, database, activeUser);
                user.displayMenu();  
            }
        } 

    }


    delete database;
    database = nullptr;

    return 0;
}
