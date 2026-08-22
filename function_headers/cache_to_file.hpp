#pragma once

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void cacheToFile(json& j, std::string fName);