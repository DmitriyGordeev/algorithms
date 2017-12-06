#include "RedBlackTree.h"

namespace rbtree {

    RedBlackTree::RedBlackTree()
    {
        _root = nullptr;
        _size = 0;
    }

    RedBlackTree::~RedBlackTree() {
        // TODO: copy release() method from Tree
    }

    node* RedBlackTree::add(int value)
    {
        if(_root == nullptr) {
            _root = new node(value, BLACK);
            _size++;
            return _root;
        }

        return add_recursive(_root, value);
    }

    node* RedBlackTree::find(int value)
    {
        // TODO: copy from Tree and test
    }

    void RedBlackTree::erase(int value)
    {
        // TODO
    }

    node* RedBlackTree::add_recursive(node* entry, int value)
    {
        if(entry == nullptr) {
            entry = new node(value, RED);
            resolve_red_red(entry);
            _size++;
            return entry;
        }

        if(value == entry->value) {
            return nullptr;
        }
        else if(value < entry->value) {
            if(entry->left == nullptr) {
                entry->left = new node(value, RED);
                entry->left->parent = entry;
                resolve_red_red(entry->left);
                _size++;
                return entry;
            }
            else {
                return add_recursive(entry->left, value);
            }
        }
        else {
            if(entry->right == nullptr) {
                entry->right = new node(value, RED);
                entry->right->parent = entry;
                resolve_red_red(entry->right);
                _size++;
                return entry;
            }
            else {
                return add_recursive(entry->right, value);
            }
        }
    }
 
    node* RedBlackTree::find_recursive(node* entry, int value)
    {
        // TODO
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