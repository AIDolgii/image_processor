#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include "../../structs/image/color.h"

namespace utils {
template <typename T>
class Cache {
private:
    std::vector<std::vector<T>> data_;
    size_t current_line_ = 0;

public:
    Cache() = default;
    Cache(size_t height, size_t width) : data_(height, std::vector<T>(width)) {
    }

    Cache(const Cache&) = delete;
    ~Cache() = default;

    void Set(size_t x, const T& color) {
        data_[current_line_][x] = color;
    }

    void Next() {
        current_line_ = (current_line_ + 1) % data_.size();
    }

    const T& Get(size_t x) const {
        return data_[current_line_][x];
    }
};
}  // namespace utils

#endif  // CACHE_H