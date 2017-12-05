#include "RedBlackTree.h"

namespace rbtree {

    RedBlackTree::RedBlackTree()
    {
        _root = nullptr;
        _size = 0;
    }

    RedBlackTree::~RedBlackTree() {}

    node* RedBlackTree::add(int value)
    {
        if(_root == nullptr) {
            _root = new node(value, BLACK);
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

    node* RedBlackTree::add_recursive(node* entry, int value)
    {
        if(entry == nullptr) {
            entry = new node(value, RED);
            _size++;
            rotate(entry);
            return entry;
        }
    }

    node* RedBlackTree::find_recursive(node* entry, int value)
    {
    }

    void RedBlackTree::rotate(node* entry)
    {
        if(!entry)
            return;

        if(entry == _root) {
            _root->color == COLOR::BLACK;
            return;
        }

        if(entry->parent) {
            if(entry->parent->color == COLOR::BLACK)
                return;
        }


        if(entry->parent)
        {

            // case one: uncle is red:
            if(entry->parent->color == RED)
            {
                if(entry->parent->parent)
                {
                    node* father = entry->parent;
                    node* grandfa = father->parent;

                    node* uncle = father->bro();
                    if(uncle) {
                        if (uncle->color == COLOR::RED) {
                            father->color = COLOR::BLACK;
                            uncle->color = COLOR::BLACK;
                            grandfa->color = COLOR::RED;

                            rotate(grandfa);
                        }
                    }
                }
            }


        }


    }


}