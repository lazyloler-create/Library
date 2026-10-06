#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <nlohmann/json.hpp>

#include "../classes/book_class.hpp"
#include "../function_headers/jsonFile.hpp"
#include "../classes/treenode_class.hpp"
#include "../function_headers/getBookInfo.hpp"

using json = nlohmann::json;

std::vector<std::string> getCatVec(std::vector<std::string> bookVec){
    std::vector<std::string> catVec;
    for(auto it : bookVec){
        catVec.push_back(getCategory(it));
    }
    return catVec;
}

//returns a json with books attributes 
json cacheBookAttribute(json& jsonArr, Book& b, int ID){
    if (jsonArr.is_null()) {
        jsonArr = nlohmann::json::array();
    }

    json bookJson = nlohmann::json::object();
    bookJson["Title"] = b.getTitle();
    bookJson["Author"] = b.getAuthor();
    bookJson["Date"] = b.getDate();
    bookJson["ISBN"] = ID;

    jsonArr.push_back(bookJson);
    return jsonArr;
}

//returns a json with categories cached
json cacheCategories(std::string cat, json& jsonArr){
    if (jsonArr.is_null()) {
        jsonArr = nlohmann::json::object();
    }
    if (!jsonArr.contains("Categories") || !jsonArr["Categories"].is_array()) {
        jsonArr["Categories"] = nlohmann::json::array();
    }

    jsonArr["Categories"].push_back(cat);
    return jsonArr;
}

//checks all the cached categories in categories_cache.json
std::vector<std::string> checkCachedCat(std::string fName){
    std::vector<std::string> categories;
    std::ifstream file(fName + ".json");
    if(!file.is_open()){
        return {};
    }

    try {
        auto j = json::parse(file);
        categories = j.at("Categories").get<std::vector<std::string>>();
    } catch (const json::out_of_range&) {
        std::cerr << "Key is missing" << std::endl;
    } catch(const json::parse_error& ex){
        std::cerr<<"Json parse error: " << ex.what() << std::endl; 
    }
    return categories;
}

//inserts a category string into a CategoryTree and creates an empty bst,
//CategoryTree = std::map<std::string, std::unique_ptr<TreeNode>>
CategoryTrees insertCategory(std::string cat){
    CategoryTrees categoryTree;
    categoryTree.insert({cat, nullptr});

    return categoryTree;
}

//used for inserting a category string into a CategoryTree in loops
void insertCategory(CategoryTrees& categoryTree, std::string cat){
    categoryTree.insert({cat, nullptr});
}

//inserts a vector of categories made by checkCachedCat(std::string fName, json& j)
void insertCategories(CategoryTrees& categoryTree, std::vector<std::string> categories){
    for(int i = 0; i < categories.size(); i++)
        insertCategory(categoryTree, categories[i]);
}