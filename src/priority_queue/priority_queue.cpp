#include "priority_queue.h"

Node* PriorityQueue::find(int value) const {
    if (!_root)
        return nullptr;

    return _root->find_rec(value);
}

Node* PriorityQueue::add(int value) {
    if (!_root) {
        _root = new Node(value);
        return _root;
    }

    Node* node = _root->add_rec(value);
    node->swap_up_rec();
    return node;
}

void PriorityQueue::remove() {
    if (!_root)
        return;

    Node* replacement = _root->find_root_replacement_rec();
    if (!replacement)
        return;

    _root->value = replacement->value;

    // удаляем элемент, предварительно занулив указатели у его parent-ноды
    Node* replacement_parent = replacement->parent;
    if (replacement == replacement_parent->l_child)
        replacement_parent->l_child = nullptr;
    else if(replacement == replacement_parent->r_child)
        replacement_parent->r_child = nullptr;
    delete replacement;

    // толкаем root значение вниз,
    // пока он не встретит элементы ниже, которые больше по значению
    Node* X = _root->swap_down_rec();

    // толкаем его парент вверх, пока не всплывет достаточно,
    // чтобы соблюсти структуру PriorityQueue
    X->parent->swap_up_rec();
}

