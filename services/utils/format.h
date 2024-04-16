#ifndef FORMAT_H
#define FORMAT_H

#include <vector>
#include <string>
#include <string_view>

namespace utils {
template <typename T>
std::string ToString(T value) {
    if constexpr (std::is_same_v<T, std::string>) {
        return value;
    } else if constexpr (std::is_same_v<T, std::string_view>) {
        return static_cast<std::string>(value);
    } else if constexpr (std::is_same_v<T, char*>) {
        return std::string(value);
    } else {
        return std::to_string(value);
    }
}

template <typename... Args>
std::string Format(std::string format, Args... args) {
    std::string::size_type pos = 0;
    int count = 0;
    std::vector<std::string> arg_strings = {ToString(args)...};
    while ((pos = format.find("{}")) != std::string::npos) {
        format.replace(pos, 2, arg_strings[count]);
        ++count;
    }
    return format;
}
}  // namespace utils

#endif  // FORMAT_H