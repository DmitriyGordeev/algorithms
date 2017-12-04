#include "Tree.h"

Tree::Tree() {
    _size = 0;
    _root = nullptr;
}

Tree::~Tree() {
    release_memory();
}



node* Tree::add(int value)
{
    if(_root == nullptr) {
        _root = new node(value);
        _size++;
        return _root;
    }

    return add_recursive(_root, value);
}

node* Tree::find(int value)
{
    return find_recursive(_root, value);
}

void Tree::erase(int value)
{
    if(_root) {
        if(value == _root->value) {

            node* r = _root;

            if(!_root->left && !_root->right) {
                _root = nullptr;
            }

            // only left:
            else if(_root->left && !_root->right) {
                _root = _root->left;
            }

            // only right:
            else if(!_root->left && _root->right) {
                _root = _root->right;
            }

            // both:
            else {
                node* least_of_right = seek_end(_root->right);
                if(least_of_right) {
                    least_of_right->left = _root->left;
                    _root = _root->right;
                }
            }

            delete r;
            _size--;
        }
    }


    node* p = find_parent_recursive(_root, value);
    if(p == nullptr) {
        return;
    }

    node* v = nullptr;
    if(value == p->left->value) {
        v = p->left;

        if(!v->left && !v->right) {
            p->left = nullptr;
        }

        // only left:
        else if(v->left && !v->right) {
            p->left = v->left;
        }

        // only right:
        else if(!v->left && v->right) {
            p->left = v->right;
        }

        // both:
        else {
            node* least_of_right = seek_end(v->right);
            if(least_of_right) {
                least_of_right->left = v->left;
                p->left = v->right;
            }
        }

        delete v;
        _size--;

    }
    else if(value == p->right->value) {
        v = p->right;

        if(!v->left && !v->right) {
            p->right = nullptr;
        }

        // only left:
        else if(v->left && !v->right) {
            p->right = v->left;
        }

        // only right:
        else if(!v->left && v->right) {
            p->right = v->right;
        }

        // both:
        else {
            node* least_of_right = seek_end(v->right);
            if(least_of_right) {
                least_of_right->left = v->left;
                p->right = v->right;
            }
        }

        delete v;
        _size--;
    }
}



node* Tree::add_recursive(node* entry, int value)
{
    if(entry == nullptr) {
        entry = new node(value);
        _size++;
        return entry;
    }

    if(value == entry->value) {
        return nullptr;
    }
    else if(value < entry->value) {
        if(entry->left == nullptr) {
            entry->left = new node(value);
            _size++;
            return entry;
        }
        else {
            return add_recursive(entry->left, value);
        }
    }
    else {
        if(entry->right == nullptr) {
            entry->right = new node(value);
            _size++;
            return entry;
        }
        else {
            return add_recursive(entry->right, value);
        }
    }
}

node* Tree::find_recursive(node* entry, int value)
{
    if(entry == nullptr) {
        return nullptr;
    }

    if(value == entry->value) {
        return entry;
    }

    if(value < entry->value) {
        return find_recursive(entry->left, value);
    }
    else {
        return find_recursive(entry->right, value);
    }
}

node* Tree::find_parent_recursive(node* entry, int value)
{
    if(entry == nullptr) {
        return nullptr;
    }

    if(entry->left == nullptr) {
        return nullptr;
    }

    if(entry->right == nullptr) {
        return nullptr;
    }

    if(value == entry->left->value) {
        return entry;
    }

    if(value == entry->right->value) {
        return entry;
    }

    node* left_branch_result = find_parent_recursive(entry->left, value);
    node* right_branch_result = find_parent_recursive(entry->right, value);

    if(left_branch_result)
        return left_branch_result;
    if(right_branch_result)
        return right_branch_result;

    return nullptr;
}

bool is_disbalanced(node* entry)
{

}

node* Tree::seek_end(node* entry, bool left)
{
    if(entry == nullptr) {
        return nullptr;
    }

    if(left) {
        if(entry->left) {
            return seek_end(entry->left, left);
        }
        return entry;
    } else {
        if(entry->right) {
            return seek_end(entry->right, left);
        }
        return entry;
    }
}

void Tree::release_memory()
{
    release_recursive(_root);
}

void Tree::release_recursive(node* entry)
{
    if(!entry) {
        return;
    }

    if(entry->left) {
        release_recursive(entry->left);
    }

    if(entry->right) {
        release_recursive(entry->right);
    }

    delete entry;
}

