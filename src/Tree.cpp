#include "Tree.h"

Tree::Tree() {
    _size = 0;
    _root = nullptr;
}

Tree::~Tree() {}


node* Tree::add(int value)
{
    if(_root == nullptr) {
        _root = new node(value);
        _size++;
        return _root;
    }


}

node* Tree::find(int value)
{

}

node* Tree::erase(int value)
{

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

}