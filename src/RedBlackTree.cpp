#include "RedBlackTree.h"

namespace rbtree
{
    RedBlackTree::RedBlackTree()
    {
        _root = nullptr;
        _size = 0;
    }

    RedBlackTree::~RedBlackTree() {}

    node* RedBlackTree::add(int value)
    {
        if(_root == nullptr) {
            _root = new node(value, false);
            _size++;
            return _root;
        }



    }

    node* RedBlackTree::find(int value)
    {

    }

    void RedBlackTree::erase(int value)
    {

    }

    node* RedBlackTree::add_recursive(node* entry, int value, bool is_black)
    {
        if(entry == nullptr) {
            entry = new node(value, is_black);
            _size++;
            return entry;
        }

        if(value == entry->value) {
            return entry;
        }
        else if(value < entry->value) {
            return add_recursive(entry->left, value, !entry->black);
        }
        else if(value)

    }

    node* RedBlackTree::find_recursive(node* entry, int value)
    {
    }

}