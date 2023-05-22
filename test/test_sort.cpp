#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <iostream>
#include "sort.h"
using std::cout;


TEST_CASE("Sort_0", "[bubble_sort()]") {
    int a[] = {-19, 2, 3, -5, 8, 9};
    int b[] = {-19, -5, 2, 3, 8, 9};

    sort::bubble_sort(a, 6);

    cout << "bubble sort:\n";
    for (auto i = 0; i < 6; i++) {
        REQUIRE(a[i] == b[i]);
        cout << a[i] << ",";
    }
    cout << "\n";
}

TEST_CASE("Sort_1", "[qsort()]") {
    int a[] = {-19, 2, 3, -5, 8, 9};
    int b[] = {-19, -5, 2, 3, 8, 9};

    sort::qsort(a, 6);

    cout << "qsort result:\n";
    for (auto i = 0; i < 6; i++) {
        REQUIRE(a[i] == b[i]);
        cout << a[i] << ",";
    }
    cout << "\n";
}

TEST_CASE("Sort_2", "[insertion_sort()]") {
    int a[] = {-19, 2, 3, -5, 8, 9};
    int b[] = {-19, -5, 2, 3, 8, 9};

    sort::insertion_sort(a, 6);

    cout << "insertion sort result:\n";
    for (auto i = 0; i < 6; i++) {
        REQUIRE(a[i] == b[i]);
        cout << a[i] << ",";
    }
    cout << "\n";
}

TEST_CASE("Sort_3", "[selection_sort()]") {
    int a[] = {-19, 2, 3, -5, 8, 9};
    int b[] = {-19, -5, 2, 3, 8, 9};

    sort::selection_sort(a, 6);

    cout << "selection sort result:\n";
    for (auto i = 0; i < 6; i++) {
        REQUIRE(a[i] == b[i]);
        cout << a[i] << ",";
    }
    cout << "\n";
}

TEST_CASE("Sort_4", "[shaker_sort()]") {

    SECTION("random array") {
        int a[] = {-19, 2, 3, -5, 8, 9};
        int b[] = {-19, -5, 2, 3, 8, 9};

        sort::shaker_sort(a, 6);

        cout << "shaker sort result:\n";
        for (auto i = 0; i < 6; i++) {
            REQUIRE(a[i] == b[i]);
            cout << a[i] << ",";
        }
        cout << "\n";
    }

    SECTION("reversed") {
        int a[] = {3, 2, 1};
        int b[] = {1, 2, 3};

        sort::shaker_sort(a, 3);
        cout << "shaker sort:\n";
        for(int i = 0; i < 3; i++) {
            REQUIRE(a[i] == b[i]);
            cout << a[i] << ",";
        }
        cout << "\n";
    }

}

TEST_CASE("Sort_5", "[counting_sort()]") {

    SECTION("no repetitions") {
        int a[] = {-19, 2, 3, -5, 8, 9};
        int b[] = {-19, -5, 2, 3, 8, 9};

        sort::counting_sort(a, 6, -20, 10);

        cout << "counting sort:\n";
        for (auto i = 0; i < 6; i++) {
            REQUIRE(a[i] == b[i]);
            cout << a[i] << ",";
        }
        cout << "\n";
    }

    SECTION("repetitions") {
        int a[] = {1, -4, -3, -2, 1,-4};
        int b[] = {-4, -4, -3, -2, 1, 1};

        sort::counting_sort(a, 6, -10, 10);

        cout << "counting sort:\n";
        for (auto i = 0; i < 6; i++) {
            REQUIRE(a[i] == b[i]);
            cout << a[i] << ",";
        }
        cout << "\n";
    }
}

TEST_CASE("Sort_6", "[merge_sort()]") {

    SECTION("even size") {
        int a[] = {-19, 2, 3, -5, 8, 9};
        int b[] = {-19, -5, 2, 3, 8, 9};
        int* out = sort::merge_sort(a, 6);

        cout << "merge sort 1:\n";
        for (int i = 0; i < 6; i++) {
            REQUIRE(out[i] == b[i]);
            cout << out[i] << ",";
        }
        cout << "\n";
    }

    SECTION("odd size") {
        int a[] = {4, 3, 2};
        int b[] = {2, 3, 4};
        int* out = sort::merge_sort(a, 3);

        cout << "merge sort 2:\n";
        for (int i = 0; i < 3; i++) {
            REQUIRE(out[i] == b[i]);
            cout << out[i] << ",";
        }
        cout << "\n";
    }



    cout << "out";
}