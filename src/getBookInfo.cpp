#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <nlohmann/json.hpp>
#include <httplib.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include "cpp-dotenv/dotenv.h"

using namespace dotenv;

using json = nlohmann::json;

//returns books info in a JSON object, containts books details such as: title, authors, categories

std::string getApiFromFile(){
    const auto& e = dotenv::env.load_dotenv(".env");
    const std::string apiKey = e["GOOGLE_API_KEY"];

    if(apiKey.empty()){
        throw std::runtime_error("\nAPI_KEy failed to load or is missing!\n");
    }
    return apiKey;
}

std::string getApiKey(){
    auto apiKey = getApiKey();

    if(apiKey.empty()){
        return {};
    }
    return apiKey;
}

json getBookInfo(std::string& book){
    
    aut& apiKey = getApiKey();
    httplib::SSLClient client("www.googleapis.com");
    
    auto url = "/books/v1/volumes?q=" + book + "&key=" + apiKey;
    const auto response = client.Get(url);

    if(response->status != 200){
        throw std::runtime_error("Google books returned HTTP status" + std::to_string(response->status));
    }
    
    const auto& data = json::parse(response->body);

    if(!data.contains("items") || !data["items"].is_array()){
        return json{};
    } else{
        return data;
    }

    return json{};
}

std::string getTitle(std::string& book){
    const auto& result = getBookInfo(book);
    std::string title = "";
    if(result.contains("volumeInfo") && result["volumeInfo"].contains("title")){
        title = result.at("volumeInfo").at("title");
    } else{
        return {};
    }
    
    return title;
}

std::string getAuthors(std::string book){
    const auto& result = getBookInfo(book);

    std::vector<std::string> authors;
    if(result.contains("volumeInfo") && result["volumeInfo"].contains("authors")){
        authors = result.at("volumeInfo").at("authors");
    } else{
        return {};
    }

    std::string val;
    for(const auto& author : authors){
        val = author + "&";
    }
    
    if(!val.empty())
        val.resize(val.size() - 1);

    return val;
}

std::string getPublishedDate(std::string book){
    const auto& result = getBookInfo(book);
    std::string date = "";

    if(result.contains("volumeInfo") && result["volumeInfo"].at("publishedDate")){
        date = result.at("volumeInfo").at("publishedDate");
    } else{
        return {};
    }
    return date;
}

std::string getISBN_10(std::string book){
    const auto& result = getBookInfo(book);
    std::string ISBN_10 = "";

    if(result.contains("industryIdentifiers") && result["industryIdentifiers"].at("ISBN_10")){
        ISBN_10 = result.at("industryIdentifiers").at("ISBN_10");
    } else{
        return {};
    }
    return ISBN_10;
}

std::string getISBN_13(std::string book){
    const auto& result = getBookInfo(book);
    std::string ISBN_13 = "";

    if(result.contains("industryIdentifiers") && result["industryIdentifiers"].at("ISBN_13")){
        ISBN_13 = result.at("industryIdentifiers").at("ISBN_13");
    } else{
        return {};
    }
    return ISBN_13;
}

std::string getMainCategory(std::string book){
    const auto& result = getBookInfo(book);
    std::string mainCategory = "";

    if(result.contains("mainCategory")){
        mainCategory = result.at("mainCategory");
    }
    return mainCategory;
}

float getRating(std::string book){
    const auto& result = getBookInfo(book);
    float rating = 0;

    if(result.contains("avarageRating")){
        rating = result.at("avarageRating");
    } else{
        return 0;
    }
    return rating;
}

float getPrice(std::string book){
    const auto& result = getBookInfo(book);
    float price = 0;

    if(result.contains("saleInfo") && result["saleInfo"].contains("listPrice") 
    && result["saleInfo"]["listPrice"].contains("amount")){
        price = result.at("saleInfo").at("listPrice").at("amount");
    } else{
        return 0;
    }
    return price;
}

int getPages(std::string book){
    const auto& result = getBookInfo(book); 
    int pages = 0;

    if(result.contains("pageCount")){
        pages = result.at("pageCount");
    } else{
        return 0;
    }
    return pages;
}