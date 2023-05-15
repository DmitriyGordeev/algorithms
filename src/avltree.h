#ifndef TREE_AVLTREE_H
#define TREE_AVLTREE_H

namespace avl {

    struct node {
        node(int x) :
            value(x),
            left(nullptr),
            right(nullptr),
            parent(nullptr),
            h_left(0),
            h_right(0) {}


        int value;
        node* left;
        node* right;
        node* parent;

        int h_left;
        int h_right;


        node* find_lowest() {
            node *cursor = this;
            while (cursor->left)
                cursor = cursor->left;
            return cursor;
        }

        node* find_highest() {
            node *cursor = this;
            while (cursor->right)
                cursor = cursor->right;
            return cursor;
        }

        void recalculate_heights() {
            node* cursor = this;
            while(cursor->parent) {
                int max_height = (cursor->h_left >= cursor->h_right) ? cursor->h_left : cursor->h_right;
                if (cursor == cursor->parent->left)
                    cursor->parent->h_left = max_height + 1;
                else
                    cursor->parent->h_right = max_height + 1;
                cursor = cursor->parent;
            }
        }
    };


    class avltree {
    public:
        avltree() : m_size(0), m_root(nullptr) {}

        virtual ~avltree();

        node* add(int value);

        bool erase(int value);

        [[nodiscard]] node* get(int value) const;

        [[nodiscard]] unsigned int size() const { return m_size; }

        [[nodiscard]] node* get_root() const { return m_root; }

    protected:
        void rotate_left(node* pivot);

        void rotate_right(node* pivot);

        void clean_memory(node* start);

    protected:
        node* m_root;
        unsigned int m_size;
    };
}




#endif //TREE_AVLTREE_H
