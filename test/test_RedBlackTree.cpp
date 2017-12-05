#include <gtest/gtest.h>
#include <iostream>
#include "../src/RedBlackTree.h"

using namespace std;
using namespace rbtree;

class TestRB : public RedBlackTree
{
public:
    TestRB() : RedBlackTree() {}

    void unit_rotate(node* entry) {
        rotate(entry);
    }
};



TEST(bro, correct_value)
{
    TestRB trb;

    node* father = new node(0, COLOR::BLACK);
    father->left = new node(-1, COLOR::RED);
    father->left->parent = father;

    father->right = new node(1, COLOR::RED);
    father->right->parent = father;

    auto bro = father->left->bro();

    ASSERT_TRUE(bro);
    EXPECT_EQ(father->right, bro);
    EXPECT_EQ(father->right->value, bro->value);

}

TEST(rotate, correct_structure)
{
    TestRB t;

    node* grandfa = new node(0, COLOR::BLACK);
    node* father  = new node(-1, COLOR::RED);
    node* uncle   = new node(1, COLOR::RED);
    node* son     = new node(-2, COLOR::RED);

    grandfa->left = father; father->parent = grandfa;
    grandfa->right = uncle; uncle->parent = grandfa;
    father->left = son; son->parent = father;

    t.unit_rotate(son);

    EXPECT_EQ(COLOR::RED, son->color);
    EXPECT_EQ(COLOR::BLACK, father->color);
    EXPECT_EQ(COLOR::RED, grandfa->color);
    EXPECT_EQ(COLOR::BLACK, uncle->color);

    delete son;
    delete uncle;
    delete father;
    delete grandfa;
}






int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
