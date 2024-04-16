#include "writer.h"

void writer::WriteBmp(const image::BmpImage& image, std::string_view path) {
    if (path.empty()) {
        throw ImageProcessorError("No file path provided for writing");
    }
    std::ofstream file(path.data(), std::ios::binary);
    if (!file.is_open()) {
        throw ImageProcessorError("Can't open file" + static_cast<std::string>(path) + " for writing");
    }
    file.write(image.GetHeader().data(), static_cast<std::streamsize>(image.GetHeader().size()));
    std::string output_data;
    size_t line_size =
        utils::RoundUp(static_cast<int>(image.GetWidth() * sizeof(image::Color)), image::BMP_LINE_PADDING);
    output_data.reserve(line_size * image.GetHeight());
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            image::Color color = image.GetPixelColor(x, image.GetHeight() - y - 1);
            output_data.push_back(static_cast<char>(color.GetBlue()));
            output_data.push_back(static_cast<char>(color.GetGreen()));
            output_data.push_back(static_cast<char>(color.GetRed()));
        }
        for (size_t i = 0; i < line_size - image.GetWidth() * sizeof(image::Color); ++i) {
            output_data.push_back(0);
        }
    }
    file.write(output_data.data(), static_cast<std::streamsize>(output_data.size()));
    file.close();
}
