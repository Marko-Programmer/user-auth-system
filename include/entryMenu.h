#pragma once
 

#include <iostream>
#include <string>
#include <unordered_set>
#include "../include/user.h"
#include "../include/dbManager.h"
#include "../include/utils.h"

class entryMenu {
private:
    std::unordered_set<User, User::HashFunction>& users;
    dbManager* database;
    User*& activeUser;

public:
    entryMenu(std::unordered_set<User, User::HashFunction>& users, dbManager* database, User*& activeUser);

    void registration();
    void login();
    void exit();
    void displayMenu();
     
};
 
