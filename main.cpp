#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cctype>
#include <vector>
#include <variant>
#include <nlohmann/json.hpp>

#include "classes/book_class.hpp"
#include "classes/treenode_class.hpp"
#include "function_headers/categories_functions.hpp"
#include "./function_headers/jsonFile.hpp"

using json = nlohmann::json;

void BSTinsert(std::unique_ptr<TreeNode>& node, NodeData val){
    if(node == nullptr){
        node = TreeNode::createNode(val);
        return;
    }
    if(val < node->book)
        BSTinsert(node->left, val);
    else
        BSTinsert(node->right, val);
}

int main(){
    std::vector<std::string> categories;
    json cachedCategories;
    try{
        std::ifstream categoriesCacheFile("categories_cache.json");
        cachedCategories = json::parse(categoriesCacheFile);
    }catch(...){

    }
    checkCategories(categories, cachedCategories);
    
    // Input books for each category
   std::cout<<"Enter book title, author, edition and book ID for each book: " << std::endl;

    std::vector<std::unique_ptr<TreeNode>> forest;
    json jsonBookArr;
    for(int i = 0; i < categories.size(); i++){
        NodeData categoryNode(categories[i]);

        // Create category node with unique_ptr ownership
        std::unique_ptr<TreeNode> categoryNodePtr = TreeNode::createNode(categoryNode);
        forest.push_back(std::move(categoryNodePtr));

        Book book;
        bool keepInserting = true;

        while(keepInserting){
            std::cout<<"Enter book title: ";
            std::string title;
            std::getline(std::cin, title);

            std::cout<<"Enter author: ";
            std::string author;
            std::getline(std::cin, author);

            std::cout<<"Enter edition: ";
            std::string edition;
            
            std::getline(std::cin, edition);
            
            book.setTitle(title);
            book.setAuthor(author); 
            book.setEdition(edition);

            // Store the book in a map structure

            std::map<Book, int> bookMap;
            bookMap[book] = i + 1000000000000; 
            cacheBookAttribute(jsonBookArr, book, bookMap[book]);
            NodeData bookNode(std::move(bookMap));

            BSTinsert(forest[i], bookNode);

            std::cout<<"Do you want to add another book? (y/n): ";
            char ch;
            std::cin>>ch;

            if(tolower(ch) != 'y'){
                keepInserting = false;
            }
        }
    }
    cacheToFile(jsonBookArr, "books_cache");
    
    std::cout<<"Total categories: " << categories.size() << std::endl;
    for(int i = 0; i < categories.size(); i++){
        std::cout<<"Category "<<i+1<<": "<<categories[i]<<std::endl;
    }

    return 0;
}