#pragma once

#include <string>

class Book{
private:  
    std::string title;
    std::string author;
    std::string date;
    std::string ISBN;
public:
    std::string getTitle() const {
        return title;
    };
    std::string getAuthor() const {
        return author;
    };
    std::string getDate() const {
        return date;
    };
    std::string getISBN() const {
        return ISBN;
    }

    void setTitle(std::string& title){
        this->title = title;
    };
    void setAuthor(std::string& author){
        this->author = author;
    };
    void setDate(std::string& date){
        this->date = date;
    };
    void setISBN(std::string& ISBN){
        this->ISBN = ISBN;
    }

    bool operator<(const Book& other) const {
        return std::stoi(ISBN) > std::stoi(other.ISBN);
    }

    bool operator>(const Book& other) const {
        return std::stoi(ISBN) > std::stoi(other.ISBN);
    }

    bool operator==(const Book& other) const {
        return title == other.title && author == other.author && date == other.date && std::stoi(other.ISBN) == std::stoi(ISBN);
    }
};