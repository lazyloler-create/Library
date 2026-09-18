#include <memory>
#include <map>
#include <variant>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <nlohmann/json.hpp>
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

//gets todays date in local time 
std::string getDate(){
    auto date = localDate();
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

//deletes a book in a tree
std::unique_ptr<TreeNode> deleteNode(std::unique_ptr<TreeNode>& root, NodeData target) {
    if (!root) {
        return nullptr;
    }

    if (std::get<std::map<Book, int>>(target) < std::get<std::map<Book, int>>(root->book)) {
        root->left = deleteNode(root->left, std::move(target)); 
    } else if (std::get<std::map<Book, int>>(target) > std::get<std::map<Book, int>>(root->book)) {
        root->right = deleteNode(root->right, std::move(target));
    } else {
        if (!root->left) {
            return std::move(root->right);
        }
        if (!root->right) {
            return std::move(root->left);
        }

        TreeNode* successor = root->right.get();
        while (successor->left) {
            successor = successor->left.get();
        }

        root->book  = successor->book;
        root->right = deleteNode(root->right, root->book);
    }
    return std::move(root);
}

//finds a tree based on its categorie (categorie is the root of a tree)
std::unique_ptr<TreeNode> findTree(std::vector<std::unique_ptr<TreeNode>>& forest, NodeData& target){
    auto const tar = std::get<std::string>(target); // gets value of the target in string
    for(auto it = 0; it < forest.size(); it++){
        std::unique_ptr<TreeNode> temp = std::move(forest[it]);
        auto tempVal = std::get<std::string>(temp->book); //gets the value of the current tree root
        if(tempVal == tar){
            return std::move(temp); //returns tree
        }
    }
    return nullptr;
}

//finds a node (book) and returns the node
TreeNode* findNode(std::unique_ptr<TreeNode>& tree, NodeData target) {
    if (!tree) return nullptr;

    if (std::get<std::map<Book, int>>(target) == std::get<std::map<Book, int>>(tree->book))
        return tree.get(); //returns the found node

    if (std::get<std::map<Book, int>>(target) < std::get<std::map<Book, int>>(tree->book))
        return findNode(tree->left, target);

    return findNode(tree->right, target);
}   

//gets title, author and edition of a book that is declared with NodeData
std::vector<std::string> getBookAttributes(const NodeData& book){
    std::vector<std::string> result;
    if (const auto* books = std::get_if<std::map<Book, int>>(&book)) {
        for (const auto& [book, isbn] : *books) {
            result.push_back(book.getTitle());
            result.push_back(book.getAuthor());
            result.push_back(book.getEdition());
        }
    }
    return result;
}

//gets isbn of a book that is declared with NodeData
int getIsbn(const NodeData& book){
    int ISBN = 0;
    if (const auto* books = std::get_if<std::map<Book, int>>(&book)) {
        for (const auto& [book, isbn] : *books) {
            ISBN = isbn;
        }
    }
    return ISBN;
}

//caches the book in a json file before renting 
void cacheRentedBook(json& j, std::unique_ptr<TreeNode>& tree, NodeData book){
    if(j.is_null()) j = nlohmann::json::object();

    if(!j.contains("Rented books") || !j.is_array())
        j["Rented book"] = nlohmann::json::array();

    auto date = localDate(); 
    auto bookCategorie = std::get<std::string>(book);

    auto targetBook = findNode(tree, book);
    auto data = targetBook->book;
    
    auto bookAtt = getBookAttributes(book);
    auto ISBN = getIsbn(book);

    j["Rented books: "] = {
        {bookAtt[0], bookAtt[1], bookAtt[2], ISBN, date},
    };    
}

//function for renting a book,
//finds the needed tree by categorie of the book, finds the book in the tree, caches it and deletes the node in the tree
void rentBook(std::vector<std::unique_ptr<TreeNode>>& forest, std::unique_ptr<TreeNode>& tree, NodeData& bookVal){
    json j;
    auto foundTree = findTree(forest, bookVal);
    auto foundBook = findNode(foundTree, bookVal);
    cacheRentedBook(j, foundTree, foundBook->book);
    cacheToFile(j, "Rented books");
    deleteNode(foundTree, foundBook->book);
} 