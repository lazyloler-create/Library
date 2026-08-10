#include <iostream>
#include <map>
#include <variant>
#include <tuple>
#include <stdexcept>
#include "classes/book_class.hpp"
#include "classes/treenode_class.hpp"

TreeNode::TreeNode(NodeData data, int id) : book(std::move(data)), bookID(id), 
                                            left(nullptr), right(nullptr) {}

bool isString() const {
    return std::holds_alternative<std::string>(data);
}

bool isMap() const {
    return std::holds_alternative<std::map<Book, int>>(data);
}

static std::unique_ptr<TreeNode> TreeNode::createNode(NodeData val){
    return std::make_unique<TreeNode>(std::move(val));
}

TreeNode::~TreeNode() = default;