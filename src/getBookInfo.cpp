#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <nlohmann/json.hpp>
#include <httplib.h>
#include <vector>

using json = nlohmann::json;

//returns a std::string based on query link and the parameter of the API
std::vector<std::string> getReqInf(std::string q){
    httplib::SSLClient cli("openlibrary.org");
    
    std::string param[] = {"title", "author_name", "subjects", "editions"};
    auto path = "/search.json?q=" + q +"&fields=title,author_name,subjects";
    auto res = cli.Get(path);
    std::vector<std::string> info;
    
    if(res && res->status == 200){
        try{
            for(auto it : param)
            {
                auto j = json::parse(res->body);
                info.push_back(j[it].get<std::string>());
            }
        } catch(const json::parse_error& e){
            std::cerr << "JSON parse error" << e.what() << std::endl;
        }
    }
    return info;
}
