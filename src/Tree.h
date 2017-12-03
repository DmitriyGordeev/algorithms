#ifndef ALGORITHMS_TREE_H
#define ALGORITHMS_TREE_H

#include <cstddef>
#include <iostream>

struct node
{
    node(int value) {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }

    ~node() {
        std::cout << "~node(): value was: " << value << std::endl;
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
    void erase(int value);
    size_t size() const { return _size; }

protected:
    node* add_recursive(node* entry, int value);
    node* find_recursive(node* entry, int value);
    node* find_parent_recursive(node* entry, int value);

    node* seek_end(node* entry, bool left = true);
    node* root() const { return _root; }


private:
    node* _root;
    size_t _size;
};


#endif
