#include "../include/utils.h"


void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

bool isValidInput(const std::string& input) {
    return !(input.empty() || input.find(' ') != std::string::npos);
}

std::size_t simpleHash(const std::string& password) {
    return std::hash<std::string>{}(password);
}


std::map<std::string, std::string> loadConfig(const std::string& filename) {
    std::map<std::string, std::string> config;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        auto pos = line.find('=');
        if (pos != std::string::npos) {
            config[line.substr(0, pos)] = line.substr(pos + 1);
        }
    }
    return config;
}