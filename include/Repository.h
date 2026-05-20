#pragma once

#include "BookstoreException.h"

#include <memory>
#include <vector>

// Generic storage for shared objects.
template <typename T>
class Repository {
private:
    std::vector<std::shared_ptr<T>> items;

public:
    void add(std::shared_ptr<T> item) {
        if (!item) {
            throw InvalidBookDataException("Cannot add an empty item.");
        }

        items.push_back(item);
    }

    const std::vector<std::shared_ptr<T>>& getAll() const {
        return items;
    }

    bool empty() const {
        return items.empty();
    }

    std::size_t size() const {
        return items.size();
    }

    void clear() {
        items.clear();
    }
};
