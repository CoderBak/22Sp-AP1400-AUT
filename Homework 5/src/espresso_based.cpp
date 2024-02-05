#include "espresso_based.h"
#include <iostream>
#include <vector>
#include <unistd.h>
#include <iomanip>

void EspressoBased::brew() const {
    std::cout << "Preparing your " << name << std::endl;
    sleep(3);
    double units = 0, cur = 0;
    for (const auto&i: ingredients) {
        units += static_cast<double>(i->get_units());
    }
    for (const auto&i: ingredients) {
        std::cout << "Adding: " << std::left << std::setw(11) << i->get_name() << " ";
        std::cout << std::right << std::setw(4) << static_cast<int>(100 * cur / units) << " %" << std::endl;
        cur += static_cast<double>(i->get_units());
        sleep(static_cast<unsigned int>(10 * static_cast<double>(i->get_units()) / units));
    }
    std::cout << "Finished! Please enjoy it!" << std::endl;
    sleep(5);
}

std::vector<Ingredient *>& EspressoBased::get_ingredients() { return ingredients; }

EspressoBased::~EspressoBased() {
    for (const auto&i: ingredients) { delete i; }
    ingredients.clear();
}

EspressoBased::EspressoBased() = default;

EspressoBased::EspressoBased(const EspressoBased&esp) {
    for (const auto&i: esp.ingredients) {
        ingredients.push_back(i->clone());
    }
    name = esp.name;
}

EspressoBased& EspressoBased::operator=(const EspressoBased&esp) {
    if (this == &esp) {
        return *this;
    }
    for (const auto&i: ingredients) { delete i; }
    ingredients.clear();
    for (const auto&i: esp.ingredients) {
        ingredients.push_back(i->clone());
    }
    name = esp.name;
    return *this;
}
