#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

void cacheToFile(json& j, std::string fName);