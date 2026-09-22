#pragma once

#include <fstream>
#include <string>
#include "../classes/open_file.hpp"

bool checkIfOpen(std::ifstream& f);
std::string getDir(OpenFile& f);
void moveToDir(const std::string& src, const std::string& dest);