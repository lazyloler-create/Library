#include <memory>
#include <vector>
#include "../classes/treenode_class.hpp"

TreeNode::TreeNode(NodeData data) : book(std::move(data)), left(nullptr), right(nullptr) {}

std::unique_ptr<TreeNode> TreeNode::createNode(NodeData node) {
    return std::make_unique<TreeNode>(std::move(node));
}

std::unique_ptr<TreeNode> findTree(std::vector<std::unique_ptr<TreeNode>>& forest, NodeData& target){
    if(forest.empty()) return nullptr;

    size_t n = forest.size();
    auto const tar = std::get<std::string>(target); // gets value of the target in string
    for(auto it = 0; it < n - 1; it++){
        auto current = std::get<std::string>(forest[it]->book); //gets the value of the current tree root
        auto next = std::get<std::string>(forest[it + 1]->book);
        if(current == tar){
            return std::move(forest[it]); //returns tree
        }
        if(it + 1 < n && forest[it + 1]){
            return std::move(forest[it + 1]);
        }
    }
    return nullptr;
}

std::unique_ptr<TreeNode> newTree(std::unique_ptr<TreeNode>& tree, NodeData& categorie, std::vector<std::unique_ptr<TreeNode>>& forest){
    auto find = findTree(forest, categorie);
    if(find){
       return nullptr; 
    }

    if(std::get<std::string>(tree->book) != std::get<std::string>(categorie)){
        std::unique_ptr<TreeNode> newTree = TreeNode::createNode(categorie);
        forest.push_back(newTree);
        return newTree;
    } 
    return nullptr;
}

void insert(std::unique_ptr<TreeNode>& node, NodeData val, std::vector<std::unique_ptr<TreeNode>>& forest){
    NodeData temp = std::get<std::string>(val); 
    if(node == nullptr){
        node = TreeNode::createNode(val);
        return;
    }

    auto newT = newTree(node, val, forest);
    if(!newT){
        node = std::move(newT);
    }

    if(val < node->book){
        insert(node->left, val);
    }
    else{
        insert(node->right, val);
    }
}

TreeNode::~TreeNode() = default;