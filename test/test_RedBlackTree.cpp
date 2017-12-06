#include <gtest/gtest.h>
#include <iostream>
#include "../src/RedBlackTree.h"

using namespace std;
using namespace rbtree;

class TestRB : public RedBlackTree
{
public:
    TestRB() : RedBlackTree() {}

    void unit_resolve_red_red(node* entry) {
        resolve_red_red(entry);
    }

    static void unit_rotate_left(node* node) {
        rotate_left(node);
    }

    static void unit_rotate_right(node* node) {
        rotate_right(node);
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

TEST(resolve_red_red, correct_structure)
{
    TestRB t;

    node* grandfa = new node(0, COLOR::BLACK);
    node* father  = new node(-1, COLOR::RED);
    node* uncle   = new node(1, COLOR::RED);
    node* son     = new node(-2, COLOR::RED);

    grandfa->left = father; father->parent = grandfa;
    grandfa->right = uncle; uncle->parent = grandfa;
    father->left = son; son->parent = father;

    t.unit_resolve_red_red(son);

    EXPECT_EQ(COLOR::RED, son->color);
    EXPECT_EQ(COLOR::BLACK, father->color);
    EXPECT_EQ(COLOR::RED, grandfa->color);
    EXPECT_EQ(COLOR::BLACK, uncle->color);

    delete son;
    delete uncle;
    delete father;
    delete grandfa;
}

TEST(rotate_left, correct)
{
    node* R = new node(100, COLOR::BLACK);
    node* A = new node(10, COLOR::BLACK);
    node* B = new node(5, COLOR::BLACK);
    node* C = new node(15, COLOR::BLACK);

    node* S1 = new node(3, COLOR::BLACK);
    node* S2 = new node(6, COLOR::BLACK);
    node* S3 = new node(11, COLOR::BLACK);
    node* S4 = new node(18, COLOR::BLACK);

    R->left = A; A->parent = R;
    A->left = B; B->parent = A;
    A->right = C; C->parent = A;
    B->left = S1; S1->parent = B;
    B->right = S2; S2->parent = B;
    C->left = S3; S3->parent = C;
    C->right = S4; S4->parent = C;

    TestRB::unit_rotate_left(A);

    EXPECT_EQ(C, R->left);
    EXPECT_EQ(S1, B->left);
    EXPECT_EQ(A, C->left);
    EXPECT_EQ(S2, B->right);
    EXPECT_EQ(B, A->left);
    EXPECT_EQ(S3, A->right);
    EXPECT_EQ(S4, C->right);


    delete S4; delete S3; delete S2; delete S1;
    delete B; delete C;
    delete A;
    delete R;
}

TEST(rotate_right, correct)
{
    node* R = new node(100, COLOR::BLACK);
    node* A = new node(10, COLOR::BLACK);
    node* B = new node(5, COLOR::BLACK);
    node* C = new node(15, COLOR::BLACK);

    node* S1 = new node(3, COLOR::BLACK);
    node* S2 = new node(6, COLOR::BLACK);
    node* S3 = new node(11, COLOR::BLACK);
    node* S4 = new node(18, COLOR::BLACK);

    R->left = A; A->parent = R;
    A->left = B; B->parent = A;
    A->right = C; C->parent = A;
    B->left = S1; S1->parent = B;
    B->right = S2; S2->parent = B;
    C->left = S3; S3->parent = C;
    C->right = S4; S4->parent = C;

    TestRB::unit_rotate_right(A);

    EXPECT_EQ(B, R->left);
    EXPECT_EQ(S1, B->left);
    EXPECT_EQ(A, B->right);
    EXPECT_EQ(S2, A->left);
    EXPECT_EQ(C, A->right);
    EXPECT_EQ(S3, C->left);
    EXPECT_EQ(S4, C->right);


    delete S4; delete S3; delete S2; delete S1;
    delete B; delete C;
    delete A;
    delete R;
}


// TODO: add more tests


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
