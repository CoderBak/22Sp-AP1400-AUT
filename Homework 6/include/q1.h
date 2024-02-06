#ifndef Q1_H
#define Q1_H
#include <functional>

namespace q1 {
    inline double derivative(const double x, const std::function<double(double)>&func) {
        constexpr double dx = 1e-5;
        return 1e5 * (func(x + dx) - func(x));
    }

    inline double solver(double x, const double step, const std::function<double(double)>&func) {
        for (int k = 0; k < 5000000; k += 1) {
            x = x - derivative(x, func) * step;
        }
        return x;
    }

    template<typename T, typename Func>
    double gradient_descent(const double x, const double step) {
        return solver(x, step, Func());
    }

    template<typename Func>
    double gradient_descent(const double x, const double step, Func func) {
        return solver(x, step, static_cast<const std::function<double(double)> &>(func));
    }

    inline double gradient_descent(const double x, const double step, double (*func)(double)) {
        return solver(x, step, func);
    }
}

#endif //Q1_H
