#include <gtest/gtest.h>
#include "../src/Tree.h"
#include <iostream>

class TreeTest: public Tree {
public:
    TreeTest() : Tree() {}
    node* unit_add_recursive(node* entry, int value) {
        return add_recursive(entry, value);
    }
    node* unit_root() const {
        return root();
    }
    size_t unit_size() const {
        return size();
    }

};

TEST(unique, add_recursive)
{
    TreeTest tt;
    tt.add(0);
    EXPECT_EQ(1, tt.size());

    tt.add(0);
    EXPECT_EQ(1, tt.size());

    node* root = tt.unit_root();

    EXPECT_EQ(0, root->value);
    EXPECT_FALSE(root->left);
    EXPECT_FALSE(root->right);

}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

