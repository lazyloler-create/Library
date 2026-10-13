#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

json getBookInfo(std::string& book);
std::string getTitle(std::string& book);
std::string getAuthors(std::string book);
std::string getPublishedDate(std::string book);
std::string getISBN_10(std::string book);
std::string getISBN_13(std::string book);
std::string getMainCategory(std::string book);
float getRating(std::string book);
float getPrice(std::string book);
int getPages(std::string book);