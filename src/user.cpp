#include "../include/User.h" 
#include <functional>
 
User::User(std::string username, std::string password, std::string role)
    : Username(username), Password(password), Role(role), isActive(false) {
} 
std::string User::getUsername() const {
    return Username;
}

std::string User::getPassword() const {
    return Password;
}

std::string User::getRole() const {
    return Role;
}

void User::setPassword(const std::string& newPassword) {
    Password = newPassword;
}

void User::setRole(const std::string& newRole) {
    Role = newRole;
}

void User::setActive(bool status) {
    isActive = status;
}

bool User::getActive() const {
    return isActive;
}

bool User::checkPassword(const std::string& pass) const {
    return pass == Password;
}

bool User::operator==(const User& other) const {
    return Username == other.Username;
}

size_t User::HashFunction::operator()(const User& user) const {
    return std::hash<std::string>()(user.getUsername());
}
