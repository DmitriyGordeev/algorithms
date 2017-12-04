#include <iostream>
#include <ctime>
#include "Tree.h"
using namespace std;


int main() {

    srand(time(NULL));
    Tree t;

    int middle = 100000;
    int range = 100000;

    t.add(middle);
    for(int i = middle - 1; i > middle - range; i--) {
        t.add(i);
        cout << "left branch: " << i << endl;
    }

    for(int i = middle + 1; i < middle + range; i++) {
        t.add(i);
        cout << "right branch: " << i << endl;
    }

    node* n = t.find(1);
    if(n) {
        cout << "n->value = " << n->value << endl;
    }



    return 0;
}