#pragma once

#include <string>
#include <vector>

class Book{
private:  
    std::string title;
    std::string author;
    std::string ISBN;
    std::string publishedDate;
    
    float rating;
    float priceUSD;
    int pages;
public:
    std::string getTitle() const {
        return title;
    };
    std::string getAuthor() const {
        return author;
    };
    std::string getISBN() const {
        return ISBN;
    };
    float getRating() const {
        return rating;
    };
    std::string getPublishedDate() const {
        return publishedDate;
    };
    int getPrice() const{
        return priceUSD;
    }

    void setTitle(std::string& title){
        this->title = title;
    };
    void setAuthor(std::string& author){
        this->author = author;
    };
    void setISBN(std::string& ISBN){
        this->ISBN = ISBN;
    };
    void setRating(float rating){
        this->rating = rating;
    };
    void setPublishedDate(std::string date){
        publishedDate = date;
    };
    void setPrice(int priceUSD){
        this->priceUSD = priceUSD;
    };

    bool operator<(const Book& other) const {
        return ISBN > other.ISBN;
    }

    bool operator>(const Book& other) const {
        return ISBN > other.ISBN;
    }

    bool operator==(const Book& other) const {
        return title == other.title 
        && author == other.author 
        && other.ISBN == ISBN
        && other.publishedDate == publishedDate;
    } 

    Book(std::string& t, std::string& a, std::string& I, 
        float r, std::string& PD, int p, int price) : 
    title(t), author(a), ISBN(I), rating(r), 
    publishedDate(PD), pages(p), priceUSD(price) {}
};