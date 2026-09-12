#include <memory>
#include <map>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <nlohmann/json.hpp>
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

std::string getDate(){
    auto date = localDate();
    return date; 
}

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
std::unique_ptr<TreeNode> findTree(std::vector<std::unique_ptr<TreeNode>>& forest, std::unique_ptr<TreeNode>& target){
    auto const tar = std::get<std::string>(target->book); // gets value of the target in string
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
std::unique_ptr<TreeNode> findNode(std::unique_ptr<TreeNode>& tree, NodeData target){
    if(!tree || std::get<std::map<Book, int>>(target) == std::get<std::map<Book, int>>(tree->book)){ //base case, checks if tree is null and compares target and tree value
        auto newNode = std::move(tree);
        return newNode;
    }

    if(std::get<std::map<Book, int>>(target) < std::get<std::map<Book, int>>(tree->book)) //standard BST comparison
        return findNode(tree->left, target);

    return findNode(tree->right, target);
}

void cacheRentedBook(json& j, std::vector<std::unique_ptr<TreeNode>>& forest,NodeData book){
    if(j.is_null()) j = nlohmann::json::object();

    auto date = localDate(); 
}

void rentBook(std::unique_ptr<TreeNode>& node, NodeData& bookVal){

}