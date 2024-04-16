#include <cmath>
#include "../structs/filter.h"

namespace filters {
class GaussianBlur : public Filter {
private:
    const float kernel_coef_ = 6;
    utils::Kernel CalculateKernel(float sigma) const {
        utils::Kernel result(1);
        auto blur_size = static_cast<size_t>(kernel_coef_ * sigma + 1);
        float sum = 0;
        int mid = static_cast<int>(blur_size) / 2;
        for (size_t i = 0; i < blur_size; ++i) {
            result.front().push_back(static_cast<float>(exp(-pow(static_cast<int>(i) - mid, 2) / (2 * pow(sigma, 2)))));
            sum += result.front().back();
        }
        for (size_t i = 0; i < blur_size; ++i) {
            result[0][i] /= sum;
        }
        return result;
    }

public:
    void Apply(image::BmpImage& image, const std::vector<std::string_view>& args) const override {
        float sigma = std::stof(static_cast<const std::string>(args[0]));
        utils::Kernel kernel = CalculateKernel(sigma);

        utils::CachedPerPixelOperation(image, kernel.size() / 2 + 1, [&image, &kernel](size_t x, size_t y) {
            return utils::ApplyKernel(image, kernel, x, y);
        });

        kernel = utils::GetTransposedKernel(kernel);
        utils::CachedPerPixelOperation(image, kernel.size() / 2 + 1, [&image, &kernel](size_t x, size_t y) {
            return utils::ApplyKernel(image, kernel, x, y);
        });
    }

    std::string_view GetName() const override {
        return GAUSSIAN_BLUR_FILTER_NAME;
    }

    std::vector<std::string_view> GetRequiredArgs() const override {
        return GAUSSIAN_BLUR_REQUIRED_ARGS;
    }
};
}  // namespace filters