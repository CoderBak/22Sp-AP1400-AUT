#include "hw1.h"
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <random>
#include <iostream>

struct Size {
    size_t n, m;
};

void valid_check(size_t n, size_t m) {
    if (!n || !m) {
        throw std::logic_error("Invalid size");
    }
}

void valid_check(const Matrix& mat) {
    if (mat.size()) {
        size_t m = mat[0].size();
        int flag = 1;
        for (size_t i = 1; i < mat.size(); ++ i) {
            if (mat[i].size() != m) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            return;
        }
    }
    throw std::logic_error("Invalid matrix");
}

Size mat_size(const Matrix& mat) {
    return {mat.size(), mat[0].size()};
}

void valid_check(const Matrix& mat, size_t r, size_t c) {
    auto [u, v] = mat_size(mat);
    if (r < 0 || r >= u || c < 0 || c >= v) {
        throw std::logic_error("Out of bound");
    }
}

int valid_check(const Matrix& a, const Matrix& b) {
    int c1 = a.empty();
    int c2 = b.empty();
    if (c1 && (!c2) || c2 && (!c1)) {
        throw std::logic_error("Invalid size: empty");
    }
    return !(c1 && c2);
}

Matrix empty_mat() {
    Matrix mat;
    return mat;
}

namespace algebra {
Matrix zeros(size_t n, size_t m) {
    valid_check(n, m);
    Array line(m, 0);
    Matrix result(n, line);
    return result;
}

Matrix ones(size_t n, size_t m) {
    valid_check(n, m);
    Array line(m, 1);
    Matrix result(n, line);
    return result;
}

Matrix random(size_t n, size_t m, double min, double max) {
    valid_check(n, m);
    if (min > max) {
        throw std::logic_error("Invalid bound");
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    Matrix result;
    for (size_t i = 0; i < n; ++ i) {
        Array vec;
        for (size_t j = 0; j < m; ++ j) {
            vec.push_back(dis(gen));
        }
        result.push_back(vec);
    }
    return result;
}

void show(const Matrix& matrix) {
    if (matrix.empty()) {
        return;
    }
    valid_check(matrix);
    std::cout << std::showpoint << std::setprecision(3);
    for (auto& line : matrix) {
        for (auto& elem : line) {
            std::cout << std::setw(9) << elem << " ";
        }
        std::cout << "\n";
    }
}

Matrix multiply(const Matrix& matrix, double c) {
    if (matrix.empty()) {
        return empty_mat();
    }
    valid_check(matrix);
    Matrix mat = matrix;
    for (auto& line : mat) {
        for (auto& elem : line) {
            elem *= c;
        }
    }
    return mat;
}

Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
    if (!valid_check(matrix1, matrix2)) {
        return empty_mat();
    }
    valid_check(matrix1);
    valid_check(matrix2);
    auto [r1, c1] = mat_size(matrix1);
    auto [r2, c2] = mat_size(matrix2);
    if (c1 != r2) {
        throw std::logic_error("Invalid size when multiplying");
    }
    Matrix mat;
    for (size_t i = 0; i < r1; ++ i) {
        Array line;
        for (size_t j = 0; j < c2; ++ j) {
            T sum = 0;
            for (size_t k = 0; k < c1; ++ k) {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            line.push_back(sum);
        }
        mat.push_back(line);
    }
    return mat;
}

Matrix sum(const Matrix& matrix, double c) {
    if (matrix.empty()) {
        return empty_mat();
    }
    valid_check(matrix);
    Matrix mat = matrix;
    for (auto& line : mat) {
        for (auto& elem : line) {
            elem += c;
        }
    }
    return mat;
}

Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
    if (!valid_check(matrix1, matrix2)) {
        return empty_mat();
    }
    valid_check(matrix1);
    valid_check(matrix2);
    auto [r1, c1] = mat_size(matrix1);
    auto [r2, c2] = mat_size(matrix2);
    if (c1 != c2 || r1 != r2) {
        throw std::logic_error("Invalid size when summing");
    }
    Matrix mat;
    for (size_t i = 0; i < r1; ++ i) {
        Array line;
        for (size_t j = 0; j < c1; ++ j) {
            line.push_back(matrix1[i][j] + matrix2[i][j]);
        }
        mat.push_back(line);
    }
    return mat;
}

Matrix transpose(const Matrix& matrix) {
    if (matrix.empty()) {
        return empty_mat();
    }
    valid_check(matrix);
    auto [u, v] = mat_size(matrix);
    Matrix mat = zeros(v, u);
    for (size_t i = 0; i < u; ++ i) {
        for (size_t j = 0; j < v; ++ j) {
            mat[j][i] = matrix[i][j];
        }
    }
    return mat;
}

Matrix minor(const Matrix& matrix, size_t n, size_t m) {
    valid_check(matrix);
    valid_check(matrix, n, m);
    auto [u, v] = mat_size(matrix);
    Matrix mat;
    for (size_t i = 0; i < u; ++ i) {
        if (i == n) {
            continue;
        }
        Array line;
        for (size_t j = 0; j < v; ++ j) {
            if (j != m) {
                line.push_back(matrix[i][j]);
            }
        }
        mat.push_back(line);
    }
    return mat;
}

double determinant(const Matrix& matrix) {
    if (matrix.empty()) {
        return 1;
    }
    valid_check(matrix);
    auto [n, m] = mat_size(matrix);
    if (n != m) {
        throw std::logic_error("Invalid size when calculating determinant");
    }
    if (matrix.size() == 1) {
        return matrix[0][0];
    }
    T op = 1, result = 0;
    for (size_t j = 0; j < n; ++ j) {
        result += op * matrix[0][j] * determinant(minor(matrix, 0, j));
        op *= -1;
    }
    return result;
}

Matrix inverse(const Matrix& matrix) {
    if (matrix.empty()) {
        return empty_mat();
    }
    valid_check(matrix);
    auto [n, m] = mat_size(matrix);
    if (n != m) {
        throw std::logic_error("Invalid size when calculating inverse");
    }
    const T D = determinant(matrix);
    if (D == 0) {
        throw std::logic_error("Unable to get inverse matrix");
    }
    Matrix mat = zeros(n, n);
    for (size_t i = 0; i < n; ++ i) {
        for (size_t j = 0; j < n; ++ j) {
            mat[i][j] = determinant(minor(matrix, j, i)) / D;
            if ((i + j) % 2) {
                mat[i][j] *= -1;
            }
        }
    }
    return mat;
}

Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis) {
    if (axis != 0 && axis != 1) {
        throw std::logic_error("Invalid axis");
    }
    if (!valid_check(matrix1, matrix2)) {
        return empty_mat();
    }
    valid_check(matrix1);
    valid_check(matrix2);
    auto [r1, c1] = mat_size(matrix1);
    auto [r2, c2] = mat_size(matrix2);
    if ((axis == 0 && c1 != c2) || (axis == 1 && r1 != r2)) {
        throw std::logic_error("Invalid size when concatenating");
    }
    Matrix mat;
    if (axis == 0) {
        for (auto line : matrix1) {
            mat.push_back(line);
        }
        for (auto line : matrix2) {
            mat.push_back(line);
        }
    } else {
        for (size_t i = 0; i < r1; ++ i) {
            Array line = matrix1[i];
            for (auto elem : matrix2[i]) {
                line.push_back(elem);
            }
            mat.push_back(line);
        }
    }
    return mat;
}

Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2) {
    valid_check(matrix);
    valid_check(matrix, r1, 0);
    valid_check(matrix, r2, 0);
    Matrix mat = matrix;
    swap(mat[r1], mat[r2]);
    return mat;
}

Matrix ero_multiply(const Matrix& matrix, size_t r, double c) {
    valid_check(matrix);
    valid_check(matrix, r, 0);
    Matrix mat = matrix;
    for (auto& elems : mat[r]) {
        elems *= c;
    }
    return mat;
}

Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
    valid_check(matrix);
    valid_check(matrix, r1, 0);
    valid_check(matrix, r2, 0);
    auto [u, v] = mat_size(matrix);
    Matrix mat = matrix;
    for (size_t i = 0; i < v; ++ i) {
        mat[r2][i] += c * mat[r1][i];
    }
    return mat;
}

Matrix upper_triangular(const Matrix& matrix) {
    if (matrix.empty()) {
        return empty_mat();
    }
    valid_check(matrix);
    auto [n, m] = mat_size(matrix);
    if (n != m) {
        throw std::logic_error("Invalid size when upper_triangularing");
    }
    Matrix mat = matrix;

    // Guass elimination
    for (size_t i = 0; i < n - 1; ++ i) {
        for (size_t nonZero = i; nonZero < n; ++ nonZero) {
            if (mat[nonZero][i]) {
                swap(mat[i], mat[nonZero]);
                break;
            }
        }
        for (size_t j = i + 1; j < n; ++ j) {
            T r = mat[j][i] / mat[i][i];
            for (size_t k = i; k < n; ++ k) {
                mat[j][k] -= r * mat[i][k];
            }
        }
    }
    return mat;
}
}
