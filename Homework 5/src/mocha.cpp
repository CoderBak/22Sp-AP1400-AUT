#include "mocha.h"
#include <sub_ingredients.h>
#include <vector>

Mocha::Mocha() {
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    ingredients.push_back(new Chocolate(1));
    name = "Mocha";
}

Mocha::Mocha(const Mocha&cap) : EspressoBased(cap) {
    for (const auto&i: cap.side_items) {
        side_items.push_back(i->clone());
    }
}

Mocha::~Mocha() {
    for (const auto&i: side_items) { delete i; }
    side_items.clear();
}

Mocha& Mocha::operator=(const Mocha&cap) {
    if (this == &cap) {
        return *this;
    }
    for (const auto&i: ingredients) { delete i; }
    ingredients.clear();
    for (const auto&i: side_items) { delete i; }
    side_items.clear();
    for (const auto&i: cap.ingredients) {
        ingredients.push_back(i->clone());
    }
    for (const auto&i: cap.side_items) {
        side_items.push_back(i->clone());
    }
    return *this;
}

std::string Mocha::get_name() const { return name; }

double Mocha::price() const {
    double sum = 0;
    for (const auto&i: ingredients) { sum += i->price(); }
    for (const auto&i: side_items) { sum += i->price(); }
    return sum;
}

void Mocha::add_side_item(Ingredient* side) { side_items.push_back(side); }

std::vector<Ingredient *>& Mocha::get_side_items() { return side_items; }
