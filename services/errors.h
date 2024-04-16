#ifndef ERRORS_H
#define ERRORS_H

#include <stdexcept>

class ImageProcessorError : public std::runtime_error {
public:
    using runtime_error::runtime_error;
};

#endif  // ERRORS_H
