#include "image_processor.h"

void image_processor::ParseAndApplyFilters(int argc, char** argv) {
    if (argc < 2) {
        throw ImageProcessorError("No input file specified");
    }
    image::BmpImage image = reader::ReadBmp(argv[1]);
    if (argc < 3) {
        throw ImageProcessorError("No output file specified");
    }
    for (std::vector<parser::Token> tokens = parser::ParseFilters(argc - 2, argv + 2);
            const parser::Token& token : tokens) {
        token.GetFilter()->Apply(image, token.GetArgs());
    }
    writer::WriteBmp(image, argv[2]);
}

int main(int argc, char** argv) {
    image_processor::ParseAndApplyFilters(argc, argv);
    return 0;
}
