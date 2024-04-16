#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include "parser/parser.h"
#include "services/io/reader.h"
#include "services/io/writer.h"

namespace image_processor {
void ParseAndApplyFilters(int argc, char** argv);
}  // namespace image_processor

#endif  // IMAGE_PROCESSOR_H
