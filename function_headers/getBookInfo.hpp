#pragma once

#include <nlohmann/json.hpp>

std::string GetTitle(std::string q);
std::string GetAuthor(std::string q);
std::string GetDate(std::string q);
std::string GetISBN(std::string q);