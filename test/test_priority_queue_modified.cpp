#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "priority_queue_modified.h"
#include <iostream>
using std::cout;



TEST_CASE( "Testing enque", "[enqueue()]" ) {

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
