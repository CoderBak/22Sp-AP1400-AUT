#ifndef MOCHA_H
#define MOCHA_H
#include "ingredient.h"
#include "espresso_based.h"
#include <string>
#include <vector>

class Mocha : public EspressoBased {
public:
    Mocha();
    Mocha(const Mocha&cap);
    ~Mocha() override;

    Mocha& operator=(const Mocha&cap);

    [[nodiscard]] std::string get_name() const override;
    [[nodiscard]] double price() const override;
    void add_side_item(Ingredient* side);
    std::vector<Ingredient *>& get_side_items();

private:
    std::vector<Ingredient *> side_items;
};

#endif // MOCHA_H
