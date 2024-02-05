#ifndef ESPRESSO_BASED_H
#define ESPRESSO_BASED_H
#include "ingredient.h"
#include <string>
#include <vector>

class EspressoBased {
public:
    [[nodiscard]] virtual std::string get_name() const = 0;
    [[nodiscard]] virtual double price() const = 0;
    void brew() const;
    std::vector<Ingredient *>& get_ingredients();
    virtual ~EspressoBased();

protected:
    EspressoBased();
    EspressoBased(const EspressoBased&esp);
    EspressoBased& operator=(const EspressoBased&esp);
    std::vector<Ingredient *> ingredients;
    std::string name;
};

#endif // ESPRESSO_BASED_H
