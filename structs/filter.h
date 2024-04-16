#ifndef FILTER_H
#define FILTER_H

#include <algorithm>
#include "image/bmp_image.h"
#include "../services/utils/image_utils.h"

namespace filters {
class Filter {
public:
    Filter() = default;
    Filter(const Filter& other) = default;
    virtual ~Filter() = default;

    virtual void Apply(image::BmpImage& image, const std::vector<std::string_view>& args) const = 0;

    virtual std::string_view GetName() const = 0;
    virtual std::vector<std::string_view> GetRequiredArgs() const = 0;
};

const std::string CROP_FLAG = "-crop";
const std::string CROP_FILTER_NAME = "crop";
const std::vector<std::string_view> CROP_REQUIRED_ARGS = {"width", "size_t", "height", "size_t"};

const std::string GRAYSCALE_FLAG = "-gs";
const std::string GRAYSCALE_FILTER_NAME = "grayscale";
const std::vector<std::string_view> GRAYSCALE_REQUIRED_ARGS = {};

const std::string NEGATIVE_FLAG = "-neg";
const std::string NEGATIVE_FILTER_NAME = "negative";
const std::vector<std::string_view> NEGATIVE_REQUIRED_ARGS = {};

const std::string SHARPENING_FLAG = "-sharp";
const std::string SHARPENING_FILTER_NAME = "sharpening";
const std::vector<std::string_view> SHARPENING_REQUIRED_ARGS = {};

const std::string EDGE_DETECTION_FLAG = "-edge";
const std::string EDGE_DETECTION_FILTER_NAME = "edge_detection";
const std::vector<std::string_view> EDGE_DETECTION_REQUIRED_ARGS = {"threshold", "float"};

const std::string GAUSSIAN_BLUR_FLAG = "-blur";
const std::string GAUSSIAN_BLUR_FILTER_NAME = "gaussian_blur";
const std::vector<std::string_view> GAUSSIAN_BLUR_REQUIRED_ARGS = {"sigma", "float"};

const std::string CRYSTALLIZE_FLAG = "-cryst";
const std::string CRYSTALLIZE_FILTER_NAME = "crystallize";
const std::vector<std::string_view> CRYSTALLIZE_REQUIRED_ARGS = {"step_size", "size_t"};
}  // namespace filters

#endif  // FILTER_H
