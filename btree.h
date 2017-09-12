#ifndef INHERITANCE_BTREE_H
#define INHERITANCE_BTREE_H

struct node {
    int* data;
    int size;
    node** child;
    bool leaf;
};

class btree {
public:
    btree();
    ~btree();

private:
    node* _root;

};


#endif //INHERITANCE_BTREE_H
