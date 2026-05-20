#include "BookFactory.h"

#include "AudioBook.h"
#include "BookstoreException.h"
#include "EBook.h"
#include "PrintedBook.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace {
std::string trim(const std::string& text) {
    const std::string spaces = " \t\r\n";
    const std::size_t start = text.find_first_not_of(spaces);

    if (start == std::string::npos) {
        return "";
    }

    const std::size_t end = text.find_last_not_of(spaces);
    return text.substr(start, end - start + 1);
}

std::vector<std::string> splitCsvLine(const std::string& line) {
    std::vector<std::string> fields;
    std::stringstream stream(line);
    std::string field;

    // We keep the CSV format simple for this project.
    while (std::getline(stream, field, ',')) {
        fields.push_back(trim(field));
    }

    return fields;
}

int toInt(const std::string& text, const std::string& fieldName) {
    try {
        std::size_t usedCharacters = 0;
        int value = std::stoi(text, &usedCharacters);

        if (usedCharacters != text.length()) {
            throw InvalidBookDataException("Invalid number for " + fieldName + ".");
        }

        return value;
    } catch (const std::invalid_argument&) {
        throw InvalidBookDataException("Invalid number for " + fieldName + ".");
    } catch (const std::out_of_range&) {
        throw InvalidBookDataException("Number is too large for " + fieldName + ".");
    }
}

double toDouble(const std::string& text, const std::string& fieldName) {
    try {
        std::size_t usedCharacters = 0;
        double value = std::stod(text, &usedCharacters);

        if (usedCharacters != text.length()) {
            throw InvalidBookDataException("Invalid number for " + fieldName + ".");
        }

        return value;
    } catch (const std::invalid_argument&) {
        throw InvalidBookDataException("Invalid number for " + fieldName + ".");
    } catch (const std::out_of_range&) {
        throw InvalidBookDataException("Number is too large for " + fieldName + ".");
    }
}
}

std::shared_ptr<Book> BookFactory::createBookFromLine(const std::string& line) {
    std::vector<std::string> fields = splitCsvLine(line);

    if (fields.size() < 7) {
        throw InvalidBookDataException("Book line does not have enough fields.");
    }

    const std::string& type = fields[0];
    const std::string& title = fields[1];
    const std::string& author = fields[2];
    double basePrice = toDouble(fields[3], "base price");
    int stock = toInt(fields[4], "stock");

    // Factory method: create the correct book type from one line.
    if (type == "printed") {
        int pages = toInt(fields[5], "pages");
        double weight = toDouble(fields[6], "weight");
        return std::make_shared<PrintedBook>(title, author, basePrice, stock, pages, weight);
    }

    if (type == "ebook") {
        const std::string& fileFormat = fields[5];
        double fileSizeMB = toDouble(fields[6], "file size");
        return std::make_shared<EBook>(title, author, basePrice, stock, fileFormat, fileSizeMB);
    }

    if (type == "audio") {
        int durationMinutes = toInt(fields[5], "duration");
        const std::string& narrator = fields[6];
        return std::make_shared<AudioBook>(title, author, basePrice, stock, durationMinutes, narrator);
    }

    throw InvalidBookDataException("Unknown book type: " + type + ".");
}

std::vector<std::shared_ptr<Book>> BookFactory::loadBooksFromFile(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file) {
        throw InvalidBookDataException("Could not open file: " + filePath + ".");
    }

    std::vector<std::shared_ptr<Book>> books;
    std::string line;

    // This function loads all books from a file.
    while (std::getline(file, line)) {
        line = trim(line);

        if (line.empty() || line == "type,title,author,basePrice,stock,extra1,extra2") {
            continue;
        }

        books.push_back(createBookFromLine(line));
    }

    return books;
}
