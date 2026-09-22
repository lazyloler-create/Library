#include <memory>
#include "../classes/treenode_class.hpp"

TreeNode::TreeNode(NodeData data) : book(std::move(data)), left(nullptr), right(nullptr) {}

std::unique_ptr<TreeNode> TreeNode::createNode(NodeData node) {
    return std::make_unique<TreeNode>(std::move(node));
}

void insert(std::unique_ptr<TreeNode>& node, NodeData val){
    if(node == nullptr){
        node = TreeNode::createNode(val);
        return;
    }
    if(val < node->book)
        insert(node->left, val);
    else
        insert(node->right, val);
}

TreeNode::~TreeNode() = default;