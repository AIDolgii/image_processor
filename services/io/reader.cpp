#include "reader.h"

image::BmpImage reader::ReadBmp(std::string_view path) {
    if (path.empty()) {
        throw ImageProcessorError("No file path provided for reading");
    }
    std::ifstream file(path.data(), std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        throw ImageProcessorError("Failed to open file " + static_cast<std::string>(path.data()) + " for reading");
    }
    auto header = std::make_unique<char[]>(image::BMP_HEADER_SIZE);
    file.read(header.get(), image::BMP_HEADER_SIZE);
    if (file.gcount() != image::BMP_HEADER_SIZE) {
        throw ImageProcessorError("Failed to read BMP header from file " + static_cast<std::string>(path.data()));
    }
    if (std::string_view(header.get(), 2) != image::K_BMP_SIGNATURE) {
        throw ImageProcessorError("File " + static_cast<std::string>(path.data()) + " is not a BMP file");
    }
    uint32_t width = 0;
    uint32_t height = 0;
    std::memcpy(&width, header.get() + image::BMP_WIDTH_OFFSET, sizeof(uint32_t));
    std::memcpy(&height, header.get() + image::BMP_HEIGHT_OFFSET, sizeof(uint32_t));
    if (width == 0 || height == 0) {
        throw ImageProcessorError("Invalid image dimensions in file " + static_cast<std::string>(path.data()));
    }
    size_t line_size = utils::RoundUp(static_cast<int>(width * sizeof(image::Color)), image::BMP_LINE_PADDING);
    size_t data_size = line_size * height;
    auto data = std::make_unique<char[]>(data_size);
    file.read(data.get(), static_cast<std::streamsize>(data_size));
    if (static_cast<size_t>(file.gcount()) != data_size) {
        throw ImageProcessorError("Failed to read image data from file " + static_cast<std::string>(path.data()));
    }
    image::BmpImage result{std::string(header.get(), image::BMP_HEADER_SIZE), width, height};
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            image::Color color;
            std::memcpy(&color, data.get() + y * line_size + x * sizeof(image::Color), sizeof(image::Color));
            result.SetPixelColor(x, height - y - 1, color);
        }
    }
    return result;
}
