#pragma once
#include "../include/actionMenu.h"
#include <iomanip> 

class adminMenu : public actionMenu {
    private:
        void deleteUser();
        void promoteUser();
        void demoteUser();

    public:
        adminMenu(std::unordered_set<User, User::HashFunction>& users, dbManager* database, User*& activeUser);

        void viewAllUsers() override;
        void displayMenu() override; 
};

