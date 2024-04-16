#ifndef WRITER_H
#define WRITER_H
#include <fstream>
#include "../errors.h"
#include "../utils/math_utils.h"
#include "../../structs/image/bmp_image.h"

namespace writer {
void WriteBmp(const image::BmpImage& image, std::string_view path);
}  // namespace writer

#endif  // WRITER_H
