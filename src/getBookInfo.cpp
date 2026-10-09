#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <nlohmann/json.hpp>
#include <httplib.h>
#include <iostream>
#include <vector>

using json = nlohmann::json;

//searches Open Library for query and return the value of requested field, such as title
std::vector<std::string> getReqInf(const std::string& q, const std::string& param){
    httplib::SSLClient cli("openlibrary.org");
    auto path = "/search.json?q=" + q +"&fields=" + param;
    auto res = cli.Get(path);

    //no response means the request could not reach the server
    if (!res) {
        std::cerr << "Open Library request failed: " << httplib::to_string(res.error()) << std::endl;
        return {};
    }

    //http status 200 means the server handled the request successfully
    if (res->status != 200) {
        std::cerr << "Open Library returned HTTP status " << res->status << std::endl;
        return {};
    }

    try {
        //convert the response text into JSON
        const auto j = json::parse(res->body);

        //search results are stored in the docs list.
        const auto& docs = j.at("docs");
        if (!docs.is_array() || docs.empty()) {
            std::cerr << "Open Library search returned no documents for query: " << q << std::endl;
            return {};
        }

        //use the first matching book in the search results
        const auto& doc = docs.at(0);

        //looks for the requested field in that book
        const auto field = doc.find(param);
        if (field == doc.end()) {
            std::cerr << "Open Library result is missing field: " << param << std::endl;
            return {};
        }
        auto jVal = json::parse(field);
        return jVal;
    } catch (const json::exception& e) {
        //the response was not shaped like the JSON this code expected
        std::cerr << "Invalid Open Library JSON response: " << e.what() << std::endl;
        return {};
    }
}

//search for a book and return its title
std::string getTitle(const std::string& b){
    return getReqInf(b, "title");
}

//search for a book and return its author name.
std::string getAuthor(const std::string& b){
    return getReqInf(b, "author_name");
}

//search for a book and return its categories (subjects)
std::string getCategory(const std::string& b){
    return getReqInf(b, "subject");
}

//search for a book and return its edition information
std::string getEdition(const std::string& b){
    return getReqInf(b, "edition");
}