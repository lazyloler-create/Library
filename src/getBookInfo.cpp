#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <nlohmann/json.hpp>
#include <httplib.h>

using json = nlohmann::json;

//returns a std::string based on query link and the parameter of the API
std::string getReqInf(std::string param){
    httplib::SSLClient cli("openlibrary.org");
    
    auto path        = "/search.json?q=" + param;
    auto res = cli.Get(path);
    std::string info;
    
    if(res && res->status == 200){
        try{
            auto j = json::parse(res->body);
             info = j[param].get<std::string>();
        } catch(const json::parse_error& e){
            std::cerr << "JSON parse error" << e.what() << std::endl;
        }
    }
    return info;
}

std::string GetTitle(){
    return getReqInf("title");
}

std::string GetAuthor(){
    return getReqInf("author");
}

std::string GetDate(){
    return getReqInf("publish_date");
}

std::string GetISBN(){
    return getReqInf("isbn_10");
}