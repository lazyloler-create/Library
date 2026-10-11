#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <nlohmann/json.hpp>
#include <httplib.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "dotenv.h" 

using namespace dotenv;

using json = nlohmann::json;

//returns books info in a JSON object, containts books details such as: title, authors, categories
json getBookInfo(std::string& book){
    dotenv::env.load_dotenv(".env");
    const std::string apiKey = dotenv::env["API_KEY"];

    if(apiKey.empty()){
        throw std::runtime_error("\nAPI_KEy failed to load or is missing!\n");
    }

    httplib::SSLClient client("www.googleapis.com");
    
    auto url = "/books/v1/volumes?q=" + book + "&key=" + apiKey;
    auto response = client.Get(url);

    if(response->status != 200){
        throw std::runtime_error("Google books returned HTTP status" + std::to_string(response->status));
    }
    
    const json data = json::parse(response->body);

    if(!data.contains("items") || !data["items"].is_array()){
        return json{};
    }

    for(const auto& it : data["items"]){
        const auto& inf = it.value("volumeInfo", json::object());
        const std::string foundTitle = inf.value("title", "");

        if (foundTitle == book) {
            return inf;
        }
    }
    return json{};
}

std::string reqTitle(std::string& book){
    const auto& result = getBookInfo(book);
    const auto title = result.at("title");
    
    return title;
}