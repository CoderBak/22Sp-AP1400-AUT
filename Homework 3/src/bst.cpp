#include "bst.h"
#include <functional>
#include <string>
#include <vector>
#include <queue>
#include <ostream>
#include <iostream>
#include <iomanip>

BST::Node::Node(int value, Node* left, Node* right)
    : value(value), left(left), right(right) {
}

BST::Node::Node()
    : value(0), left(nullptr), right(nullptr) {
}

BST::Node::Node(const Node&node) = default;

std::ostream& operator<<(std::ostream&os, const BST::Node&obj) {
    os << std::left << std::setw(17) << &obj;
    os << "=> value:" << std::left << std::setw(10) << obj.value;
    os << "left:" << std::left << std::setw(17) << obj.left;
    os << "right:" << std::left << std::setw(17) << obj.right;
    return os;
}

bool operator==(const BST::Node&lhs, const int rhs) { return lhs.value == rhs; }
bool operator==(const int lhs, const BST::Node&rhs) { return rhs == lhs; }
bool operator!=(const BST::Node&lhs, const int rhs) { return !(lhs == rhs); }
bool operator!=(const int lhs, const BST::Node&rhs) { return !(lhs == rhs); }
bool operator>(const BST::Node&lhs, const int rhs) { return lhs.value > rhs; }
bool operator>(const int lhs, const BST::Node&rhs) { return lhs > rhs.value; }
bool operator<(const BST::Node&lhs, const int rhs) { return rhs > lhs; }
bool operator<(const int lhs, const BST::Node&rhs) { return rhs > lhs; }
bool operator>=(const BST::Node&lhs, const int rhs) { return !(lhs < rhs); }
bool operator>=(const int lhs, const BST::Node&rhs) { return !(lhs < rhs); }
bool operator<=(const BST::Node&lhs, const int rhs) { return !(lhs > rhs); }
bool operator<=(const int lhs, const BST::Node&rhs) { return !(lhs > rhs); }

BST::BST() : root(nullptr) {
}

BST::BST(const std::initializer_list<int> init) {
    root = nullptr;
    for (auto&elem: init) {
        add_node(elem);
    }
}

BST::BST(const BST&other) {
    root = nullptr;
    std::vector<int> data;
    const_cast<BST &>(other).bfs([&data](Node*&node) { data.push_back(node->value); });
    for (const auto&elem: data) {
        add_node(elem);
    }
}

BST::BST(BST&&other) noexcept {
    root = other.root;
    other.root = nullptr;
}

//BST::~BST() = default;

BST::~BST() {
    std::vector<Node *> nodes;
    bfs([&nodes](Node*&node) { nodes.push_back(node); });
    for (const auto&node: nodes) {
        delete node;
    }
}

BST& BST::operator=(const BST&rhs) {
    if (this == &rhs) {
        return *this;
    }
    root = nullptr;
    std::vector<int> data;
    const_cast<BST &>(rhs).bfs([&data](Node*&node) { data.push_back(node->value); });
    for (const auto&elem: data) {
        add_node(elem);
    }
    return *this;
}

BST& BST::operator=(BST&&rhs) noexcept {
    root = rhs.root;
    rhs.root = nullptr;
    return *this;
}

BST::Node*& BST::get_root() { return root; }

void BST::bfs(const std::function<void(Node*&node)>&func) {
    std::queue<Node *> q;
    q.push(root);
    while (!q.empty()) {
        Node* top = q.front();
        q.pop();
        if (top != nullptr) {
            q.push(top->left);
            q.push(top->right);
            func(top);
        }
    }
}

size_t BST::length() const {
    size_t size = 0;
    const_cast<BST &>(*this).bfs([&size](Node*&node) { size += 1; });
    return size;
}

bool BST::add_node(const int value) {
    Node** current = &root;
    while (true) {
        if (*current == nullptr) {
            *current = new Node(value, nullptr, nullptr);
            return true;
        }
        const int cur_val = (*current)->value;
        if (cur_val < value) { current = &((*current)->right); }
        if (cur_val > value) { current = &((*current)->left); }
        if (cur_val == value) { return false; }
    }
}

BST::Node** BST::find_node(const int value) {
    Node** current = &root;
    while (true) {
        if (*current == nullptr) { return nullptr; }
        const int cur_val = (*current)->value;
        if (cur_val < value) { current = &((*current)->right); }
        if (cur_val > value) { current = &((*current)->left); }
        if (cur_val == value) { return current; }
    }
}

BST::Node** BST::find_parrent(int value) {
    Node** current = &root;
    if (root->value == value) {
        return nullptr;
    }
    while (true) {
        if (*current == nullptr) { return nullptr; }
        if ((*current)->right != nullptr && (*current)->right->value == value
            || (*current)->left != nullptr && (*current)->left->value == value) {
            return current;
        }
        const int cur_val = (*current)->value;
        if (cur_val < value) { current = &((*current)->right); }
        if (cur_val > value) { current = &((*current)->left); }
    }
}

BST::Node** BST::find_successor(int value) {
    Node** cur = find_node(value);
    if (cur == nullptr) {
        return nullptr;
    }
    if ((*cur)->left != nullptr) {
        Node** toFind = &((*cur)->left);
        while (true) {
            if ((*toFind)->right == nullptr) {
                return toFind;
            }
            toFind = &((*toFind)->right);
        }
    }
    return nullptr;
}

bool BST::delete_node(int value) {
    Node** cur = find_node(value);
    if (cur != nullptr) {
        int cnt = 0;
        cnt += ((*cur)->left != nullptr);
        cnt += ((*cur)->right != nullptr);
        if (cnt == 0) { *cur = nullptr; }
        if (cnt == 1) { *cur = ((*cur)->left != nullptr) ? (*cur)->left : (*cur)->right; }
        if (cnt == 2) {
            Node** successor = find_successor(value);
            (*cur)->value = (*successor)->value;
            *successor = nullptr;
        }
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream&os, const BST&obj) {
    size_t size = 0;
    os << std::string(81, '*') << std::endl;
    const_cast<BST &>(obj).bfs([&os, &size](BST::Node*&node) {
        os << *node << std::endl;
        size += 1;
    });
    os << "binary search tree size: " << size << std::endl;
    os << std::string(81, '*') << std::endl;
    return os;
}

BST& BST::operator++() {
    bfs([](Node*&node) { node->value += 1; });
    return *this;
}

BST BST::operator++(int) {
    BST old(*this);
    bfs([](Node*&node) { node->value += 1; });
    return old;
}
