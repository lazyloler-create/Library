#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <chrono>
#include <ctime>
#include "../classes/book_class.hpp"
#include "../classes/treenode_class.hpp"
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

class BookForRent{
    private:
        Book book;
    public:

    std::string getDate(){
        auto date = localDate();
        return date; 
    }
}; 

std::unique_ptr<TreeNode> deleteNode(std::unique_ptr<TreeNode>& root, NodeData target) {
    if (!root) {
        return nullptr;
    }

    if (target < root->book) {
        root->left = deleteNode(root->left, std::move(target)); 
    } else if (target > root->book) {
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


void cacheRentedBook(std::unique_ptr<TreeNode>& node){
    

    json j = json::object();
     
}

void rentBook(std::unique_ptr<TreeNode>& node, NodeData& bookVal){

}