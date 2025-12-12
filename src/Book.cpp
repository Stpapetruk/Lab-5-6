#include "Book.h"
#include <chrono>
#include <ctime>
#include <stdexcept>

Book::Book(const std::string& title, const std::string& author, 
           int year, const std::string& isbn)
    : title(title), author(author), year(year), isbn(isbn), 
      isAvailable(true), borrowedBy("") {
    
    if (!isValidYear(year)) {
        throw std::invalid_argument("Некорректный год. Год должен быть от 1450 до текущего.");
    }
    
    if (isbn.empty()) {
        throw std::invalid_argument("ISBN не может быть пустым.");
    }
}

bool Book::isValidYear(int year) const {
    int currentYear = getCurrentYear();
    return year >= 1450 && year <= currentYear;
}

int Book::getCurrentYear() const {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&time);
    return localTime->tm_year + 1900;
}

void Book::borrowBook(const std::string& userName) {
    if (!isAvailable) {
        throw std::runtime_error("Книга уже выдана.");
    }
    if (userName.empty()) {
        throw std::invalid_argument("Имя пользователя не может быть пустым.");
    }
    
    isAvailable = false;
    borrowedBy = userName;
}

void Book::returnBook() {
    if (isAvailable) {
        throw std::runtime_error("Книга не была выдана.");
    }
    
    isAvailable = true;
    borrowedBy = "";
}

void Book::displayInfo() const {
    std::cout << "Название: " << title << std::endl;
    std::cout << "Автор: " << author << std::endl;
    std::cout << "Год издания: " << year << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    std::cout << "Статус: " << (isAvailable ? "Доступна" : "Выдана " + borrowedBy) << std::endl;
    std::cout << "-------------------" << std::endl;
}

std::string Book::toFileString() const {
    std::string result;
    result += "КНИГА\n";
    result += "Название: " + title + "\n";
    result += "Автор: " + author + "\n";
    result += "Год: " + std::to_string(year) + "\n";
    result += "ISBN: " + isbn + "\n";
    result += "Доступна: " + std::string(isAvailable ? "да" : "нет") + "\n";
    result += "Выдана: " + borrowedBy + "\n";
    return result;
}

Book Book::fromFileString(const std::vector<std::string>& lines) {
    std::string title, author, isbn, borrowedBy;
    int year;
    bool available = true;
    
    for (const auto& line : lines) {
        if (line.find("Название: ") == 0) {
            title = line.substr(10);
        } else if (line.find("Автор: ") == 0) {
            author = line.substr(7);
        } else if (line.find("Год: ") == 0) {
            year = std::stoi(line.substr(5));
        } else if (line.find("ISBN: ") == 0) {
            isbn = line.substr(6);
        } else if (line.find("Доступна: ") == 0) {
            std::string avail = line.substr(10);
            available = (avail == "да");
        } else if (line.find("Выдана: ") == 0) {
            borrowedBy = line.substr(8);
        }
    }
    
    Book book(title, author, year, isbn);
    if (!available) {
        book.borrowBook(borrowedBy);
    }
    
    return book;
}
