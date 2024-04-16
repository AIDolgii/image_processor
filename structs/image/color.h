#ifndef PIXEL_COLOR_H
#define PIXEL_COLOR_H

#include <cstddef>
#include <cstdint>

const int CHANNELS_AMOUNT = 3;

namespace image {
class Color {
private:
    uint8_t blue_;
    uint8_t green_;
    uint8_t red_;

public:
    Color() = default;
    Color(uint8_t red, uint8_t green, uint8_t blue);
    Color(const Color& pixel_color) = default;
    ~Color() = default;

    uint8_t GetRed() const;
    uint8_t GetGreen() const;
    uint8_t GetBlue() const;

    void SetRed(uint8_t red);
    void SetGreen(uint8_t green);
    void SetBlue(uint8_t blue);
};
}  // namespace image

#endif  // PIXEL_COLOR_H
