#include "DiscountStrategy.h"

#include "BookstoreException.h"

double NoDiscountStrategy::applyDiscount(double price) const {
    // This strategy does not change the price.
    return price;
}

std::string NoDiscountStrategy::getName() const {
    return "No discount";
}

PercentageDiscountStrategy::PercentageDiscountStrategy(double percent)
    : percent(percent) {
    if (percent < 0 || percent > 100) {
        throw InvalidBookDataException("Percentage discount must be between 0 and 100.");
    }
}

double PercentageDiscountStrategy::applyDiscount(double price) const {
    return price - price * percent / 100.0;
}

std::string PercentageDiscountStrategy::getName() const {
    return "Percentage discount";
}

FixedDiscountStrategy::FixedDiscountStrategy(double amount)
    : amount(amount) {
    if (amount < 0) {
        throw InvalidBookDataException("Fixed discount cannot be negative.");
    }
}

double FixedDiscountStrategy::applyDiscount(double price) const {
    double discountedPrice = price - amount;

    if (discountedPrice < 0) {
        return 0;
    }

    return discountedPrice;
}

std::string FixedDiscountStrategy::getName() const {
    return "Fixed discount";
}
