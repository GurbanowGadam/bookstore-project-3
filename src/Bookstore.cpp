#include "Bookstore.h"

#include "BookstoreException.h"
#include "DiscountStrategy.h"
#include "PrintedBook.h"
#include "TemplateUtils.h"

#include <iostream>
#include <memory>
#include <utility>

Bookstore::Bookstore(const std::string& name)
    : name(name) {
    if (name.empty()) {
        throw InvalidBookDataException("Bookstore name cannot be empty.");
    }
}

Bookstore::Bookstore(const Bookstore& other)
    : name(other.name) {
    for (const auto& book : other.books.getAll()) {
        // We still clone books when copying the bookstore.
        books.add(book->clone());
    }

    for (const auto& order : other.orders.getAll()) {
        orders.add(std::make_shared<Order>(*order));
    }
}

Bookstore& Bookstore::operator=(Bookstore other) {
    swap(*this, other);
    return *this;
}

void swap(Bookstore& first, Bookstore& second) noexcept {
    using std::swap;
    swap(first.name, second.name);
    swap(first.books, second.books);
    swap(first.orders, second.orders);
}

void Bookstore::addBook(std::shared_ptr<Book> book) {
    if (!book) {
        throw InvalidBookDataException("Cannot add an empty book.");
    }

    books.add(book);
}

std::shared_ptr<Book> Bookstore::findBookById(int id) const {
    for (const auto& book : books.getAll()) {
        if (book->getId() == id) {
            return book;
        }
    }

    throw BookNotFoundException("Book with id " + std::to_string(id) + " was not found.");
}

void Bookstore::showBooks() const {
    printCollection<Book>(books.getAll(), "Books from " + name + ":");
}

Order Bookstore::sellBook(int id, int quantity) {
    NoDiscountStrategy noDiscount;
    return sellBook(id, quantity, noDiscount);
}

Order Bookstore::sellBook(int id, int quantity, const DiscountStrategy& discountStrategy) {
    if (quantity <= 0) {
        throw InvalidBookDataException("Quantity must be positive.");
    }

    auto book = findBookById(id);

    if (quantity > book->getStock()) {
        throw NotEnoughStockException("Not enough stock for book: " + book->getTitle());
    }

    double rawTotalPrice = book->calculateFinalPrice() * quantity;
    double finalPrice = discountStrategy.applyDiscount(rawTotalPrice);

    // Bookstore can use any discount strategy here.
    book->reduceStock(quantity);

    Order order(book->getTitle(), quantity, finalPrice, discountStrategy.getName());
    orders.add(std::make_shared<Order>(order));

    return order;
}

void Bookstore::showPrintedBookShippingInfo() const {
    std::cout << "\nPrinted book shipping information:\n";

    for (const auto& book : books.getAll()) {
        auto printedBook = std::dynamic_pointer_cast<PrintedBook>(book);

        if (printedBook) {
            // This cast is safe because we check the result.
            std::cout << printedBook->getTitle()
                      << " has shipping cost "
                      << printedBook->getShippingCost() << '\n';
        }
    }
}

void Bookstore::showOrders() const {
    printCollection<Order>(orders.getAll(), "Orders:");
}
