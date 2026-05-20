#pragma once

#include "Book.h"
#include "Order.h"
#include "Repository.h"

#include <memory>
#include <string>

class DiscountStrategy;

class Bookstore {
private:
    std::string name;
    Repository<Book> books;
    Repository<Order> orders;

public:
    explicit Bookstore(const std::string& name);
    Bookstore(const Bookstore& other);

    Bookstore& operator=(Bookstore other);

    friend void swap(Bookstore& first, Bookstore& second) noexcept;

    void addBook(std::shared_ptr<Book> book);
    std::shared_ptr<Book> findBookById(int id) const;
    void showBooks() const;
    Order sellBook(int id, int quantity);
    Order sellBook(int id, int quantity, const DiscountStrategy& discountStrategy);
    void showPrintedBookShippingInfo() const;
    void showOrders() const;
};
