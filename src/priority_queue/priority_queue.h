
#ifndef ALGORITHMS_PRIORITY_QUEUE_H
#define ALGORITHMS_PRIORITY_QUEUE_H

#include <corecrt.h>

struct Node {
    Node() : value(0), l_child(nullptr), r_child(nullptr), parent(nullptr) {}

    Node(int x) : value(x), l_child(nullptr), r_child(nullptr), parent(nullptr) {}

    Node* find_rec(int x) {
        if (this->value == x)
            return this;

        Node *result = nullptr;
        if (this->l_child)
            result = this->l_child->find_rec(x);

        if (!result)
            if (this->r_child)
                result = this->r_child->find_rec(x);

        return result;
    }

    Node* add_rec(int x) {
        if (dl > dr + 1) {
            dr++;
            if (!r_child) {
                r_child = new Node(x);
                r_child->parent = this;
                return r_child;
            }
            return r_child->add_rec(x);
        }

        dl++;
        if (!l_child) {
            l_child = new Node(x);
            l_child->parent = this;
            return l_child;
        }

        return l_child->add_rec(x);
    }

    Node* swap_up_rec() {
        if (!parent)
            return this;

        if (this->value < parent->value) {
            int x = this->value;
            this->value = parent->value;
            parent->value = x;
            return parent->swap_up_rec();
        }
        return this;
    }

    Node* find_root_replacement_rec() {
        // идем по самому глубокому под-дереву,
        // потому что удаляя этот элемент, мы улучшим баланс дерева
        int side = dl - dr;
        if (side >= 0) {
            if (l_child)
                return l_child->find_root_replacement_rec();
        }

        if (!r_child)
            return this;

        return r_child->find_root_replacement_rec();
    }

    Node* swap_down_rec() {

        if (l_child) {
            if (!r_child || r_child->value > l_child->value) {
                if (l_child->value < this->value) {
                    l_swap();
                    return l_child->swap_down_rec();
                }
            }
        }

        if (r_child) {
            if (!l_child || l_child->value > r_child->value) {
                if (r_child->value < this->value) {
                    r_swap();
                    return r_child->swap_down_rec();
                }
            }
        }

        return this;
    }

    void r_swap() {
        int x_swap = this->value;
        this->value = r_child->value;
        r_child->value = x_swap;
    }

    void l_swap() {
        int x_swap = this->value;
        this->value = l_child->value;
        l_child->value = x_swap;
    }

    int value;
    Node *l_child;
    Node *r_child;
    Node *parent;

    // Balancing depths:
    int dl{0}; // depth of left subtree
    int dr{0}; // depth or right subtree
};

class PriorityQueue {
public:
    Node* find(int value) const;

    Node* add(int value);

    // можем удалить только корневой элемент
    // со всплывающей заменой на новый корень
    void remove();

    Node* get_root() const { return _root; }

#ifdef TEST
public:
#else
    protected:
#endif
    Node *_root{nullptr};
    size_t _len{0};
};


#endif //ALGORITHMS_PRIORITY_QUEUE_H
