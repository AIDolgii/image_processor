#ifndef GRAYSCALE_FILTER_CPP
#define GRAYSCALE_FILTER_CPP
#include "../structs/filter.h"

namespace filters {
class Grayscale : public Filter {
private:
    const float red_coefficient_ = 0.299f;
    const float green_coefficient_ = 0.587f;
    const float blue_coefficient_ = 0.114f;

    uint8_t CntGrayValue(uint8_t red, uint8_t green, uint8_t blue) const {
        float red_value = static_cast<float>(red) * red_coefficient_;
        float green_value = static_cast<float>(green) * green_coefficient_;
        float blue_value = static_cast<float>(blue) * blue_coefficient_;
        return static_cast<uint8_t>(red_value + green_value + blue_value);
    }

public:
    void Apply(image::BmpImage& image, const std::vector<std::string_view>& args) const override {
        utils::CachedPerPixelOperation(image, 1, [this, image](size_t x, size_t y) {
            image::Color pixel = image.GetPixelColor(x, y);
            uint8_t gray_value = CntGrayValue(pixel.GetRed(), pixel.GetGreen(), pixel.GetBlue());
            return image::Color(gray_value, gray_value, gray_value);
        });
    }

    std::string_view GetName() const override {
        return GRAYSCALE_FILTER_NAME;
    }

    std::vector<std::string_view> GetRequiredArgs() const override {
        return GRAYSCALE_REQUIRED_ARGS;
    }
};
}  // namespace filters

#endif  // GRAYSCALE_FILTER_CPP
