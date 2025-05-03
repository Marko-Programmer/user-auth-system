#pragma once

#include <string>

class User {
private:
    std::string Username;
    std::string Password;
    std::string Role;
    bool isActive;

public: 
    User(std::string name, std::string password, std::string role = "user");

    std::string getUsername() const;
    std::string getPassword() const;
    std::string getRole() const;

    void setPassword(const std::string& newPassword);
    void setRole(const std::string& newRole);

    void setActive(bool status);
    bool getActive() const;

    bool checkPassword(const std::string& pass) const;

    bool operator==(const User& other) const;

    struct HashFunction {
        size_t operator()(const User& user) const;
    };
};



 