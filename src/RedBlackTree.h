#ifndef ALGORITHMS_REDBLACKTREE_H
#define ALGORITHMS_REDBLACKTREE_H

#include <cstddef>

namespace rbtree
{
    struct node
    {
        node(int value, bool red)
        {
            this->value = value;
            this->red = red;
            this->left = nullptr;
            this->right = nullptr;
        }

        int value;
        node* left;
        node* right;
        bool red;
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
        node* _root;
        size_t _size;

    };
}






#endif //ALGORITHMS_REDBLACKTREE_H
