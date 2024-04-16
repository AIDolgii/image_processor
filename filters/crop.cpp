#include "../structs/filter.h"

namespace filters {
class Crop : public Filter {
public:
    void Apply(image::BmpImage& image, const std::vector<std::string_view>& args) const override {
        int64_t width = std::stol(static_cast<const std::string>(args[0]));
        int64_t height = std::stol(static_cast<const std::string>(args[1]));
        if (width < 0 || height < 0) {
            throw ImageProcessorError("Invalid crop size (negative input)");
        }
        image.Resize(std::min(static_cast<size_t>(width), image.GetWidth()),
                     std::min(static_cast<size_t>(height), image.GetHeight()));
    }

    std::string_view GetName() const override {
        return CROP_FILTER_NAME;
    }

    std::vector<std::string_view> GetRequiredArgs() const override {
        return CROP_REQUIRED_ARGS;
    }
};
}  // namespace filters
