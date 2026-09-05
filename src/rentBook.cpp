#include <memory>
#include "../classes/treenode_class.hpp"
#include <nlohmann/json.hpp>
#include <ctime>


using json = nlohmann::json;

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

        root->book = successor->book;
        root->right = deleteNode(root->right, root->book);
    }
    return std::move(root);
}

void cacheRentedBook(std::unique_ptr<TreeNode>& tree){
    std::time_t now;
    struct tm* date; 
    std::time(&now);
    date = std::localtime(&now);
    int day = date->tm_mday;
    int month = date->tm_mon + 1;
    int year = date->tm_year + 1900;

    json j = json::object();
}

void rentBook(std::unique_ptr<TreeNode>& node, NodeData& bookVal){

}