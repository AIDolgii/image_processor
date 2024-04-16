#include "../structs/filter.h"

namespace filters {
class Negative : public Filter {
public:
    void Apply(image::BmpImage& image, const std::vector<std::string_view>& args) const override {
        utils::CachedPerPixelOperation(image, 1, [image](size_t x, size_t y) {
            image::Color pixel = image.GetPixelColor(x, y);
            return image::Color(UINT8_MAX - pixel.GetRed(), UINT8_MAX - pixel.GetGreen(), UINT8_MAX - pixel.GetBlue());
        });
    }

    std::string_view GetName() const override {
        return NEGATIVE_FILTER_NAME;
    }

    std::vector<std::string_view> GetRequiredArgs() const override {
        return NEGATIVE_REQUIRED_ARGS;
    }
};
}  // namespace filters