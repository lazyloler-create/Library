#ifndef BOOK_CLASS_HPP
#define BOOK_CLASS_HPP

#include <string>
#include <algorithm>

class Book{
private:  
    std::string title;
    std::string author;
    std::string edition;

public:
    std::string getTitle() const {
        return title;
    };
    std::string getAuthor() const {
        return author;
    };
    std::string getEdition() const {
        return edition;
    };

    void setTitle(std::string& title){
        this->title = title;
    };
    void setAuthor(std::string& author){
        this->author = author;
    };
    void setEdition(std::string& edition){
        this->edition = edition;
    };

    // Comparison operators for std::map
    bool operator<(const Book& other) const {
        return title < other.title;
    }

    bool operator>(const Book& other) const {
        return title > other.title;
    }

    bool operator==(const Book& other) const {
        return title == other.title && author == other.author && edition == other.edition;
    }
};

#endif