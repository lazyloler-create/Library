#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

void cacheToFile(json& j, std::string fName);
void openJson(json& j, std::string fName);
std::string loadJson(json& j, std::string fName);