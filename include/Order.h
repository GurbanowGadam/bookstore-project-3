#pragma once

#include <iosfwd>
#include <string>

class Order {
private:
    static int nextOrderId;
    const int id;
    std::string bookTitle;
    int quantity;
    std::string discountName;
    double totalPrice;

public:
    Order(const std::string& bookTitle, int quantity, double totalPrice,
          const std::string& discountName = "No discount");

    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};
