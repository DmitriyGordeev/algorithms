#ifndef ALGORITHMS_TREE_H
#define ALGORITHMS_TREE_H

#include <cstddef>

struct node
{
    node(int value) {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }

    int value;
    node* left;
    node* right;
};


class Tree
{
public:
    Tree();
    ~Tree();

    node* add(int value);
    node* find(int value);
    node* erase(int value);

protected:
    node* add_recursive(node* entry, int value);
    node* find_recursive(node* entry, int value);

protected:
    node* _root;
    size_t _size;
};


#endif
