#include <iostream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "../classes/book_class.hpp"
#include "../function_headers/jsonFile.hpp"

using json = nlohmann::json;

void cacheBookAttribute(json& jsonArr, Book& b, int ID){
    if (jsonArr.is_null()) {
        jsonArr = nlohmann::json::array();
    }

    json bookJson = nlohmann::json::object();
    bookJson["Title"] = b.getTitle();
    bookJson["Author"] = b.getAuthor();
    bookJson["Edition"] = b.getEdition();
    bookJson["ISBN"] = ID;

    jsonArr.push_back(bookJson);
}

void cacheCategories(std::string& cat, json& jsonArr){
    if (jsonArr.is_null()) {
        jsonArr = nlohmann::json::object();
    }
    if (!jsonArr.contains("Categories") || !jsonArr["Categories"].is_array()) {
        jsonArr["Categories"] = nlohmann::json::array();
    }

    jsonArr["Categories"].push_back(cat);
}

void createCategories(std::vector<std::string>& categories){
    std::cout<<"How many categories do you want to create:" <<std::endl;
    int count = 0;
    std::cin>>count;
    if(count == 0){
        std::cout<<"Can't create 0 categories!" << std::endl;
        return;
    }

    json jsonArr = nlohmann::json::object();
    std::cout<<"Enter categorie/s: " << std::endl;
    for(int i = 0; i < count; i++){
        std::string categorie;
        std::cout<<"Categorie " << i + 1 << std::endl;
       
        if(i == 0) {
            std::cin.ignore(1000, '\n');  
        }

        std::getline(std::cin, categorie);
        categories.push_back(categorie);
        cacheCategories(categorie, jsonArr);
    }
    cacheToFile(jsonArr, "categories_cache");
}

//checks if categories vector is empty and prompts the user to create if empty
void checkCategories(std::vector<std::string>& categories){
    if(!categories.empty()){
        std::cout<<"You alrleady have categories present, create more? \n(y/n)" << std::endl;
        char ch;
        std::cin>>ch;
        switch(tolower(ch)){
            case 'y':
                createCategories(categories);
                break;
            case 'n':
                std::cout<<"No categories, ending program!" <<std::endl;
                exit(1);
                break;
            default:
                std::cout<<"Invalid choice!" << std::endl;
                exit(1);
                break;
        }
    }
 if(categories.empty()){
        std::cout<<"You have no categories, create some? \n (y/n)" << std::endl;
        char ch;
        std::cin>>ch;
        switch(tolower(ch)){
            case 'y':
                createCategories(categories);
                break;
            case 'n':
                std::cout<<"No categories created, ending program!" <<std::endl;
                exit(1);
                break;
            default:
                std::cout<<"Invalid choice!" << std::endl;
                exit(1);
                break;
        }
    }
}