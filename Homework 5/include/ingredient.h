#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <string>

class Ingredient {
public:
    [[nodiscard]] double get_price_unit() const;
    [[nodiscard]] size_t get_units() const;
    [[nodiscard]] virtual std::string get_name() const = 0;
    [[nodiscard]] double price() const;
    virtual ~Ingredient() = default;
    [[nodiscard]] virtual Ingredient* clone() const = 0;

protected:
    Ingredient(double price_unit, size_t units);

    double price_unit;
    size_t units;
    std::string name;
};

inline double Ingredient::get_price_unit() const { return price_unit; }
inline size_t Ingredient::get_units() const { return units; }
inline double Ingredient::price() const { return price_unit * static_cast<double>(units); }

inline Ingredient::Ingredient(const double price_unit, const size_t units) {
    this->price_unit = price_unit;
    this->units = units;
}

#endif // INGREDIENT_H
