#include "../include/dbManager.h"

dbManager::dbManager(const string& server, const string& username, const string& password, const string& database) {
    driver = get_driver_instance();
    con = unique_ptr<sql::Connection>(driver->connect(server, username, password));
    con->setSchema(database);
}

unordered_set<User, User::HashFunction> dbManager::getAllUsers() {
    unordered_set<User, User::HashFunction> dbUsers;

    try {

        unique_ptr<sql::Statement> stmt(con->createStatement());
        unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT username, hashed_password, role FROM authsystem.users"));

        while (res->next()) {
            string username = res->getString("username");
            string password = res->getString("hashed_password");
            string role = res->getString("role");
            dbUsers.insert(User(username, password, role));
        }
    } 
    catch (sql::SQLException& e) {
        cerr << "SQL Error in getAllUsers(): " << e.what() << endl;
    } 

    return dbUsers;
}

void dbManager::changePassword(const string& username, const string& newPass) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            con->prepareStatement("UPDATE users SET hashed_password = ? WHERE username = ?")
        );
        pstmt->setString(1, newPass);
        pstmt->setString(2, username);
        pstmt->executeUpdate();
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error in changePassword(): " << e.what() << endl;
    }
}

void dbManager::registration(const User& newUser) {
    try {
    unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("INSERT INTO users (username, hashed_password) VALUES (?, ?)")
    );
    pstmt->setString(1, newUser.getUsername());
    pstmt->setString(2, newUser.getPassword());
    pstmt->executeUpdate();
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error in registration(): " << e.what() << endl;
    }
}
 
void dbManager::deleteUser(const string& username) {
    try {
    unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("DELETE FROM users WHERE username = ?")
    );
    pstmt->setString(1, username); 
    pstmt->executeUpdate();
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error in deleteUser(): " << e.what() << endl;
    }
}

void dbManager::promoteUser(const string& username) {
    try {
    unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("UPDATE users set role = 'admin' where username = ?")
    );
    pstmt->setString(1, username);
    pstmt->executeUpdate();
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error in promoteUser(): " << e.what() << endl;
    }
}

void dbManager::demoteUser(const string& username) {
    try {
    unique_ptr<sql::PreparedStatement> pstmt(
        con->prepareStatement("UPDATE users set role = 'user' where username = ?")
    );
    pstmt->setString(1, username);
    pstmt->executeUpdate();
    }
    catch (sql::SQLException& e) {
        cerr << "SQL Error in demoteUser(): " << e.what() << endl;
    }
}