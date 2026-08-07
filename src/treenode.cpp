#include <iostream>
#include <map>
#include "classes/book_class.hpp"
#include "classes/treenode.hpp"

TreeNode::TreeNode(Book data, int id) : book(data), bookID(id) {}

TreeNode* TreeNode::createNode(std::string t, int ID){
    TreeNode* newNode;
    newNode->book.insert({t, ID});
    newNode->left = newNode->right = nullptr;
    return newNode;
}

TreeNode::~TreeNode(){
    delete left;
    delete right;
}