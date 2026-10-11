#pragma once 

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../classes/book_class.hpp"
#include "../classes/treenode_class.hpp"

using json = nlohmann::json;

std::vector<std::vector<std::string>> getCatArr(const std::vector<std::string>& bookVec);
json cacheBookAttribute(json& j, Book& b, int ID);
json cacheCategories(std::string cat, json& jsonArr);
std::vector<std::string> checkCachedCat(std::string fName);
void insertCategory(CategoryTrees& categoryTree, const std::string& cat);
void insertCategories(CategoryTrees& categoryTree, const std::vector<std::string>& categories);
void insertCategories(
    CategoryTrees& categoryTree,
    const std::vector<std::vector<std::string>>& categoriesByBook
);