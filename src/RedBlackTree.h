#ifndef ALGORITHMS_REDBLACKTREE_H
#define ALGORITHMS_REDBLACKTREE_H

#include <cstddef>

namespace rbtree
{
    struct node
    {
        node(int value, bool black)
        {
            this->value = value;
            this->black = black;
            this->left = nullptr;
            this->right = nullptr;
        }

        int value;
        node* left;
        node* right;
        bool black;
    };


    class RedBlackTree
    {
    public:
        RedBlackTree();
        ~RedBlackTree();

        node* add(int value);
        node* find(int value);
        void erase(int value);

        size_t size() const { return _size; }

    protected:
        node* add_recursive(node* entry, int value, bool is_black);
        node* find_recursive(node* entry, int value);

    protected:
        node* _root;
        size_t _size;

    };
}






#endif //ALGORITHMS_REDBLACKTREE_H
