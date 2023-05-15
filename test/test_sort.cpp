#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include "sort.h"
using std::cout;


TEST_CASE("Sort_0", "[bubble_sort()]") {
    int a[] = {-19, 2, 3, -5, 8, 9};
    int b[] = {-19, -5, 2, 3, 8, 9};

    sort::bubble_sort(a, 6);
    for (auto i = 0; i < 6; i++)
        REQUIRE(a[i] == b[i]);
}

TEST_CASE("Sort_1", "[qsort()]") {
    int a[] = {-19, 2, 3, -5, 8, 9};
    int b[] = {-19, -5, 2, 3, 8, 9};

    sort::qsort(a, 6);
    for (auto i = 0; i < 6; i++)
        REQUIRE(a[i] == b[i]);
}

TEST_CASE("Sort_2", "[insertion_sort()]") {
    int a[] = {-19, 2, 3, -5, 8, 9};
    int b[] = {-19, -5, 2, 3, 8, 9};

    sort::insertion_sort(a, 6);
    for (auto i = 0; i < 6; i++)
        REQUIRE(a[i] == b[i]);
}

TEST_CASE("Sort_3", "[selection_sort()]") {
    int a[] = {-19, 2, 3, -5, 8, 9};
    int b[] = {-19, -5, 2, 3, 8, 9};

    sort::selection_sort(a, 6);
    for (auto i = 0; i < 6; i++)
        REQUIRE(a[i] == b[i]);
}

TEST_CASE("Sort_4", "[shaker_sort()]") {
    int a[] = {-19, 2, 3, -5, 8, 9};
    int b[] = {-19, -5, 2, 3, 8, 9};

    sort::shaker_sort(a, 6);
    for (auto i = 0; i < 6; i++)
        REQUIRE(a[i] == b[i]);
}

TEST_CASE("Sort_5", "[counting_sort()]") {
    int a[] = {-19, 2, 3, -5, 8, 9};
    int b[] = {-19, -5, 2, 3, 8, 9};

    sort::counting_sort(a, 6, 100);
    for (auto i = 0; i < 6; i++)
        REQUIRE(a[i] == b[i]);
}

TEST_CASE("Sort_6", "[merge_sort()]") {
    int a[] = {-19, 2, 3, -5, 8, 9};
    int b[] = {-19, -5, 2, 3, 8, 9};

    int* c = sort::merge_sort(a, 6);
    for (auto i = 0; i < 6; i++)
        REQUIRE(c[i] == b[i]);
}