#include <memory>
#include "../classes/treenode_class.hpp"

TreeNode::TreeNode(NodeData data) : book(std::move(data)), left(nullptr), right(nullptr) {}

std::unique_ptr<TreeNode> TreeNode::createNode(NodeData node) {
    return std::make_unique<TreeNode>(std::move(node));
}

TreeNode::~TreeNode() = default;