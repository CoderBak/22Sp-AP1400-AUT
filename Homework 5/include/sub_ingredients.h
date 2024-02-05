#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H
#define DEFCLASS(X, price) \
class X : public Ingredient {\
public:\
    explicit X(const size_t units) : Ingredient{price, units} {\
        name = #X;\
    }\
    std::string get_name() const override { return name; }\
    X* clone() const override { return new X(*this); }\
}

DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);

#endif // SUB_INGREDIENTS_H
