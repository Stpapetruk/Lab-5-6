#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include <vector>

class Book {
private:
    std::string title;
    std::string author;
    int year;
    std::string isbn;
    bool isAvailable;
    std::string borrowedBy;

    bool isValidYear(int year) const;
    int getCurrentYear() const;

public:
    Book(const std::string& title, const std::string& author, 
         int year, const std::string& isbn);
    
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    int getYear() const { return year; }
    std::string getIsbn() const { return isbn; }
    bool getIsAvailable() const { return isAvailable; }
    std::string getBorrowedBy() const { return borrowedBy; }
    
    void borrowBook(const std::string& userName);
    void returnBook();
    void displayInfo() const;
    
    std::string toFileString() const;
    static Book fromFileString(const std::vector<std::string>& lines);
};

#endif
