#pragma once 

#include <string>
#include <nlohmann/json.hpp>
#include "../classes/book_class.hpp"
#include "../classes/treenode_class.hpp"

using json = nlohmann::json;

std::vector<std::string> getCatVec(std::vector<std::string>& bookVec);
json cacheBookAttribute(json& j, Book& b, int ID);
json cacheCategories(std::string cat, json& jsonArr);
std::vector<std::string> checkCachedCat(std::string fName);
void insertCategory(CategoryTrees& categoryTree, std::string cat);
void insertCategories(CategoryTrees& categoryTree, std::vector<std::string> categories);