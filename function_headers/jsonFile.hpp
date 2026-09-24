#pragma once

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void cacheToFile(json& j, std::string fName);
std::string loadApiFile(std::ifstream& f);