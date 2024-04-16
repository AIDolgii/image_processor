#ifndef READER_H
#define READER_H

#include <cstring>
#include <fstream>
#include <memory>
#include <string_view>
#include "../errors.h"
#include "../utils/math_utils.h"
#include "../../structs/image/bmp_image.h"

namespace reader {
image::BmpImage ReadBmp(std::string_view path);
}  // namespace reader

#endif  // READER_H
