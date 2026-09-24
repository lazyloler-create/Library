#pragma once 

#include <unordered_map>
#include <memory>
#include "./book_class.hpp"

class TreeNode{
    public: 
        Book book;   
        std::unique_ptr<TreeNode> left{nullptr};
        std::unique_ptr<TreeNode> right{nullptr};
        TreeNode(Book val);
        ~TreeNode();
        
    static std::unique_ptr<TreeNode> createNode(Book node);
    
};

using CategoryTrees = std::unordered_map<std::string, std::unique_ptr<TreeNode>>;

std::unique_ptr<TreeNode> deleteNode(std::unique_ptr<TreeNode>& root, Book target);
void insertBook(CategoryTrees& trees, std::string& book, Book b);
std::unique_ptr<TreeNode> findNode(std::unique_ptr<TreeNode>& tree, Book target);