#pragma once 

#include <string>
#include <map>
#include <memory>
#include <variant>
#include "./book_class.hpp"

using NodeData = std::variant<
    std::string, 
    std::map<Book, int>
>;

class TreeNode{
    public: 
        NodeData book;   
        std::unique_ptr<TreeNode> left{nullptr};
        std::unique_ptr<TreeNode> right{nullptr};
        TreeNode(NodeData val);
        ~TreeNode();
        
    static std::unique_ptr<TreeNode> createNode(NodeData node);
};