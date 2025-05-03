#pragma once

#include <unordered_set>
#include <memory>
#include <string>
#include "../include/user.h" 



#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;

class dbManager {
private:
    sql::Driver* driver;
    unique_ptr<sql::Connection> con;

public:
    dbManager(const string& server, const string& username, const string& password, const string& database);

    unordered_set<User, User::HashFunction> getAllUsers();
    void changePassword(const string& username, const string& newPass);
    void registration(const User& newUser);
    void deleteUser(const string& username);
    void promoteUser(const string& username);
    void demoteUser(const string& username);
};
