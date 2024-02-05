#ifndef BST_H
#define BST_H
#include <functional>

class BST
{
public:
    class Node
    {
    public:
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);

        int value;
        Node* left;
        Node* right;

        friend std::ostream& operator<<(std::ostream& os, const Node& obj);
        friend bool operator==(const Node& lhs, int rhs);
        friend bool operator==(int lhs, const Node& rhs);
        friend bool operator!=(const Node& lhs, int rhs);
        friend bool operator!=(int lhs, const Node& rhs);
        friend bool operator>(const Node& lhs, int rhs);
        friend bool operator>(int lhs, const Node& rhs);
        friend bool operator<(const Node& lhs, int rhs);
        friend bool operator<(int lhs, const Node& rhs);
        friend bool operator>=(const Node& lhs, int rhs);
        friend bool operator>=(int lhs, const Node& rhs);
        friend bool operator<=(const Node& lhs, int rhs);
        friend bool operator<=(int lhs, const Node& rhs);

    };
    explicit BST(); // Default constructor
    BST(std::initializer_list<int> init); // Constructor using initializer list
    BST(const BST& other); // Copy constructor
    BST(BST&& other) noexcept; // Move constructor
    ~BST(); // Destructor
    BST& operator=(const BST& rhs); // = as copy
    BST& operator=(BST&& rhs) noexcept; // = as move

    Node*& get_root();
    void bfs(const std::function<void(Node*& node)>& func);
    size_t length() const;
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);

    friend std::ostream& operator<<(std::ostream& os, const BST& obj);
    BST& operator++();
    BST operator++(int);

private:
    Node* root;
};

#endif //BST_H
