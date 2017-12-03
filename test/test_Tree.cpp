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

};

TEST(unique, add)
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

TEST(correct_structure, add)
{
    TreeTest tt;
    tt.add(0);
    tt.add(-1);
    tt.add(4);
    tt.add(7);
    tt.add(3);

    EXPECT_EQ(5, tt.size());
    auto root = tt.unit_root();

    ASSERT_TRUE(root);

    ASSERT_TRUE(root->left);
    EXPECT_EQ(-1, root->left->value);
    EXPECT_FALSE(root->left->left);
    EXPECT_FALSE(root->left->right);

    ASSERT_TRUE(root->right);
    EXPECT_EQ(4, root->right->value);

    ASSERT_TRUE(root->right->left);
    EXPECT_EQ(3, root->right->left->value);
    EXPECT_FALSE(root->right->left->left);
    EXPECT_FALSE(root->right->left->right);

    ASSERT_TRUE(root->right->right);
    EXPECT_EQ(7, root->right->right->value);
    EXPECT_FALSE(root->right->right->left);
    EXPECT_FALSE(root->right->right->right);

}






int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

