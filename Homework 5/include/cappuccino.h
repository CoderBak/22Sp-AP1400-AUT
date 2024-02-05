#ifndef CAPPUCCINO
#define CAPPUCCINO
#include "ingredient.h"
#include "espresso_based.h"
#include <string>
#include <vector>

class Cappuccino : public EspressoBased {
public:
    Cappuccino();
    Cappuccino(const Cappuccino&cap);
    ~Cappuccino() override;

    Cappuccino& operator=(const Cappuccino&cap);

    [[nodiscard]] std::string get_name() const override;
    [[nodiscard]] double price() const override;
    void add_side_item(Ingredient* side);
    std::vector<Ingredient *>& get_side_items();

private:
    std::vector<Ingredient *> side_items;
};

#endif // CAPPUCCINO
