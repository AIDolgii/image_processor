#include "parser.h"

parser::Token::Token(std::shared_ptr<filters::Filter> filter, const std::vector<std::string_view>& args)
    : filter_(filter), args_(args) {
}

std::shared_ptr<filters::Filter> parser::Token::GetFilter() const {
    return filter_;
}

std::vector<std::string_view> parser::Token::GetArgs() const {
    return args_;
}

parser::FilterStore::FilterStore() {
    filters_[filters::CROP_FLAG] = std::make_shared<filters::Crop>();
    filters_[filters::SHARPENING_FLAG] = std::make_shared<filters::Sharpening>();
    filters_[filters::EDGE_DETECTION_FLAG] = std::make_shared<filters::EdgeDetection>();
    filters_[filters::GRAYSCALE_FLAG] = std::make_shared<filters::Grayscale>();
    filters_[filters::NEGATIVE_FLAG] = std::make_shared<filters::Negative>();
    filters_[filters::GAUSSIAN_BLUR_FLAG] = std::make_shared<filters::GaussianBlur>();
    filters_[filters::CRYSTALLIZE_FLAG] = std::make_shared<filters::Crystallize>();
}

std::shared_ptr<filters::Filter> parser::FilterStore::GetFilter(std::string_view filter_flag) const {
    auto it = filters_.find(filter_flag);
    if (it != filters_.end()) {
        return it->second;
    } else {
        throw ImageProcessorError(utils::Format("Filter '{}' not found", filter_flag));
    }
}

bool parser::FilterStore::ContainsFilter(std::string_view filter_flag) const {
    return filters_.contains(filter_flag);
}

std::vector<parser::Token> parser::ParseFilters(int argc, char* argv[]) {
    std::vector<Token> tokens;
    FilterStore filter_store;

    for (size_t i = 1; i < static_cast<size_t>(argc); ++i) {
        std::string_view arg = argv[i];

        if (arg[0] != '-') {
            throw ImageProcessorError(utils::Format("Invalid flag {}, {}", arg, argv[i - 1]));
        }
        if (!filter_store.ContainsFilter(arg)) {
            throw ImageProcessorError(utils::Format("Unknown filter {}", arg));
        }
        std::shared_ptr<filters::Filter> filter = filter_store.GetFilter(arg);
        std::vector<std::string_view> filter_args(filter->GetRequiredArgs().size() / 2);
        if (i + filter_args.size() >= static_cast<size_t>(argc)) {
            throw ImageProcessorError(utils::Format("Not enough arguments for filter {} (expected {}, got {})",
                                                    filter->GetName(), filter_args.size(),
                                                    argc - static_cast<int>(i) - 1));
        }
        size_t arg_pos = i;
        for (size_t j = 0; j < filter_args.size(); ++j, ++i) {
            filter_args[j] = argv[i + 1];
            if (filter_args[j].empty()) {
                throw ImageProcessorError(utils::Format("Empty argument for filter: {}", arg));
            }
            if (filter_store.ContainsFilter(argv[i + 1])) {
                throw ImageProcessorError(utils::Format("Not enough arguments for filter {} (expected {}, got {})",
                                                        filter->GetName(), filter_args.size(), i - arg_pos));
            }
            if (!utils::IsSuitableType(filter_args[j], filter->GetRequiredArgs()[2 * j + 1])) {
                throw ImageProcessorError(utils::Format(
                    "{} is invalid argument type for filter {} ({} should be {})", filter_args[j], filter->GetName(),
                    filter->GetRequiredArgs()[2 * j], filter->GetRequiredArgs()[2 * j + 1]));
            }
        }
        tokens.emplace_back(filter, filter_args);
    }

    return tokens;
}
