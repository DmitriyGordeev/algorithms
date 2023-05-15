#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "avltree.h"
#include <iostream>
using std::cout;


TEST_CASE( "AVLTREE_0", "[add()]" ) {

    SECTION("rotation check: root->left->left ") {
        avl::avltree tree;
        tree.add(8);
        tree.add(4);
        tree.add(3);

        auto root = tree.get_root();
        REQUIRE(root->value == 4);
        REQUIRE(root->parent == nullptr);
        REQUIRE(root->h_left == 1);
        REQUIRE(root->h_right == 1);

        auto left = root->left;
        REQUIRE(left->value== 3);
        REQUIRE(left->parent == root);
        REQUIRE(left->left == nullptr);
        REQUIRE(left->right == nullptr);
        REQUIRE(left->h_left == 0);
        REQUIRE(left->h_right == 0);

        auto right = root->right;
        REQUIRE(right->value== 8);
        REQUIRE(right->parent == root);
        REQUIRE(right->left == nullptr);
        REQUIRE(right->right == nullptr);
        REQUIRE(right->h_left == 0);
        REQUIRE(right->h_right == 0);
    }


    SECTION("rotation check: root->left->right ") {
        avl::avltree tree;
        tree.add(8);
        tree.add(4);
        tree.add(5);

        auto root = tree.get_root();
        REQUIRE(root->value == 5);
        REQUIRE(root->parent == nullptr);
        REQUIRE(root->h_left == 1);
        REQUIRE(root->h_right == 1);

        auto left = root->left;
        REQUIRE(left->value== 4);
        REQUIRE(left->parent == root);
        REQUIRE(left->left == nullptr);
        REQUIRE(left->right == nullptr);
        REQUIRE(left->h_left == 0);
        REQUIRE(left->h_right == 0);

        auto right = root->right;
        REQUIRE(right->value== 8);
        REQUIRE(right->parent == root);
        REQUIRE(right->left == nullptr);
        REQUIRE(right->right == nullptr);
        REQUIRE(right->h_left == 0);
        REQUIRE(right->h_right == 0);
    }


    SECTION("rotation check: root->right->right ") {
        avl::avltree tree;
        tree.add(0);
        tree.add(1);
        tree.add(2);

        auto root = tree.get_root();
        REQUIRE(root->value == 1);
        REQUIRE(root->parent == nullptr);
        REQUIRE(root->h_left == 1);
        REQUIRE(root->h_right == 1);

        auto left = root->left;
        REQUIRE(left->value== 0);
        REQUIRE(left->parent == root);
        REQUIRE(left->left == nullptr);
        REQUIRE(left->right == nullptr);
        REQUIRE(left->h_left == 0);
        REQUIRE(left->h_right == 0);

        auto right = root->right;
        REQUIRE(right->value== 2);
        REQUIRE(right->parent == root);
        REQUIRE(right->left == nullptr);
        REQUIRE(right->right == nullptr);
        REQUIRE(right->h_left == 0);
        REQUIRE(right->h_right == 0);
    }


    SECTION("rotation check: root->right->left ") {
        avl::avltree tree;
        tree.add(0);
        tree.add(2);
        tree.add(1);

        auto root = tree.get_root();
        REQUIRE(root->value == 1);
        REQUIRE(root->parent == nullptr);
        REQUIRE(root->h_left == 1);
        REQUIRE(root->h_right == 1);

        auto left = root->left;
        REQUIRE(left->value== 0);
        REQUIRE(left->parent == root);
        REQUIRE(left->left == nullptr);
        REQUIRE(left->right == nullptr);
        REQUIRE(left->h_left == 0);
        REQUIRE(left->h_right == 0);

        auto right = root->right;
        REQUIRE(right->value== 2);
        REQUIRE(right->parent == root);
        REQUIRE(right->left == nullptr);
        REQUIRE(right->right == nullptr);
        REQUIRE(right->h_left == 0);
        REQUIRE(right->h_right == 0);
    }

}

TEST_CASE("AVLTREE_1", "[simple tree]") {

    SECTION("manual add()") {
        avl::avltree tree;
        tree.add(0);
        tree.add(-1);
        tree.add(1);
        tree.add(-2);
        tree.add(2);
        tree.add(3);

        REQUIRE( tree.size() == 6 );

        auto root = tree.get_root();
        REQUIRE( root->value == 0 );
        REQUIRE( root->h_left == 2 );
        REQUIRE( root->h_right == 2 );
        REQUIRE( root->parent == nullptr );

        auto l = root->left;
        REQUIRE( l->value == -1 );
        REQUIRE( l->h_left == 1 );
        REQUIRE( l->h_right == 0 );
        REQUIRE( l->parent == root );
        REQUIRE( l->left->value == -2 );
        REQUIRE( l->left->parent == l );

        auto r = root->right;
        REQUIRE( r->value == 2 );
        REQUIRE( r->h_left == 1 );
        REQUIRE( r->h_right == 1 );
        REQUIRE( r->parent == root );
        REQUIRE( r->left->value == 1 );
        REQUIRE( r->left->parent == r );
        REQUIRE( r->right->value == 3 );
        REQUIRE( r->right->parent == r );
    }

    SECTION("feeding increasing values - test against degradation to a list") {
        avl::avltree tree;
        for(auto i = 0; i < 5; i++)
            tree.add(i);

        auto root = tree.get_root();
        REQUIRE(root->value == 1);
        REQUIRE(root->parent == nullptr);

        auto left = root->left;
        REQUIRE(left->value == 0);
        REQUIRE(left->parent == root);
        REQUIRE(left->left == nullptr);
        REQUIRE(left->right == nullptr);

        auto right = root->right;
        REQUIRE(right->value == 3);
        REQUIRE(right->parent == root);
        REQUIRE(right->left->value == 2);
        REQUIRE(right->left->parent == right);
        REQUIRE(right->right->value == 4);
        REQUIRE(right->right->parent == right);
    }

}

TEST_CASE("AVLTREE_2", "[avl node]") {
    auto root = new avl::node(0);
    auto l0 = new avl::node(-10);
    auto l1 = new avl::node(-15);
    auto r1 = new avl::node(-2);


    root->left = l0; l0->parent = root;
    l0->left = l1; l1->parent = l0;
    l0->right = r1; r1->parent = l0;


    auto l = root->find_lowest();
    auto r = root->find_highest();
    auto rl = l0->find_highest();
}


TEST_CASE("AVL NODE", "[recalculate_heights]") {

    auto root = new avl::node(0);
    auto l1 = new avl::node(-10);
    auto l2 = new avl::node(-20);
    auto r1 = new avl::node(20);

    root->left = l1;    l1->parent = root;
    root->left->left = l2;  l2->parent = l1;
    root->right = r1;   r1->parent = root;

    l2->recalculate_heights();
    r1->recalculate_heights();

    REQUIRE(root->h_left == 2);
    REQUIRE(root->h_right == 1);
}


TEST_CASE("AVLTREE_3", "[erase]") {

    SECTION("erase on an empty tree") {
        avl::avltree tree;
        REQUIRE(tree.erase(0) == false);
    }


    SECTION("erase on non-exisiting value") {
        avl::avltree tree;
        tree.add(0);
        tree.add(-10);
        tree.add(10);

        REQUIRE(tree.erase(-100) == false);
        REQUIRE(tree.erase(100) == false);
    }


    SECTION("equal non-zero heights") {
        avl::avltree tree;
        tree.add(0);
        tree.add(-15);
        tree.add(20);
        tree.add(-20);
        tree.add(10);
        tree.add(30);

        REQUIRE(tree.erase(0) == true);

        auto root = tree.get_root();
        REQUIRE(root->value == -15);
        REQUIRE(root->h_left == 1);
        REQUIRE(root->h_right == 2);

        REQUIRE(root->left->value == -20);
        REQUIRE(root->left->parent == root);

        REQUIRE(root->right->value == 20);
        REQUIRE(root->right->parent == root);
        REQUIRE(root->right->h_left == 1);
        REQUIRE(root->right->h_right == 1);

        REQUIRE(root->right->left->value == 10);
        REQUIRE(root->right->left->parent == root->right);

        REQUIRE(root->right->right->value == 30);
        REQUIRE(root->right->right->parent == root->right);

        REQUIRE(tree.size() == 6);
    }

    SECTION("right subtree is higher") {
        avl::avltree tree;
        tree.add(0);
        tree.add(-15);
        tree.add(20);
        tree.add(-20);
        tree.add(10);
        tree.add(30);
        tree.add(15);

        REQUIRE(tree.erase(0) == true);

        auto root = tree.get_root();
        REQUIRE(root->value == 10);
        REQUIRE(root->h_left == 2);
        REQUIRE(root->h_right == 2);

        REQUIRE(root->left->value == -15);
        REQUIRE(root->left->parent == root);
        REQUIRE(root->left->left->value == -20);
        REQUIRE(root->left->left->parent == root->left);

        REQUIRE(root->right->value == 20);
        REQUIRE(root->right->parent == root);
        REQUIRE(root->right->left->value == 15);
        REQUIRE(root->right->left->parent == root->right);
        REQUIRE(root->right->right->value == 30);
        REQUIRE(root->right->right->parent == root->right);

        REQUIRE(tree.size() == 7);
    }

}


TEST_CASE("AVL_TREE4", "[get]") {
    avl::avltree tree;
    REQUIRE(tree.get(0) == nullptr);

    tree.add(0);
    REQUIRE(tree.get(0) == tree.get_root());

    tree.add(10);
    tree.add(-10);

    auto A = tree.get(10);
    REQUIRE(A->value == 10);
    REQUIRE(A->parent == tree.get_root());

    auto B = tree.get(-10);
    REQUIRE(B->value == -10);
    REQUIRE(B->parent == tree.get_root());
}


TEST_CASE("AVL_TREE5", "[deallocation]") {


    SECTION("empty tree") {
        avl::avltree tree;
    }

    SECTION("single element") {
        avl::avltree tree;
        tree.add(10);
    }

}