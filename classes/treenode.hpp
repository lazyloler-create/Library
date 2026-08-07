#ifndef TREENODE_CLASS_HPP
#define TREENODE_CLASS_HPP

#include "classes/book_class.hpp"

class TreeNode{
    private:
        TreeNode* left{nullptr};
        TreeNode* right{nullptr};
        std::map<Book,int bookID> book;
        
    public:
    TreeNode(Book data, int id);

        TreeNode* insert(std::map<Book b, int ID>);

    ~TreeNode();
};

#endif