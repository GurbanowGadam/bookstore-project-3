#include "Order.h"

#include <iomanip>
#include <iostream>
#include <sstream>

int Order::nextOrderId = 1;

Order::Order(const std::string& bookTitle, int quantity, double totalPrice,
             const std::string& discountName)
    : id(nextOrderId++),
      bookTitle(bookTitle),
      quantity(quantity),
      discountName(discountName),
      totalPrice(totalPrice) {
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    std::ostringstream priceStream;
    priceStream << std::fixed << std::setprecision(2) << order.totalPrice;

    os << "Order #" << order.id << '\n'
       << "Book: " << order.bookTitle << '\n'
       << "Quantity: " << order.quantity << '\n'
       << "Discount: " << order.discountName << '\n'
       << "Total price: " << priceStream.str();

    return os;
}
