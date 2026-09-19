#include <nlohmann/json.hpp>
#include <httplib.h>

using json = nlohmann::json;

//returns a std::string based on query link and the parameter of the API
std::string getReqInf(std::string query, std::string param){
    httplib::Client cli(query);

    auto res = cli.Get(query);
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

std::string GetTitle(std::string q){
    return getReqInf(q, "title");
}

std::string GetAuthor(std::string q){
    return getReqInf(q, "author");
}

std::string GetDate(std::string q){
    return getReqInf(q, "publish_date");
}

std::string GetISBN(std::string q){
    return getReqInf(q, "isbn_10");
}