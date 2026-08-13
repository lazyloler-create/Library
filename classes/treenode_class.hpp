#ifndef TREENODE_CLASS_HPP
#define TREENODE_CLASS_HPP

#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <variant>
#include "./book_class.hpp"

using NodeData = std::variant<
    std::string, 
    std::map<Book, int, std::less<Book>, std::allocator<std::pair<const Book, int>>>
>;

class TreeNode{
    private:    
        NodeData book;
        
    public:    
        std::unique_ptr<TreeNode> left{nullptr};
        std::unique_ptr<TreeNode> right{nullptr};
        
    public:
    TreeNode(NodeData val);
    ~TreeNode();

    bool isString();
    bool isMap();
    static std::unique_ptr<TreeNode> createNode(NodeData node);
    const std::unique_ptr<TreeNode>& getLeft() const { return left; }
    const std::unique_ptr<TreeNode>& getRight() const { return right; }
};

#endif