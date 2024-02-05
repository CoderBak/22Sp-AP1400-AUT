# 22Sp-AP1400-AUT
Amirkabir University of Technology 1400-2: Advanced Programming Course

homework 5 多态的析构函数

在你的析构函数中，使用 delete i 尝试释放 side_items 中的指针是一个合理的尝试，但问题可能出现在你添加了副产品时。原因在于 side_items 是一个存储指向 Ingredient 对象的指针的 std::vector，而在你的复制构造函数和赋值操作符中，并没有进行深拷贝（deep copy）操作。

在复制构造函数和赋值操作符中，你使用了 std::ranges::copy 来复制 cap 对象的 side_items 到当前对象的 side_items 中。这将只复制指针的值，而不会复制指针指向的对象。因此，当你销毁一个 Cappuccino 对象时，会导致 side_items 中的指针指向的对象被删除多次，这会导致未定义行为。

解决这个问题的一种方法是，在复制构造函数和赋值操作符中，对 side_items 中的每个指针进行深拷贝，即创建新的 Ingredient 对象并将其指针存储在 side_items 中。这样可以确保每个 Cappuccino 对象拥有自己独立的 side_items。修改后的代码如下所示：
