#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "priority_queue_modified.h"
#include <iostream>
using std::cout;



TEST_CASE( "Testing enqueue", "[enqueue()]" ) {

    priority_queue_mod::priority_queue pq(0);
    pq.enqueue(1, 0);

    // add first element
    REQUIRE(pq.m_head->m_value == 1);
    REQUIRE(pq.m_head == pq.m_tail);
    REQUIRE(pq.m_priorityEndNodes.size() == 1);

    // add element with much higher priority
    pq.enqueue(2, 3);
    REQUIRE(pq.m_head->m_value == 1);
    REQUIRE(pq.m_tail->m_value == 2);
    REQUIRE(pq.m_tail->m_priority == 3);


    // add element with priority in-between of two previous
    pq.enqueue(10, 2);
    REQUIRE(pq.m_head->m_value == 1);
    REQUIRE(pq.m_tail->m_value == 2);
    REQUIRE(pq.m_head->m_next->m_value == 10);
    REQUIRE(pq.m_head->m_next->m_priority == 2);
    REQUIRE(pq.m_head->m_next->m_next == pq.m_tail);
}


TEST_CASE("Testing dequeue", "[dequeue()]") {

    SECTION("Deque empty") {
        // trying to dequeue already empty queue
        priority_queue_mod::priority_queue pq(0);
        REQUIRE(pq.dequeue() == 0);
        REQUIRE(pq.m_head == nullptr);
        REQUIRE(pq.m_tail == nullptr);
    }

    SECTION("Deque single element") {
        // dequeue-ing single element where m_head = m_tail
        priority_queue_mod::priority_queue pq(0);
        pq.enqueue(1, 1);
        REQUIRE(pq.dequeue() == 1);
        REQUIRE(pq.m_head == nullptr);
        REQUIRE(pq.m_tail == nullptr);
    }

    SECTION("Dequeue with several elements") {
        // regular dequeue-ing
        priority_queue_mod::priority_queue pq(0);
        pq.enqueue(1, 1);
        pq.enqueue(2, 2);

        REQUIRE(pq.dequeue() == 2);
        REQUIRE(pq.m_head->m_value == 1);
        REQUIRE(pq.m_tail->m_value == 1);
    }


}

