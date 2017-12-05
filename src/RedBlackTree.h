#ifndef ALGORITHMS_REDBLACKTREE_H
#define ALGORITHMS_REDBLACKTREE_H

#include <cstddef>

namespace rbtree
{
    enum COLOR { BLACK, RED };
    struct node
    {
        node(int value, COLOR color)
        {
            this->value = value;
            this->color = color;
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
        }

        node* bro() {
            if(this->parent) {
                if(this == this->parent->left)
                    return this->parent->right;
                else
                    return this->parent->left;
            }

            return nullptr;
        }

        int value;
        node* left;
        node* right;
        node* parent;
        COLOR color;
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
        node* add_recursive(node* entry, int value);
        node* find_recursive(node* entry, int value);
        void resolve_red_red(node* entry);
        static void rotate_left(node* node);
        static void rotate_right(node* node);

    protected:
        node* _root;
        size_t _size;

    };
}






#endif //ALGORITHMS_REDBLACKTREE_H
