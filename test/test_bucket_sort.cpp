#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "bucket_sort.h"
#include <iostream>
#include <set>
using std::cout;
using std::set;


// TODO: readme

// Testing class around bucket_sort with extra function for testing only
class test_bucket_sort: public bucket_sort {
public:
    test_bucket_sort(size_t max_bucket_size = 3) : bucket_sort(max_bucket_size) {}

    void fill_bucket_1() {
        set<int> s;
        s.insert(-500);
        m_buckets.push_back(std::move(s));
    }

    void fill_bucket_2() {
        set<int> s;
        s.insert(-500);
        m_buckets.push_back(std::move(s));

        s.clear();
        s.insert(2);
        m_buckets.push_back(std::move(s));
    }

    void fill_bucket_3() {
        set<int> s;
        s.insert(-500);
        m_buckets.push_back(std::move(s));

        s.clear();
        s.insert(1);
        s.insert(3);
        m_buckets.push_back(std::move(s));
    }

    void fill_bucket_4() {
        set<int> s;
        s.insert(-500);
        m_buckets.push_back(std::move(s));

        s.clear();
        s.insert(0);
        s.insert(2);
        s.insert(3);
        m_buckets.push_back(std::move(s));
    }
};



TEST_CASE( "bucket_sort", "[find_bucket()]" ) {

    SECTION("one bucket") {
        test_bucket_sort bsort;
        bsort.fill_bucket_1();
        REQUIRE(bsort.find_bucket(1) == 0);
    }

    SECTION("two unfilled buckets") {
        test_bucket_sort bsort;
        bsort.fill_bucket_2();
        REQUIRE(bsort.find_bucket(1) == 1);
    }

    SECTION("two unfilled buckets 2") {
        test_bucket_sort bsort;
        bsort.fill_bucket_3();
        REQUIRE(bsort.find_bucket(2) == 1);
    }

    SECTION("one bucket is filled") {
        test_bucket_sort bsort;
        bsort.fill_bucket_4();
        REQUIRE(bsort.find_bucket(4) == 2);
    }

    SECTION("split bucket") {
        test_bucket_sort bsort;
        bsort.fill_bucket_4();
        bsort.add_split_bucket(1, 1);
    }
}


TEST_CASE( "bucket_sort, add", "[add()]" ) {
    test_bucket_sort bsort;
    bsort.add(-500);
    bsort.add(0);
    bsort.add(1);
    bsort.add(3);

    int a = 1000;
}