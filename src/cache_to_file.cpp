#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void cacheToFile(json& j, std::string fName){
    std::ofstream f(fName + ".json");
    f << j.dump(4);
} 