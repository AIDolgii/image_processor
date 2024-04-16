#include "../structs/filter.h"
#include "grayscale.cpp"

namespace filters {
class EdgeDetection : public Filter {
private:
    const utils::Kernel edge_detection_kernel_ = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

public:
    void Apply(image::BmpImage& image, const std::vector<std::string_view>& args) const override {
        Grayscale temp;
        temp.Apply(image, {});
        float threshold = std::stof(static_cast<const std::string>(args[0]));
        utils::CachedPerPixelOperation(image, 1, [this, image, threshold](size_t x, size_t y) {
            return utils::ApplyKernel(image, edge_detection_kernel_, x, y, [threshold](float value) {
                return value > threshold * static_cast<float>(UINT8_MAX) ? UINT8_MAX : 0;
            });
        });
    }

    std::string_view GetName() const override {
        return EDGE_DETECTION_FILTER_NAME;
    }

    std::vector<std::string_view> GetRequiredArgs() const override {
        return EDGE_DETECTION_REQUIRED_ARGS;
    }
};
}  // namespace filters
