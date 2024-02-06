# 22Sp-AP1400-AUT
Amirkabir University of Technology 1400-2: Advanced Programming Course

homework 5 多态的析构函数

在你的析构函数中，使用 delete i 尝试释放 side_items 中的指针是一个合理的尝试，但问题可能出现在你添加了副产品时。原因在于 side_items 是一个存储指向 Ingredient 对象的指针的 std::vector，而在你的复制构造函数和赋值操作符中，并没有进行深拷贝（deep copy）操作。

在复制构造函数和赋值操作符中，你使用了 std::ranges::copy 来复制 cap 对象的 side_items 到当前对象的 side_items 中。这将只复制指针的值，而不会复制指针指向的对象。因此，当你销毁一个 Cappuccino 对象时，会导致 side_items 中的指针指向的对象被删除多次，这会导致未定义行为。

解决这个问题的一种方法是，在复制构造函数和赋值操作符中，对 side_items 中的每个指针进行深拷贝，即创建新的 Ingredient 对象并将其指针存储在 side_items 中。这样可以确保每个 Cappuccino 对象拥有自己独立的 side_items。修改后的代码如下所示：

现在有基类 Ingredient, 子类 Milk, Chocolate ，现在我有一个 vector<Ingredient*>，内含 new Milk(2) 和 new Chocolate(1) ，我现在想深拷贝这个 vector，即还要复制里面每个指针所指向的对象，怎么办
ChatGPT
如果你想深拷贝一个 vector<Ingredient*>，即需要复制其中每个指针指向的对象，你需要遍历原始 vector，对其中的每个指针指向的对象进行深拷贝，并将新创建的对象的指针存储在新的 vector 中。下面是一个示例代码：

```cpp
#include <iostream>
#include <vector>

// 假设Ingredient及其子类的定义

class Ingredient {
public:
    virtual ~Ingredient() {} // 虚析构函数
    virtual Ingredient* clone() const = 0; // 克隆函数
    virtual void use() const = 0; // 使用函数
};

class Milk : public Ingredient {
public:
    virtual Milk* clone() const override {
        return new Milk(*this);
    }
    virtual void use() const override {
        std::cout << "Using Milk" << std::endl;
    }
};

class Chocolate : public Ingredient {
public:
    virtual Chocolate* clone() const override {
        return new Chocolate(*this);
    }
    virtual void use() const override {
        std::cout << "Using Chocolate" << std::endl;
    }
};

int main() {
    std::vector<Ingredient*> originalIngredients;
    originalIngredients.push_back(new Milk(2));
    originalIngredients.push_back(new Chocolate(1));

    std::vector<Ingredient*> copiedIngredients;
    copiedIngredients.reserve(originalIngredients.size()); // 保证足够的空间

    for (auto* ingredient : originalIngredients) {
        copiedIngredients.push_back(ingredient->clone()); // 深拷贝每个对象并存储指针
    }

    // 现在 copiedIngredients 中包含了深拷贝后的对象

    // 使用 copiedIngredients 的对象
    for (auto* ingredient : copiedIngredients) {
        ingredient->use();
    }

    // 释放 originalIngredients 和 copiedIngredients 中的对象
    for (auto* ingredient : originalIngredients) {
        delete ingredient;
    }
    for (auto* ingredient : copiedIngredients) {
        delete ingredient;
    }

    return 0;
}

```

踩的坑：1. operator= 里面没用清空 this 2. 多态析构 3. 深度复制


Homework 6

1。 注意function 的适配问题

the math-function can be a pointer to function, lambda function or a functor

2. 正则表达式的使用

Homework 4 借助 template 实现智能指针 同时实现一个 if (ptr) 的效果，其实就是重载 bool() 运算符
