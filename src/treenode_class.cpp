#include <memory>
#include "../classes/treenode_class.hpp"

TreeNode::TreeNode(Book data)
    : book(std::move(data)), left(nullptr), right(nullptr) {}

std::unique_ptr<TreeNode> TreeNode::createNode(Book book) {
    return std::make_unique<TreeNode>(std::move(book));
}

void insert(std::unique_ptr<TreeNode>& node, Book book) {
    if (!node) {
        node = TreeNode::createNode(std::move(book));
        return;
    }

    if (book.getISBN() == node->book.getISBN()) {
        return;
    }

    if (book.getISBN() < node->book.getISBN()) {
        insert(node->left, std::move(book));
    } else {
        insert(node->right, std::move(book));
    }
}

void insertBook(CategoryTrees& trees, const std::string& category, Book book){
    auto& root = trees[category];

    if (!root) {
        root = std::make_unique<TreeNode>(std::move(book));
        return;
    }

    insert(root, std::move(book));
}

//deletes a book in a tree
std::unique_ptr<TreeNode> deleteNode(std::unique_ptr<TreeNode>& root, Book target) {
    if (!root) {
        return nullptr;
    }

    if (target.getISBN() < root->book.getISBN()) {
        root->left = deleteNode(root->left, std::move(target)); 
    } else if (target.getISBN() > root->book.getISBN()) {
        root->right = deleteNode(root->right, std::move(target));
    } else {
        if (!root->left) {
            return std::move(root->right);
        }
        if (!root->right) {
            return std::move(root->left);
        }

        TreeNode* successor = root->right.get();
        while (successor->left) {
            successor = successor->left.get();
        }

        root->book  = successor->book;
        root->right = deleteNode(root->right, root->book);
    }
    return std::move(root);
}

std::unique_ptr<TreeNode> findNode(std::unique_ptr<TreeNode>& tree, Book target){
    if(!tree){
        return nullptr;
    }

    if(tree->book.getISBN() == target.getISBN()){
        return std::make_unique<TreeNode>(std::move(tree->book));
    }

     if (target.getISBN() < tree->book.getISBN()) {
        insert(tree->left, target);
    } else {
        insert(tree->right, target);
    }
    return nullptr;
}

TreeNode::~TreeNode() = default;