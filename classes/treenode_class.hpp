#ifndef TREENODE_CLASS_HPP
#define TREENODE_CLASS_HPP

#include <iostream>
#include "classes/book_class.hpp"
#include <memory>
#include <variant>

using NodeData = std::variant<string, std::map<Book book, int bookID>>;

class TreeNode{
    private:    
        NodeData book;
        std::unique_ptr<TreeNode> left{nullptr};
        std::unique_ptr<TreeNode> right{nullptr};
        
    public:
    TreeNode(NodeData val, int id);
    ~TreeNode();

    bool isString();
    bool isMap();
    static std::unique_ptr<TreeNode> createNode(NodeData node, std::string cat);
};

#endif