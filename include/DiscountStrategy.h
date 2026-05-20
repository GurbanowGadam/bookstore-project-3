#pragma once

#include <string>

// Strategy interface for discount rules.
class DiscountStrategy {
public:
    virtual double applyDiscount(double price) const = 0;
    virtual std::string getName() const = 0;
    virtual ~DiscountStrategy() = default;
};

class NoDiscountStrategy : public DiscountStrategy {
public:
    double applyDiscount(double price) const override;
    std::string getName() const override;
};

class PercentageDiscountStrategy : public DiscountStrategy {
private:
    double percent;

public:
    explicit PercentageDiscountStrategy(double percent);

    double applyDiscount(double price) const override;
    std::string getName() const override;
};

class FixedDiscountStrategy : public DiscountStrategy {
private:
    double amount;

public:
    explicit FixedDiscountStrategy(double amount);

    double applyDiscount(double price) const override;
    std::string getName() const override;
};
