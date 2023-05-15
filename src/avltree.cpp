#include "avltree.h"

namespace avl {

    // TODO: make a base class for both bstree and avltree ?

    avltree::~avltree() {
        clean_memory(m_root);
        m_root = nullptr;
    }

    node* avltree::add(int value) {
        if (!m_root) {
            m_root = new node(value);
            m_size++;
            return m_root;
        }


        // search correct location for new value
        node *cursor = m_root;
        while ((value >= cursor->value && cursor->right) || (value <= cursor->value && cursor->left)) {
            if (value < cursor->value)
                cursor = cursor->left;
            else if (value > cursor->value)
                cursor = cursor->right;
            else if (value == cursor->value)
                return cursor;      // if value already exists just return the node
        }

        // allocate new node
        node *n = new node(value);
        n->parent = cursor;
        m_size++;

        if (value < cursor->value) {
            cursor->left = n;

            // traverse upwards, recalculate heights and detect disbalance of subtree
            cursor = n;
            while(cursor->parent) {

                // 1. update heights
                auto max_height = cursor->h_left >= cursor->h_right ? cursor->h_left : cursor->h_right;
                if (cursor == cursor->parent->left)
                    cursor->parent->h_left = max_height + 1;
                else
                    cursor->parent->h_right = max_height + 1;

                // 2. check if subtree is disbalanced
                auto diff = cursor->parent->h_left - cursor->parent->h_right;
                if (diff < -1 || diff > 1) {

                    if (cursor == cursor->parent->left)
                        rotate_left(cursor);
                    else {
                        rotate_left(n);
                        rotate_right(n);
                    }

                    return n;
                }

                // 3. moving cursor up
                cursor = cursor->parent;
            }
        }

        else {
            cursor->right = n;

            // traverse upwards, recalculate heights and detect disbalance of subtree
            cursor = n;
            while(cursor->parent) {

                // 1. update heights
                auto max_height = cursor->h_left >= cursor->h_right ? cursor->h_left : cursor->h_right;
                if (cursor == cursor->parent->left)
                    cursor->parent->h_left = max_height + 1;
                else
                    cursor->parent->h_right = max_height + 1;

                // 2. check if subtree is disbalanced
                auto diff = cursor->parent->h_left - cursor->parent->h_right;
                if (diff < -1 || diff > 1) {

                    if (cursor == cursor->parent->right)
                        rotate_right(cursor);
                    else {
                        rotate_right(n);
                        rotate_left(n);
                    }

                    return n;
                }

                // 3. moving cursor up
                cursor = cursor->parent;
            }
        }

        return n;
    }

    bool avltree::erase(int value) {

        if (!m_root) return false;

        // traverse through the tree until we find the value or until we reach a leaf
        node* cursor = m_root;
        while(cursor->value != value) {
            if (value < cursor->value) {
                if (!cursor->left)
                    return false;
                cursor = cursor->left;
            }

            else if (value > cursor->value) {
                if (!cursor->right)
                    return false;
                cursor = cursor->right;
            }
        }


        // Check which subtree to use for replacing the value
        auto diff = cursor->h_left - cursor->h_right;
        if (diff >= 0) {
            // left subtree is higher or the same height
            // find the highest value of the left subtree
            auto hl = cursor->left->find_highest();
            auto hl_left_subtree = hl->left;

            cursor->value = hl->value;
            auto p = hl->parent;

            if (hl_left_subtree) {
                // change parent of hl_left_subtree;
                if (hl == p->right)
                    p->right = hl_left_subtree;
                else
                    p->left = hl_left_subtree;

                hl_left_subtree->parent = p;
                hl_left_subtree->recalculate_heights();
            }
            else {
                if (hl == p->left)
                    p->h_left = 0;
                else
                    p->h_right = 0;
                p->recalculate_heights();
            }

            delete hl;
        }
        else {
            // right subtree is higher
            // find the lowest value of the right subtree
            auto lr = cursor->right->find_lowest();
            auto lr_right_subtree = lr->right;

            cursor->value = lr->value;
            auto p = lr->parent;

            if (lr_right_subtree) {
                // change parent of lr_left_subtree;
                if (lr == p->left)
                    p->left = lr_right_subtree;
                else
                    p->right = lr_right_subtree;

                lr_right_subtree->parent = p;
                lr_right_subtree->recalculate_heights();
            }
            else {
                if (lr == p->left)
                    p->h_left = 0;
                else
                    p->h_right = 0;
                p->recalculate_heights();
            }

            delete lr;
        }

        return true;
    }

    node* avltree::get(int value) const {
        if (!m_root) return nullptr;

        if (m_root->value == value) return m_root;

        auto cursor = m_root;
        while((value <= cursor->value && cursor->left) || (value >= cursor->value && cursor->right)) {
            if (value > cursor->value)
                cursor = cursor->right;
            else if (value < cursor->value)
                cursor = cursor->left;

            if (value == cursor->value)
                return cursor;
        }
        return nullptr;
    }

    void avltree::rotate_left(node* pivot) {

        auto y = pivot->right;
        auto p = pivot->parent;
        if (y) { y->parent = p; }
        pivot->right = p;


        auto pp = pivot->parent->parent;
        if (pp) {
            if (p == pp->left)
                pp->left = pivot;
            else
                pp->right = pivot;
            pivot->parent = pp;
        }
        else {
            pivot->parent = nullptr;
            m_root = pivot;
        }

        p->parent = pivot;
        p->left = y;

        // change heights accordingly
        pivot->right->h_left = pivot->h_right;
        pivot->h_right = (pivot->h_right >= pivot->right->h_right ? pivot->h_right : pivot->right->h_right) + 1;
    }

    void avltree::rotate_right(node* pivot) {
        auto y = pivot->left;
        auto p = pivot->parent;
        if (y) { y->parent = p; }
        pivot->left = p;


        auto pp = pivot->parent->parent;
        if (pp) {
            if (p == pp->left)
                pp->left = pivot;
            else
                pp->right = pivot;
            pivot->parent = pp;
        }
        else {
            pivot->parent = nullptr;
            m_root = pivot;
        }

        p->parent = pivot;
        p->right = y;

        // change heights accordingly
        pivot->left->h_right = pivot->h_left;
        pivot->h_left = (pivot->h_left >= pivot->left->h_left ? pivot->h_left : pivot->left->h_left) + 1;
    }

    void avltree::clean_memory(node* start) {
        if (!start) return;

        clean_memory(start->left);
        clean_memory(start->right);

        if (!start->left && !start->right) {

            if (start->parent) {
                if (start == start->parent->left)
                    start->parent->left = nullptr;

                else if (start == start->parent->right)
                    start->parent->right = nullptr;
            }

            delete start;
            return;
        }
    }
}