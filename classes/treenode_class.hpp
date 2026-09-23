#pragma once 

#include <string>
#include <memory>
#include <variant>
#include "./book_class.hpp"
#include <vector>

using NodeData = std::variant<
    std::string, 
    Book
>;
//
class TreeNode{
    public: 
        NodeData book;   
        std::unique_ptr<TreeNode> left{nullptr};
        std::unique_ptr<TreeNode> right{nullptr};
        TreeNode(NodeData val);
        ~TreeNode();
        
    static std::unique_ptr<TreeNode> createNode(NodeData node);
    static void insert(std::unique_ptr<TreeNode>& node, NodeData val);
    static std::unique_ptr<TreeNode> newTree(std::unique_ptr<TreeNode>& tree, std::string& categorie);
};

std::unique_ptr<TreeNode> findTree(std::vector<std::unique_ptr<TreeNode>>& forest, NodeData& target);