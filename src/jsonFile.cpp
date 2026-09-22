#include <fstream>
#include <nlohmann/json.hpp>
#include "../function_headers/file_functions.hpp"

using json = nlohmann::json;

//caches any type of json to a file with an indent of 4
void cacheToFile(json& j, std::string fName){
    std::ofstream f(fName + ".json");
    f << j.dump(4);
} 

//returns a string with a url from an api json file,
std::string loadApiFile(std::string fName){
    std::ifstream f(fName + ".json");
    if(!checkIfOpen(f)){
        return {};
    }
    auto j = nlohmann::json::parse(f);
    return j[0]["api_url"]; //"api_url" is an string in json containing a link to open library API
}