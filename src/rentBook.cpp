#include <memory>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <nlohmann/json.hpp>

#include "../classes/book_class.hpp"
#include "../classes/treenode_class.hpp"
#include "../function_headers/jsonFile.hpp"

using json = nlohmann::json;

//gets local date in a string format d/m/y
std::string localDate(){
    auto now = std::chrono::system_clock::now();
    auto t  = std::chrono::system_clock::to_time_t(now);
    std::tm* tm          = std::localtime(&t);

    std::string date;
    int d  = tm->tm_mday;
    date = std::to_string(d) + '/';
    int m = tm->tm_mon + 1;
    date = std::to_string(m) + '/';  
    int y  = tm->tm_year + 1900;
    date = std::to_string(y);
    
    return date;
}

std::string getReturnDate(){
    auto now = std::chrono::system_clock::now();
    auto t  = std::chrono::system_clock::to_time_t(now);
    std::tm* tm          = std::localtime(&t);

    std::string date;
    int d  = tm->tm_mday;
    date = std::to_string(d) + '/';
    int m = tm->tm_mon + 2;
    date = std::to_string(m) + '/';  
    int y  = tm->tm_year + 1900;
    date = std::to_string(y);

    return date;
}

//gets title, author, date and ISBN of a book that is declared with NodeData
std::vector<std::string> getBookAttributes(const Book& b){
    std::vector<std::string> result;
    for(int i = 0; i < 4; i++){
            result.push_back(b.getTitle());
            result.push_back(b.getAuthor());
            result.push_back(b.getDate());
            result.push_back(b.getISBN());
        }
    return result;
}

//caches the book in a json file before renting 
void cacheRentedBook(json& j, Book book){
    if(j.is_null()) j = nlohmann::json::object();

    if(!j.contains("Rented books") || !j.is_array())
        j["Rented book"] = nlohmann::json::array();

    auto const bookAtt = getBookAttributes(book);

    j["Rented books: "] = { 
        {bookAtt[0], bookAtt[1], bookAtt[2], bookAtt[3], localDate(), getReturnDate()},
    };    
}

//function for renting a book,
//finds the needed tree by categorie of the book, finds the book in the tree, caches it and deletes the node in the tree
void rentBook(std::unique_ptr<TreeNode>& tree, Book& bookVal){
    json j;

    auto book = findNode(tree, bookVal);
    cacheRentedBook(j, book->book);
    cacheToFile(j, "Rented books");
    deleteNode(tree, book->book);
} 