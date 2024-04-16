#include "color.h"

namespace image {

Color::Color(uint8_t red, uint8_t green, uint8_t blue) : blue_{blue}, green_{green}, red_{red} {
}

uint8_t Color::GetRed() const {
    return red_;
}

uint8_t Color::GetGreen() const {
    return green_;
}

uint8_t Color::GetBlue() const {
    return blue_;
}

void Color::SetRed(uint8_t red) {
    red_ = red;
}

void Color::SetGreen(uint8_t green) {
    green_ = green;
}

void Color::SetBlue(uint8_t blue) {
    blue_ = blue;
}

}  // namespace image
