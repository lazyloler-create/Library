#include <iostream>
#include <map>
#include <string>
#include <cctype>
#include <vector>
#include "classes/book_class.hpp"

void createCategories(std::vector<std::string>& categories){
    std::cout<<"How many categories do you want to create:" <<std::endl;
    int cout = 0;
    cin>>cout;
    if(cout == 0){
        std::cout<<"Can't create 0 categories!" << std::endl;
        return;
    }
    std::cout<<"Enter categorie/s: " << std::endl;
    for(int i = 0; i < cout; i++){
        std::string categorie;
        cout<<"Categorie " << i + 1 << std::endl;
        cin>>categorie;
        categories.push_back(categorie);
    }
}

//checks if categories vector is empty and prompts the user to create if empty
void checkCategories(std::vector<std::string> categories){
 if(categories.empty()){
        std::cout<<"You have no categories, create some? \n (y/n)" << std::endl;
        char ch;
        cin>>ch;
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

   Book* book = new Book();
   std::cout<<"Enter book title, author, edition and book ID: " << std::endl;
   
}