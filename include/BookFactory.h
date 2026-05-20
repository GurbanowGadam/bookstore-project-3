#pragma once

#include "Book.h"

#include <memory>
#include <string>
#include <vector>

class BookFactory {
public:
    static std::shared_ptr<Book> createBookFromLine(const std::string& line);
    static std::vector<std::shared_ptr<Book>> loadBooksFromFile(const std::string& filePath);
};
