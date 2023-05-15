#ifndef TREE_BSTREE_H
#define TREE_BSTREE_H

#include <iterator>
#include <cstddef>

/** Simple binary search tree */

namespace bst {
    struct node {
        explicit node(int x) : value(x), left(nullptr), right(nullptr), parent(nullptr) {}

        int value;
        node* left;
        node* right;
        node* parent;
    };


    class bstree {
    public:
        bstree() : m_root(nullptr), m_size(0) {}

        virtual ~bstree() {
            clean(m_root);
            m_root = nullptr;
        }

        node* add(int value);

        node* erase(int value);

        [[nodiscard]] node* get(int value) const;

        [[nodiscard]] unsigned int size() const { return m_size; }

        node* get_root() { return m_root; }

        struct iterator {
            using iterator_cat = std::forward_iterator_tag;
            using diff_type = std::ptrdiff_t;
            using value_type = node;
            using pointer = node*;
            using ref = node&;

            iterator(pointer ptr) : m_ptr(ptr), m_prev(nullptr) {}

            ref operator * () const { return *m_ptr; }

            pointer operator -> () { return m_ptr; }

            iterator& operator ++ () {
                next();
                return *this;
            }

            iterator operator ++ (int) {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            // simple helper function
            void next() {

                // Check the left node and go if we haven't been there
                if (m_ptr->left && m_prev != m_ptr->left) {
                    m_prev = m_ptr;
                    m_ptr = m_ptr->left;
                    return;
                }

                // Check the right node and go if we haven't been there
                // searching the lowest pivot element
                else if (m_ptr->right && m_prev != m_ptr->right) {
                    m_prev = m_ptr;
                    m_ptr = find_lowest(m_ptr->right);
                    return;
                }

                // Traverse backwards (upwards) if each step up is done from the right side
                // we need to ignore m_ptr->parent because it was previously seen
                while (m_ptr->parent && m_ptr == m_ptr->parent->right) {
                    m_prev = m_ptr;
                    m_ptr = m_ptr->parent;
                }

                // If m_ptr->parent exists, and we've been on the right side,
                // or right not doesn't exist we need to go up
                if ((m_prev == m_ptr->right || !m_ptr->right) && m_ptr->parent) {
                    m_prev = m_ptr;
                    m_ptr = m_ptr->parent;
                }
                else if (!m_ptr->parent) {
                    m_prev = m_ptr;
                    m_ptr = nullptr;            // indicating end of iterator
                }

            }


            friend bool operator== (const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; };

        private:
            pointer m_ptr;
            pointer m_prev;
        };

        iterator begin();

        iterator end();


    protected:
        /** returns a substitute for the cursor node (if we decided to erase this node)
            * and rearrange the tree according to the binary tree rules: left < x, right > x */
        static node* rearrange(node* cursor);

        static node* find_lowest(node* start);

        static node* find_highest(node* start);

        static void clean(node* start);


    private:
        node* m_root;
        unsigned int m_size;
    };
}



#endif //TREE_BSTREE_H
