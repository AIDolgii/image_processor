#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include <cstddef>
#include <vector>
#include <memory>
#include "color.h"
#include "../../services/utils/math_utils.h"
#include "../../services/errors.h"

namespace image {
const char* const K_BMP_SIGNATURE = "BM";
const int BMP_HEADER_SIZE = 54;
const int BMP_WIDTH_OFFSET = 18;
const int BMP_HEIGHT_OFFSET = 22;
const int BMP_FILE_SIZE_OFFSET = 2;
const int BMP_LINE_PADDING = 4;
const int BYTE_SIZE = 8;

class BmpImage {
private:
    size_t width_;
    size_t height_;
    std::vector<std::vector<Color>> data_;
    std::string header_;

    void UpdateHeader();

public:
    BmpImage() = default;
    BmpImage(const BmpImage& image) = default;
    BmpImage(const std::string& header, size_t width, size_t height);
    ~BmpImage() = default;

    size_t GetWidth() const;
    size_t GetHeight() const;
    void Resize(size_t width, size_t height);
    std::string_view GetHeader() const;
    Color GetPixelColor(size_t x, size_t y) const;
    void SetPixelColor(size_t x, size_t y, const Color& color);
};
}  // namespace image

#endif  // BMP_IMAGE_H
