#include "bstree.h"
#include <iostream>
using std::cout;

namespace bst {

    node *bstree::add(int value) {
        if (!m_root) {
            m_root = new node(value);
            m_size++;
            return m_root;
        }

        node *cursor = m_root;
        while ((value >= cursor->value && cursor->right) || (value <= cursor->value && cursor->left)) {
            if (value > cursor->value)
                cursor = cursor->right;

            else if (value < cursor->value)
                cursor = cursor->left;

            else if (value == cursor->value)
                return cursor;
        }

        if (value > cursor->value) {
            node *n = new node(value);
            cursor->right = n;
            n->parent = cursor;
            m_size++;
            return n;
        } else {
            node *n = new node(value);
            cursor->left = n;
            n->parent = cursor;
            m_size++;
            return n;
        }
    }

    node *bstree::erase(int value) {
        if (!m_root) return nullptr;

        node *cursor = m_root;
        while (value >= cursor->value || value <= cursor->value) {

            if (value == cursor->value) {

                node* substitute = rearrange(cursor);
                if (cursor->parent) {

                    auto parent = cursor->parent;
                    if (cursor == parent->left) {
                        parent->left = substitute;
                        delete cursor;
                        m_size--;
                        return parent;
                    }

                    parent->right = substitute;
                    delete cursor;
                    m_size--;
                    return parent;
                }

                // if we need to remove the root element
                m_root = substitute;
                return m_root;
            }

            else if (value > cursor->value && cursor->right)
                cursor = cursor->right;

            else if (value < cursor->value && cursor->left)
                cursor = cursor->left;
        }

        return nullptr;
    }

    node *bstree::get(int value) const {
        if (!m_root) return nullptr;

        if (m_root->value == value) return m_root;

        auto cursor = m_root;
        while ((value >= cursor->value && cursor->right) || (value <= cursor->value && cursor->left)) {
            if (cursor->value == value)
                return cursor;

            if (value > cursor->value)
                cursor = cursor->right;

            else if (value < cursor->value)
                cursor = cursor->left;
        }

        if (value == cursor->value)
            return cursor;

        return nullptr;
    }


    /** returns a substitute for the cursor node (if we decided to erase this node)
     * and rearrange the tree according to the binary tree rules: left < x, right > x */
    node* bstree::rearrange(node* cursor) {
        if (!cursor) return nullptr;

        if (cursor->right) {
            node* lowest_right = find_lowest(cursor->right);
            lowest_right->left = cursor->left;
            return cursor->right;
        }

        return cursor->left;
    }


    node *bstree::find_lowest(node *start) {
        if (!start) return nullptr;     // if start is not valid

        node *cursor = start;
        while (cursor->left)
            cursor = cursor->left;
        return cursor;
    }

    node *bstree::find_highest(node *start) {
        if (!start) return nullptr;     // if start is not valid

        node *cursor = start;
        while (cursor->right)
            cursor = cursor->right;
        return cursor;
    }


    void bstree::clean(node *start) {
        if (!start) return;

        clean(start->left);
        clean(start->right);

        if (!start->left && !start->right) {

            if (start->parent) {
                if (start == start->parent->left)
                    start->parent->left = nullptr;

                else if (start == start->parent->right)
                    start->parent->right = nullptr;
            }

            cout << "deleting " << start->value << "\n";

            delete start;
            return;
        }
    }

    bstree::iterator bstree::begin() {
        return {find_lowest(m_root)};
    }

    bstree::iterator bstree::end() {
        return {find_highest(m_root)->right};       // right is null (out of bounds)
    }

}