#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <variant>
#include <nlohmann/json.hpp>

#include "classes/treenode_class.hpp"
#include "function_headers/categories_functions.hpp"
#include "./function_headers/jsonFile.hpp"
#include "./function_headers/rentBook.hpp"

using json = nlohmann::json;
auto url = loadApiFile("api");


int main(){
    std::vector<std::string> categories;
    json cachedCategories;
 
    try{
        std::ifstream categoriesCacheFile("categories_cache.json");
        cachedCategories = json::parse(categoriesCacheFile);
    }catch(...){

    }
    checkCategories(categories, cachedCategories);
   
    
    return 0;
}