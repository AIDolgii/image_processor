#ifndef FILTER_STORE_H
#define FILTER_STORE_H

#include <map>
#include <memory>
#include "../services/utils/format.h"
#include "../filters/crop.cpp"
#include "../filters/sharpening.cpp"
#include "../filters/edge_detection.cpp"
#include "../filters/grayscale.cpp"
#include "../filters/negative.cpp"
#include "../filters/gaussian_blur.cpp"
#include "../filters/crystallize.cpp"

namespace parser {
class Token {
private:
    std::shared_ptr<filters::Filter> filter_;
    std::vector<std::string_view> args_;

public:
    Token() = default;
    Token(std::shared_ptr<filters::Filter> filter, const std::vector<std::string_view>& args);
    Token(const Token& other) = default;
    ~Token() = default;

    std::shared_ptr<filters::Filter> GetFilter() const;
    std::vector<std::string_view> GetArgs() const;
};

class FilterStore {
private:
    std::map<std::string_view, std::shared_ptr<filters::Filter>> filters_;

public:
    FilterStore();
    std::shared_ptr<filters::Filter> GetFilter(std::string_view filter_flag) const;
    bool ContainsFilter(std::string_view filter_flag) const;
};

std::vector<Token> ParseFilters(int argc, char* argv[]);
}  // namespace parser

#endif  // FILTER_STORE_H
