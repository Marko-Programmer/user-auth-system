#pragma once

#include <unordered_set>
#include <iostream>
#include <string>
#include "../include/user.h"
#include "../include/dbManager.h"
#include "../include/utils.h" 

class actionMenu {
public:
    std::unordered_set<User, User::HashFunction>& users;
    dbManager* database;   
    User*& activeUser;

    actionMenu(std::unordered_set<User, User::HashFunction>& users, dbManager* database, User*& activeUser);

    void viewUserInfo();
    virtual void viewAllUsers();
    void changePassword();
    void exitProfile();
    virtual void displayMenu();
};
