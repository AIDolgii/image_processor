#include "math_utils.h"
#include "../errors.h"

utils::Point utils::Quadrangle::GetMin() const {
    return {std::min({a.x, b.x, c.x, d.x}), std::min({a.y, b.y, c.y, d.y})};
}

utils::Point utils::Quadrangle::GetMax() const {
    return {std::max({a.x, b.x, c.x, d.x}), std::max({a.y, b.y, c.y, d.y})};
}

int utils::RoundUp(int num, int multiple) {
    if (multiple == 0) {
        return 0;
    }
    return num + (multiple - (num % multiple)) % multiple;
}

utils::Plane utils::GeneratePointsWithOffset(size_t width, size_t height, int step, float offset_delta) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(static_cast<float>(-step) * offset_delta,
                                         static_cast<float>(step) * offset_delta);

    utils::Plane plane;
    for (int y = -step; y < static_cast<int>(height) + step * 2; y += step) {
        std::vector<utils::Point> row;
        for (int x = -step; x < static_cast<int>(width) + step * 2; x += step) {
            auto offset_x = static_cast<float>(dis(gen));
            auto offset_y = static_cast<float>(dis(gen));
            row.push_back({static_cast<float>(x) + offset_x, static_cast<float>(y) + offset_y});
        }
        plane.push_back(row);
    }

    return plane;
}

std::vector<utils::Quadrangle> utils::GenerateQuadrangles(const Plane& plane) {
    std::vector<utils::Quadrangle> quadrangles;
    for (size_t i = 0; i < plane.size() - 1; ++i) {
        for (size_t j = 0; j < plane[i].size() - 1; ++j) {
            quadrangles.push_back({plane[i][j], plane[i][j + 1], plane[i + 1][j], plane[i + 1][j + 1]});
        }
    }
    return quadrangles;
}

bool utils::IsPointInQuadrangle(const utils::Point& p, const utils::Quadrangle& q) {
    std::vector<utils::Point> polygon = {q.a, q.b, q.d, q.c};
    bool inside = false;
    for (size_t i = 0, j = polygon.size() - 1; i < polygon.size(); j = i++) {
        if (((polygon[i].y >= p.y) != (polygon[j].y >= p.y)) &&
            (p.x <=
             (polygon[j].x - polygon[i].x) * (p.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x)) {
            inside = !inside;
        }
    }
    return inside;
}

bool utils::IsSuitableType(std::string_view value, std::string_view type) {
    if (type == "size_t") {
        try {
            size_t converted = std::stoul(std::string(value));
            return converted > 0 && value.find('.') == std::string_view::npos;
        } catch (const std::invalid_argument&) {
            return false;
        }
    } else if (type == "float") {
        try {
            std::stof(std::string(value));
            return true;
        } catch (const std::invalid_argument&) {
            return false;
        }
    }
    return false;
}