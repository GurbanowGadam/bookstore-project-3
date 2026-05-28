#include "BookFactory.h"
#include "Bookstore.h"
#include "BookstoreException.h"
#include "DiscountStrategy.h"

#include <iostream>

int main() {
    try {
        std::cout << "Bookstore Project 3 Demo\n";

        Bookstore store("Bookstore");

        // Books are created by the factory from the CSV file.
        auto books = BookFactory::loadBooksFromFile("data/books.csv");

        for (const auto& book : books) {
            store.addBook(book);
        }

        std::cout << "\n=== Loaded books ===\n";
        store.showBooks();

        std::cout << "\n=== Printed book shipping information ===\n";
        store.showPrintedBookShippingInfo();

        NoDiscountStrategy noDiscount;
        PercentageDiscountStrategy studentDiscount(10);
        FixedDiscountStrategy couponDiscount(20);

        std::cout << "\n=== Strategy Pattern Demo ===\n";
        // Different discount strategies are used here.
        Order order1 = store.sellBook(1, 1, noDiscount);
        Order order2 = store.sellBook(2, 1, studentDiscount);
        Order order3 = store.sellBook(3, 1, couponDiscount);

        std::cout << order1 << "\n\n";
        std::cout << order2 << "\n\n";
        std::cout << order3 << '\n';

        std::cout << "\n=== Stored orders ===\n";
        store.showOrders();

        std::cout << "\n=== Template Demo ===\n";
        std::cout << "\nTemplate class Repository<T> is used for books and orders.\n";
        std::cout << "Template function printCollection<T> is used for books and orders.\n";

        std::cout << "\n=== Books after selling ===\n";
        store.showBooks();

        std::cout << "\n=== Deep Copy Demo ===\n";
        // This copy uses clone() internally for books.
        Bookstore copyStore = store;
        copyStore.sellBook(4, 1, noDiscount);

        std::cout << "\nOriginal store after selling from the copy:\n";
        store.showBooks();

        std::cout << "\nCopied store after one extra sale:\n";
        copyStore.showBooks();

        std::cout << "\n=== Exception Demo ===\n";
        try {
            store.sellBook(1, 100, noDiscount);
        } catch (const BookstoreException& exception) {
            std::cout << "Too much quantity: " << exception.what() << '\n';
        }

        try {
            store.findBookById(999);
        } catch (const BookstoreException& exception) {
            std::cout << "Missing book: " << exception.what() << '\n';
        }

        std::cout << "\nDemo finished.\n";
    } catch (const BookstoreException& exception) {
        std::cout << "Bookstore error: " << exception.what() << '\n';
    } catch (const std::exception& exception) {
        std::cout << "Unexpected error: " << exception.what() << '\n';
    }

    return 0;
}
