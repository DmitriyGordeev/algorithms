#include <gtest/gtest.h>
#include "../src/Tree.h"
#include <iostream>

class TreeTest: public Tree {
public:
    TreeTest() : Tree() {}
    node* unit_add_recursive(node* entry, int value) {
        return add_recursive(entry, value);
    }
    node* unit_root() {
        return root();
    }
    size_t unit_size() const {
        return size();
    }

};

TEST(returnsNull, add_recursive)
{
    TreeTest tt;
    node* root = tt.unit_root();

    EXPECT_EQ(nullptr, root);

    node* n = tt.unit_add_recursive(root, 0);
    EXPECT_EQ(0, n->value);

}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

