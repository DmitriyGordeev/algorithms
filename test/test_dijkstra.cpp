#include <iostream>
#include "graph.h"
#include <acutest.h>
#include <queue>
#include <iostream>

void test_creation() {
    graph g;
    node* A = g.add("A");
    node* B = g.add("B");

    TEST_ASSERT(A != nullptr);
    TEST_ASSERT(B != nullptr);
    TEST_ASSERT(g.nodes.size() == 2);
}

void test_graph_simple_run() {
    graph g;
    node* A = g.add("A");
    node* C = g.add("C");
    node* F = g.add("F");
    node* E = g.add("E");
    node* D = g.add("D");
    node* G = g.add("G");
    node* B = g.add("B");

    A->add(F, 2);
    A->add(C, 3);

    F->add(C, 2);
    F->add(E, 3);
    F->add(B, 6);
    F->add(G, 5);

    E->add(B, 2);

    C->add(E, 1);
    C->add(D, 4);

    G->add(B, 2);
    D->add(B, 1);

    string path;
    int cost = g.run_dijkstra(A, B, path);

    TEST_ASSERT(cost == 6);
    TEST_ASSERT(path == "AFCEB");
}


void test_priority_queue() {
    std::priority_queue<int> pq;
    pq.push(19);
    pq.push(1);
    pq.push(200);
    pq.push(34);

    while (!pq.empty()) {
        std::cout << pq.top() << std::endl;
        pq.pop();
    }
}


TEST_LIST = {
        { "test_creation", test_creation },
        { "test_graph_simple_run", test_graph_simple_run },
        { "test_priority_queue", test_priority_queue },
        { NULL, NULL }     /* zeroed record marking the end of the list */
};