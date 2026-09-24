#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

//caches any type of json to a file with an indent of 4
void cacheToFile(json& j, std::string fName){
    std::ofstream f(fName + ".json");
    f << j.dump(4);
} 

//returns a string with a url from an api json file,
std::string loadApiFile(std::string fName){
    std::ifstream f(fName + ".json");
    if(!f.is_open()){
        std::cout<<"Cannot open file" << fName + ".json" << std::endl;
        return {};
    }
    auto j = nlohmann::json::parse(f);
    return j[0]["api_url"]; //"api_url" is an string in json containing a link to open library API
}