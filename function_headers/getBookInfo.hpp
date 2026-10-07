#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

std::string getReqInf(const std::string& q, const std::string& param);
std::string getTitle(const std::string& b);
std::string getAuthor(const std::string& b);
std::string getCategory(const std::string& b);
std::string getEdition(const std::string& b);