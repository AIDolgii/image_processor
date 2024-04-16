cmake_minimum_required(VERSION 3.27)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        image_processor
        image_processor.cpp
        services/io/reader.cpp
        structs/image/color.cpp
        structs/image/bmp_image.cpp
        services/utils/math_utils.cpp
        services/io/writer.cpp
        filters/crop.cpp
        filters/grayscale.cpp
        filters/negative.cpp
        filters/sharpening.cpp
        filters/edge_detection.cpp
        services/utils/image_utils.cpp
        filters/gaussian_blur.cpp
        filters/crystallize.cpp
        parser/parser.cpp
)