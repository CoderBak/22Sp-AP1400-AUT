#ifndef Q4_H
#define Q4_H
#include <numeric>
#include <vector>

namespace q4 {
    struct Vector2D {
        double x{}, y{};
    };

    inline Vector2D operator+(const Vector2D&a, const Vector2D&b) { return Vector2D{a.x + b.x, a.y + b.y}; }
    inline Vector2D operator*(const Vector2D&a, const double b) { return Vector2D{a.x * b, a.y * b}; }
    inline Vector2D operator*(const double a, const Vector2D&b) { return b * a; }
    inline Vector2D operator/(const Vector2D&a, const double b) { return Vector2D{a.x / b, a.y / b}; }

    struct Sensor {
        Vector2D pos;
        double accuracy{};
    };

    inline Vector2D kalman_filter(const std::vector<Sensor>&sensors) {
        std::vector<Vector2D> weighted;
        double tot = 0;
        std::ranges::transform(sensors, std::back_inserter(weighted), [&tot](const Sensor&x) {
            tot += x.accuracy;
            return x.pos * x.accuracy;
        });
        return std::accumulate(weighted.begin(), weighted.end(), Vector2D{}) / tot;
    }
}


#endif //Q4_H
