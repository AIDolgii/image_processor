#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <algorithm>
#include "cache.h"
#include "math_utils.h"
#include "../../structs/image/bmp_image.h"

namespace utils {

using Kernel = std::vector<std::vector<float>>;

image::Color ApplyKernel(
    const image::BmpImage& image, const Kernel& kernel, size_t x0, size_t y0,
    std::function<float(float)> normalization_func = [](float x) { return x; });

void CachedPerPixelOperation(image::BmpImage& image, size_t cache_size,
                             const std::function<image::Color(size_t x, size_t y)>& func);

Kernel GetTransposedKernel(const Kernel& kernel);

image::Color GetAverageColor(const std::vector<image::Color>& colors);
}  // namespace utils

#endif  // IMAGE_UTILS_H
