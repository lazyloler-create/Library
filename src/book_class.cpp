#include <iostream>
#include <string.h>
#include "classes/book_class.hpp"

std::string getTitle() const {
    return title;
}
std::string getAuthor() const {
    return author;
}
std::string getEdition() const {
    return edition;
}

void setTitle(std::string title){
    this->title = title;
}
void setAuthor(std::string author){
    this->author = author;
}
void setEdition(std::string edition){
    this->edition = edition;
}