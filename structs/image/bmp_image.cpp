#include "bmp_image.h"

namespace image {

BmpImage::BmpImage(const std::string& header, size_t width, size_t height)
    : width_{width}, height_{height}, header_{header} {
    data_.resize(height);
    for (size_t i = 0; i < height; ++i) {
        data_[i].resize(width, Color());
    }
}

size_t BmpImage::GetWidth() const {
    return width_;
}

size_t BmpImage::GetHeight() const {
    return height_;
}

void BmpImage::Resize(size_t width, size_t height) {
    if (width == width_ && height == height_) {
        return;
    }
    if (data_.empty() || width > data_.front().size()) {
        for (size_t i = 0; i < height_; ++i) {
            for (size_t j = width_; j < width; ++j) {
                data_[i].emplace_back();
            }
        }
    }
    if (height > data_.size()) {
        for (size_t i = height_; i < height; ++i) {
            data_.emplace_back(width, Color());
        }
    }
    width_ = width;
    height_ = height;
    UpdateHeader();
}

std::string_view BmpImage::GetHeader() const {
    return header_;
}

Color BmpImage::GetPixelColor(size_t x, size_t y) const {
    if (y >= height_ || x >= width_) {
        throw ImageProcessorError("Invalid pixel coordinates");
    }
    return data_[y][x];
}

void BmpImage::SetPixelColor(size_t x, size_t y, const Color& color) {
    if (y >= height_ || x >= width_) {
        throw ImageProcessorError("Invalid pixel coordinates");
    }
    data_[y][x] = color;
}

void BmpImage::UpdateHeader() {
    size_t file_size =
        BMP_HEADER_SIZE + utils::RoundUp(static_cast<int>(width_ * sizeof(Color)), BMP_LINE_PADDING) * height_;
    for (size_t i = 0; i < 4; ++i) {
        header_[BMP_FILE_SIZE_OFFSET + i] =
            static_cast<char>((file_size >> (i * sizeof(char) * BYTE_SIZE)) & UINT8_MAX);
        header_[BMP_WIDTH_OFFSET + i] = static_cast<char>((width_ >> (i * sizeof(char) * BYTE_SIZE)) & UINT8_MAX);
        header_[BMP_HEIGHT_OFFSET + i] = static_cast<char>((height_ >> (i * sizeof(char) * BYTE_SIZE)) & UINT8_MAX);
    }
}

}  // namespace image
