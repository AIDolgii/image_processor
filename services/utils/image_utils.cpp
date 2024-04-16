#include "image_utils.h"

image::Color utils::ApplyKernel(const image::BmpImage& image, const Kernel& kernel, size_t x0, size_t y0,
                                std::function<float(float)> normalization_func) {

    float sum_red = 0;
    float sum_green = 0;
    float sum_blue = 0;

    for (size_t y = 0; y < kernel.size(); ++y) {
        for (size_t x = 0; x < kernel[y].size(); ++x) {
            int x_image = static_cast<int>(x0 + x) - static_cast<int>(kernel[y].size() / 2);
            int y_image = static_cast<int>(y0 + y) - static_cast<int>(kernel.size() / 2);

            x_image = std::clamp(x_image, 0, static_cast<int>(image.GetWidth()) - 1);
            y_image = std::clamp(y_image, 0, static_cast<int>(image.GetHeight()) - 1);

            image::Color pixel = image.GetPixelColor(x_image, y_image);
            sum_red += static_cast<float>(pixel.GetRed()) * kernel[y][x];
            sum_green += static_cast<float>(pixel.GetGreen()) * kernel[y][x];
            sum_blue += static_cast<float>(pixel.GetBlue()) * kernel[y][x];
        }
    }
    sum_red = normalization_func(sum_red);
    sum_green = normalization_func(sum_green);
    sum_blue = normalization_func(sum_blue);

    sum_red = std::clamp(sum_red, 0.0f, static_cast<float>(UINT8_MAX));
    sum_green = std::clamp(sum_green, 0.0f, static_cast<float>(UINT8_MAX));
    sum_blue = std::clamp(sum_blue, 0.0f, static_cast<float>(UINT8_MAX));
    return image::Color(static_cast<uint8_t>(sum_red), static_cast<uint8_t>(sum_green), static_cast<uint8_t>(sum_blue));
}

void utils::CachedPerPixelOperation(image::BmpImage& image, size_t cache_size,
                                    const std::function<image::Color(size_t x, size_t y)>& func) {
    Cache<image::Color> cache(cache_size, image.GetWidth());
    for (size_t y = 0; y < image.GetHeight() + cache_size - 1; ++y) {
        if (y < image.GetHeight()) {
            for (size_t x = 0; x < image.GetWidth(); ++x) {
                cache.Set(x, func(x, y));
            }
        }
        cache.Next();
        if (y >= cache_size - 1) {
            for (size_t x = 0; x < image.GetWidth(); ++x) {
                image.SetPixelColor(x, y - cache_size + 1, cache.Get(x));
            }
        }
    }
}

utils::Kernel utils::GetTransposedKernel(const utils::Kernel& kernel) {
    if (kernel.empty()) {
        return kernel;
    }
    size_t rows = kernel.size();
    size_t cols = kernel[0].size();
    std::vector<std::vector<float>> transposed_kernel(cols, std::vector<float>(rows));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            transposed_kernel[j][i] = kernel[i][j];
        }
    }
    return transposed_kernel;
}

image::Color utils::GetAverageColor(const std::vector<image::Color>& colors) {
    float sum_red = 0;
    float sum_green = 0;
    float sum_blue = 0;
    for (const image::Color& color : colors) {
        sum_red += static_cast<float>(color.GetRed());
        sum_green += static_cast<float>(color.GetGreen());
        sum_blue += static_cast<float>(color.GetBlue());
    }
    sum_red /= static_cast<float>(colors.size());
    sum_green /= static_cast<float>(colors.size());
    sum_blue /= static_cast<float>(colors.size());
    return image::Color(static_cast<uint8_t>(sum_red), static_cast<uint8_t>(sum_green), static_cast<uint8_t>(sum_blue));
}