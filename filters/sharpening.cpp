#include "../structs/filter.h"

namespace filters {
class Sharpening : public Filter {
private:
    const utils::Kernel sharpening_kernel_ = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

public:
    void Apply(image::BmpImage& image, const std::vector<std::string_view>& args) const override {
        utils::CachedPerPixelOperation(image, 1, [this, image](size_t x, size_t y) {
            return utils::ApplyKernel(image, sharpening_kernel_, x, y);
        });
    }

    std::string_view GetName() const override {
        return SHARPENING_FILTER_NAME;
    }

    std::vector<std::string_view> GetRequiredArgs() const override {
        return SHARPENING_REQUIRED_ARGS;
    }
};
}  // namespace filters