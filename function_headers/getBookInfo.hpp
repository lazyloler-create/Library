#pragma once

#include <nlohmann/json.hpp>

std::vector<std::string> getReqInf(std::string q);
std::string getTitle(std::string& b);
std::string getAuthor(std::string& b);
std::string getCategory(std::string& b);
std::string getEdition(std::string& b);