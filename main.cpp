#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "function_headers/categories_functions.hpp"
#include "./function_headers/jsonFile.hpp"

using json = nlohmann::json;

int main(){
    std::vector<std::string> categories;
    json cachedCategories;
 
    try{
        std::ifstream categoriesCacheFile("categories_cache.json");
        cachedCategories = json::parse(categoriesCacheFile);
    }catch(...){

    }
    
    return 0;
}