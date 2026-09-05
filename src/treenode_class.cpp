#include <map>
#include <variant>
#include <memory>
#include <string>
#include "../classes/book_class.hpp"
#include "../classes/treenode_class.hpp"

TreeNode::TreeNode(NodeData data) : book(std::move(data)), left(nullptr), right(nullptr) {}

bool TreeNode::isString() {
    return std::holds_alternative<std::string>(book);
}

bool TreeNode::isMap() {
    return std::holds_alternative<std::map<Book, int>>(book);
}

std::unique_ptr<TreeNode> TreeNode::createNode(NodeData node) {
    return std::make_unique<TreeNode>(std::move(node));
}

TreeNode::~TreeNode() = default;