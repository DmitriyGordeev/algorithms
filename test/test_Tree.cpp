#include <gtest/gtest.h>
#include "../src/Tree.h"
#include <iostream>

class TreeTest: public Tree {
public:
    TreeTest() : Tree() {}
    node* unit_add_recursive(node* entry, int value) {
        return add_recursive(entry, value);
    }
    node* unit_find_parent_recursive(node* entry, int value) {
        return find_parent_recursive(entry, value);
    }
    node* unit_seek_end(node* entry, bool left = true) {
        return seek_end(entry, left);
    }
    node* unit_root() const {
        return root();
    }
    bool unit_is_balanced(node* entry) {
        return is_balanced(entry);
    }

};

TreeTest generate_tree()
{
    TreeTest tt;
    tt.add(0);
    tt.add(-1);
    tt.add(4);
    tt.add(7);
    tt.add(3);

    return tt;
}

TEST(add, unique_elements) {

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

TEST(add, correct_structure){

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

TEST(find, returns_nullptr_on_empty) {

    TreeTest tt;
    EXPECT_FALSE(tt.find(10));
}

TEST(find, returns_nullptr_on_non_existing) {

    TreeTest tt;
    tt.add(0);
    tt.add(1);
    tt.add(-1);

    EXPECT_FALSE(tt.find(2));
}

TEST(find, returns_correct) {

    TreeTest tt;
    tt.add(0);
    tt.add(1);
    tt.add(-1);

    auto f = tt.find(1);

    EXPECT_TRUE(f);
    EXPECT_EQ(1, f->value);
}

TEST(find_parent_recursive, returns_nullptr_on_non_existing) {

    TreeTest tt = generate_tree();

    node* root = tt.unit_root();
    node* p = tt.unit_find_parent_recursive(root, 10);
    ASSERT_TRUE(p == nullptr);
}

TEST(find_parent_recursive, returns_correct) {

    TreeTest tt;
    tt.add(0);
    tt.add(-1);
    tt.add(4);
    tt.add(7);
    tt.add(3);


    node* root = tt.unit_root();
    node* p = tt.unit_find_parent_recursive(root, 3);
    ASSERT_FALSE(p == nullptr);
    EXPECT_EQ(4, p->value);
}

TEST(seek_end, returns_correct) {

    TreeTest tt = generate_tree();
    node* left_end = tt.unit_seek_end(tt.unit_root());
    ASSERT_TRUE(left_end);
    EXPECT_EQ(-1, left_end->value);

    node* right_end = tt.unit_seek_end(tt.unit_root(), false);
    ASSERT_TRUE(right_end);
    EXPECT_EQ(7, right_end->value);
}

TEST(seek_end, returns_nullptr_on_empty) {

    TreeTest tt;
    node* left_end = tt.unit_seek_end(tt.unit_root());
    ASSERT_FALSE(left_end);

    node* right_end = tt.unit_seek_end(tt.unit_root(), false);
    ASSERT_FALSE(right_end);
}

TEST(erase, erase_root_correct_structure) {

    TreeTest tt = generate_tree();
    tt.erase(0);

    node* r = tt.unit_root();
    ASSERT_TRUE(r);
    EXPECT_EQ(4, r->value);
    EXPECT_EQ(4, tt.size());

}

TEST(erase, correct_structure) {

    TreeTest tt = generate_tree();
    tt.erase(4);

    node* r = tt.unit_root();
    ASSERT_TRUE(r->right);
    EXPECT_EQ(7, r->right->value);

    ASSERT_TRUE(r->right->left);
    EXPECT_EQ(3, r->right->left->value);

    ASSERT_FALSE(r->right->right);

    EXPECT_EQ(4, tt.size());

}

TEST(is_balanced, returns_false_left_case) {

    auto A = new node(0);
    A->left = new node(-1);
    A->left->left = new node(-2);

    TreeTest tt;
    EXPECT_FALSE(tt.unit_is_balanced(A));

    delete A->left->left;
    delete A->left;
    delete A;
}

TEST(is_balanced, returns_false_right_case) {

    auto A = new node(0);
    A->right = new node(1);
    A->right->right = new node(2);

    TreeTest tt;
    EXPECT_FALSE(tt.unit_is_balanced(A));

    delete A->right->right;
    delete A->right;
    delete A;
}

TEST(is_balanced, returns_true_case_one) {

    auto A = new node(0);
    A->right = new node(1);
    A->left = new node(-1);
    A->right->right = new node(3);

    TreeTest tt;
    EXPECT_TRUE(tt.unit_is_balanced(A));

    delete A->right->right;
    delete A->right;
    delete A->left;
    delete A;
}

TEST(is_balanced, returns_true_case_two) {

    auto A = new node(0);
    A->right = new node(1);
    A->right->right = new node(3);
    A->right->left = new node(-1);

    TreeTest tt;
    EXPECT_TRUE(tt.unit_is_balanced(A));

    delete A->right->right;
    delete A->right;
    delete A->left;
    delete A;
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

