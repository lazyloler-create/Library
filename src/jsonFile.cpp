#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>

using json = nlohmann::json;

void cacheToFile(json& j, std::string fName){
    std::ofstream f(fName + ".json");
    f << j.dump(4);
} 

void openJson(json& j, std::string& fName){
    std::ifstream file(fName);
    if(!file.is_open()){
        std::cout<< "Failed to open file" << fName << std::endl;
        return;
    }

    try {
    j = json::parse(file);
    } catch (const json::parse_error& ex) {
        std::cerr << "Json parse error: " << ex.what() << std::endl;
        return;
    }
}

std::string loadJson(json &j, std::string fName){
    openJson(j,fName);
    std::ostringstream buffer;
    std::ifstream file(fName);

    if(!file.is_open()){
        std::cout<< "Failed to open file" << fName << std::endl;
        return {};
    }

    buffer << file.rdbuf();
    try {
        j = json::parse(buffer);

    } catch (const json::parse_error ex) {
        std::cerr << "Json parse error: " << ex.what() << std::endl;
        return {}; //returns empty string
    }
    return buffer.str();
}