#ifndef BOOK_CLASS_HPP
#define BOOK_CLASS_HPP

class Book{
private:  
    std::string title;
    std::string author;
    std::string edition;

public:
    std::string getTitle();
    std::string getAuthor();
    std::string getEdition();

    void setTitle(std::string title);
    void setAuthor(std::string author);
    void setEdition(std::string edition);
};

#endif