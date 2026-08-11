#include <iostream>
#include <map>
#include <string>
#include <cctype>
#include <vector>
#include <variant>
#include "classes/book_class.hpp"

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
        std::cin>>categorie;
        categories.push_back(categorie);
    }
}

//checks if categories vector is empty and prompts the user to create if empty
void checkCategories(std::vector<std::string> categories){
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



int main(){
    std::vector<std::string> categories;

   checkCategories(categories);

   std::cout<<"Enter book title, author, edition and book ID for each book: " << std::endl;
   
}