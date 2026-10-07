#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <nlohmann/json.hpp>
#include <httplib.h>
#include <vector>

using json = nlohmann::json;

//returns a std::string based on query link and the parameter of the API
std::string getReqInf(const std::string& q, const std::string& param){
    httplib::SSLClient cli("openlibrary.org");
    auto path = "/search.json?q=" + q +"&fields=" + param;
    auto res = cli.Get(path);
    std::string result = "";
    if(res && res->status == 200){
        try{
            auto j = json::parse(res->body);
            result = j["subjects"].dump(1);
        }catch(const json::parse_error& e){
            std::cerr << "JSON parse error" << e.what() << std::endl;
        }
    }
    return result;
}

std::string getTitle(const std::string& b){
    return getReqInf(b, "title");
}

std::string getAuthor(const std::string& b){
    return getReqInf(b, "author_name");
}

std::string getCategory(const std::string& b){
    return getReqInf(b, "subjects");
}

std::string getEdition(const std::string& b){
    return getReqInf(b, "edition");
}