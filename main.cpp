#include <iostream>
#include <map>
#include <string>
#include <cctype>
#include <vector>
#include <variant>
#include "classes/book_class.hpp"
#include "classes/treenode_class.hpp"

void createCategories(std::vector<std::string>& categories){
    std::cout<<"How many categories do you want to create:" <<std::endl;
    int count = 0;
    std::cin>>count;
    if(count == 0){
        std::cout<<"Can't create 0 categories!" << std::endl;
        return;
    }

    std::cout<<"Enter categorie/s: " << std::endl;
    for(int i = 0; i < count; i++){
        std::string categorie;
        std::cout<<"Categorie " << i + 1 << std::endl;
       
        if(i == 0) {
            std::cin.ignore(1000, '\n');  
        }

        std::getline(std::cin, categorie);
        categories.push_back(categorie);
    }
}

//checks if categories vector is empty and prompts the user to create if empty
void checkCategories(std::vector<std::string>& categories){
 if(categories.empty()){
        std::cout<<"You have no categories, create some? \n (y/n)" << std::endl;
        char ch;
        std::cin>>ch;
        switch(tolower(ch)){
            case 'y':
                createCategories(categories);
                break;
            case 'n':
                std::cout<<"No categories, ending program!" <<std::endl;
                exit(1);
                break;
            default:
                std::cout<<"Invalid choice!" << std::endl;
                exit(1);
                break;
        }
    }
}

//Simple binary tree insertion - adds to any empty slot, fills left before right
void insertRec(TreeNode* node, NodeData value){
    if(node == nullptr) {
        return; 
    }

    if(!node->left) {
        std::unique_ptr<TreeNode> newNode = TreeNode::createNode(value);
        node->left = std::move(newNode); 
    }

    else if(!node->right) {  
        std::unique_ptr<TreeNode> newNode = TreeNode::createNode(value);
        node->right = std::move(newNode);
    }

    if(node->left) insertRec(node->left.get(), value);  
    if(node->right) insertRec(node->right.get(), value); 
}

int main(){
    std::vector<std::string> categories;
    checkCategories(categories);

    // Input books for each category
   std::cout<<"Enter book title, author, edition and book ID for each book: " << std::endl;

    std::vector<std::unique_ptr<TreeNode>> forest;
    
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
            bookMap[book] = i; 

            NodeData bookNode(std::move(bookMap));

            insertRec(forest[i].get(), bookNode);

            std::cout<<"Do you want to add another book? (y/n): ";
            char ch;
            std::cin>>ch;

            if(tolower(ch) != 'y'){
                keepInserting = false;
            }
        }
    }
    
    std::cout<<"Total categories: " << categories.size() << std::endl;
    for(int i = 0; i < categories.size(); i++){
        std::cout<<"Category "<<i+1<<": "<<categories[i]<<std::endl;
    }

    return 0;
}