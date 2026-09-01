#ifndef CATEGORIES_FUNCTIONS_HPP
#define CATEGORIES_FUNCTIONS_HPP

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "../classes/book_class.hpp"

using json = nlohmann::json;


void cacheBookAttribute(json& j, Book& b, int ID);
void cacheCategories(std::string& cat, json& jsonArr);
void createCategories(std::vector<std::string>& categories);
void checkCategories(std::vector<std::string>& categories);

#endif