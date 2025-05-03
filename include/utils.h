#pragma once

#include <string>
#include <fstream>
#include <map>

void clearScreen();

bool isValidInput(const std::string& input);
 
std::size_t simpleHash(const std::string& password);

std::map<std::string, std::string> loadConfig(const std::string& filename);