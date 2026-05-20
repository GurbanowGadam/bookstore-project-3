#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// This function prints any collection that supports operator<<.
template <typename T>
void printCollection(const std::vector<std::shared_ptr<T>>& items, const std::string& title) {
    std::cout << "\n" << title << "\n";

    if (items.empty()) {
        std::cout << "No items found.\n";
        return;
    }

    for (const auto& item : items) {
        if (item) {
            std::cout << *item << "\n";
        }
    }
}
