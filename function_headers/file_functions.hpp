#pragma once

#include <string>
#include "../classes/open_file.hpp"

std::string getDir(OpenFile& f);
void moveToDir(const std::string& src, const std::string& dest);