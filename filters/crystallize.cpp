#include "../structs/filter.h"

namespace filters {
class Crystallize : public Filter {
private:
    const float offset_delta_ = 0.3f;

    void ProcessQuadrangle(image::BmpImage& image, const utils::Quadrangle& quadrangle) const {
        utils::Point min_point = quadrangle.GetMin();
        utils::Point max_point = quadrangle.GetMax();

        int min_x = std::max(static_cast<int>(min_point.x), 0);
        int max_x = std::min(static_cast<int>(max_point.x), static_cast<int>(image.GetWidth()) - 1);
        int min_y = std::max(static_cast<int>(min_point.y), 0);
        int max_y = std::min(static_cast<int>(max_point.y), static_cast<int>(image.GetHeight()) - 1);

        std::vector<image::Color> colors;
        for (int y = min_y; y <= max_y; ++y) {
            for (int x = min_x; x <= max_x; ++x) {
                if (!utils::IsPointInQuadrangle({static_cast<float>(x), static_cast<float>(y)}, quadrangle)) {
                    continue;
                }
                colors.push_back(image.GetPixelColor(x, y));
            }
        }

        image::Color average_color = utils::GetAverageColor(colors);
        for (int y = min_y; y <= max_y; ++y) {
            for (int x = min_x; x <= max_x; ++x) {
                if (!utils::IsPointInQuadrangle({static_cast<float>(x), static_cast<float>(y)}, quadrangle)) {
                    continue;
                }
                image.SetPixelColor(x, y, average_color);
            }
        }
    }

public:
    void Apply(image::BmpImage& image, const std::vector<std::string_view>& args) const override {
        int step_size = std::stoi(static_cast<const std::string>(args[0]));
        utils::Plane plane =
            utils::GeneratePointsWithOffset(image.GetWidth(), image.GetHeight(), step_size, offset_delta_);
        std::vector<utils::Quadrangle> quadrangles = utils::GenerateQuadrangles(plane);
        for (const auto& quadrangle : quadrangles) {
            ProcessQuadrangle(image, quadrangle);
        }
    }

    std::string_view GetName() const override {
        return CRYSTALLIZE_FILTER_NAME;
    }

    std::vector<std::string_view> GetRequiredArgs() const override {
        return CRYSTALLIZE_REQUIRED_ARGS;
    }
};
}  // namespace filters