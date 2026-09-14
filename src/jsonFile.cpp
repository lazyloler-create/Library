#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

//caches any type of json to a file with an indent of 4
void cacheToFile(json& j, std::string fName){
    std::ofstream f(fName + ".json");
    f << j.dump(4);
} 