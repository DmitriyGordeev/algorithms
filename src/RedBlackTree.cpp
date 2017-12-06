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
            resolve_red_red(entry);
            return entry;
        }
    }
 
    node* RedBlackTree::find_recursive(node* entry, int value)
    {
    }

    void RedBlackTree::resolve_red_red(node* entry)
    {
        if(!entry)
            return;

        if(entry == _root) {
            _root->color = BLACK;
            return;
        }

        if(entry->parent)
        {
            if(entry->parent->color == COLOR::BLACK)
                return;

            if(entry->parent->color == RED)
            {
                if(entry->parent->parent)
                {
                    node* father = entry->parent;
                    node* grandfa = father->parent;

                    node* uncle = father->bro();
                    if(uncle) {

                        // case one: uncle is red:
                        if (uncle->color == COLOR::RED) {
                            father->color = COLOR::BLACK;
                            uncle->color = COLOR::BLACK;
                            grandfa->color = COLOR::RED;

                            resolve_red_red(grandfa);
                        }
                    }


                    // case two: uncle is black of doesn't exists
                    if(!uncle || uncle->color == BLACK)
                    {
                        grandfa->color = RED;
                        if(entry->value < father->value) {
                            rotate_right(grandfa);
                            father->color = BLACK;
                        }
                        else if(entry->value > father->value)
                        {
                            entry->color = BLACK;
                            rotate_left(father);
                            rotate_right(grandfa);
                        }
                    }
                }
            }
        }
    }

    void RedBlackTree::rotate_left(node* A)
    {
        node* father = A->parent;
        if(A->right)
        {
            node* C = A->right;

            A->parent = C;
            A->right = C->left;
            C->left = A;
            C->parent = father;

            if(father) {
                if (A->value < father->value)
                    father->left = C;
                else
                    father->right = C;
            }
        }
    }

    void RedBlackTree::rotate_right(node* A)
    {
        node* father = A->parent;
        if(A->left)
        {
            node* B = A->left;

            A->parent = B;
            A->left = B->right;
            B->right = A;
            B->parent = father;

            if(father) {
                if(A->value < father->value)
                    father->left = B;
                else
                    father->right = B;
            }

        }
    }
}