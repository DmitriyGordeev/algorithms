#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "bstree.h"
#include <iostream>
using std::cout;


TEST_CASE( "BSTREE_0", "[add()]" ) {

    bst::bstree tree;
    REQUIRE(tree.size() == 0);

    tree.add(0);
    tree.add(-1);
    tree.add(1);
    REQUIRE(tree.size() == 3);

    auto root = tree.get_root();

    REQUIRE(root->value == 0);
    REQUIRE(root->parent == nullptr);
    REQUIRE(root->left->value == -1);
    REQUIRE(root->left->parent == root);
    REQUIRE(root->right->value == 1);
    REQUIRE(root->right->parent == root);
}


TEST_CASE( "BSTREE_1", "[get()]" ) {
    bst::bstree tree;
    auto n = tree.get(0);
    REQUIRE(n == nullptr);

    tree.add(0);
    tree.add(-1);

    n = tree.get(-1);
    REQUIRE(n->value == -1);
    REQUIRE(n->parent == tree.get_root());
}


TEST_CASE( "BSTREE_2", "[erase()]" ) {

    SECTION("erase empty tree") {
        bst::bstree tree;
        auto n = tree.erase(0);
        REQUIRE(n == nullptr);
    }

    SECTION("erase one of the leafs") {
        bst::bstree tree;
        tree.add(0);
        tree.add(-1);
        tree.add(1);

        auto n = tree.erase(1);     // substitute with parent node
        REQUIRE(n != nullptr);
        REQUIRE(n->value == 0);
        REQUIRE(n == tree.get_root());
    }

    SECTION("erase root") {
        bst::bstree tree;
        tree.add(0);
        tree.add(-1);
        tree.add(1);

        auto n = tree.erase(0);
        REQUIRE(n != nullptr);
        REQUIRE(n->value == 1);
        REQUIRE(n->parent == nullptr);
        REQUIRE(n->left->value == -1);
    }
}


TEST_CASE( "BSTREE_3", "[iterator]" ) {

    bst::bstree tree;
    tree.add(0);
    tree.add(-1);
    tree.add(1);
    tree.add(2);
    tree.add(-3);

    SECTION("simple comparison with the expected order") {
        int expected[] = {-3, -1, 0, 1, 2};
        int index = 0;
        for (auto v : tree)
            REQUIRE(v.value == expected[index++]);
    }

    SECTION("check values of begin() and end()") {
        REQUIRE(tree.begin() != nullptr);
        REQUIRE(tree.begin()->value == -3);

        REQUIRE(tree.end() == nullptr); // marks the end
    }

}