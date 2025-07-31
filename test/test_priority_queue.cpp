#include "priority_queue.h"
#include <acutest.h>

void test_Node_find_rec() {
    Node* A = new Node(10);
    Node* B = new Node(20);
    Node* C = new Node(30);
    Node* D = new Node(40);
    Node* E = new Node(50);
    Node* F = new Node(60);

    A->l_child = B;
    A->r_child = C;

    B->l_child = D;
    B->r_child = E;

    C->r_child = F;


    Node* r = A->find_rec(50);
    TEST_ASSERT(r != nullptr);
    TEST_ASSERT(r->value == 50);

    delete F;
    delete E;
    delete D;
    delete C;
    delete B;
    delete A;
}


void test_find() {
    PriorityQueue pq;

    pq._root = new Node(0);
    auto r1 = pq.find(0);
    TEST_ASSERT(r1 != nullptr);
    TEST_ASSERT(r1->value == 0);

    auto r2 = pq.find(10);
    TEST_ASSERT(r2 == nullptr);
}


void test_Node_add_rec_root_empty() {

    Node* A = new Node(0);
    Node* B = A->add_rec(10);
    Node* C = A->add_rec(20);
    Node* D = A->add_rec(30);
    Node* E = A->add_rec(40);
    Node* F = A->add_rec(50);

    TEST_ASSERT(A->dl == 3);
    TEST_ASSERT(A->dr == 2);

    TEST_ASSERT(B != nullptr);
    TEST_ASSERT(B->parent = A);

    TEST_ASSERT(C != nullptr);
    TEST_ASSERT(C->parent = B);

    TEST_ASSERT(D != nullptr);
    TEST_ASSERT(D->parent = A);

    TEST_ASSERT(E != nullptr);
    TEST_ASSERT(E->parent = C);

    TEST_ASSERT(F != nullptr);
    TEST_ASSERT(F->parent = D);

    delete A->l_child;
    delete A;
}


void test_Node_swap_up_CASE1() {
    Node* A = new Node(19);
    A->l_child = new Node(30);
    A->l_child->parent = A;
    A->l_child->l_child = new Node(25);
    A->l_child->l_child->parent = A->l_child;

    Node* B = A->l_child->l_child->swap_up_rec();
    TEST_ASSERT(B->value == 25);
    TEST_ASSERT(B == A->l_child);
}

void test_Node_swap_up_CASE2() {
    Node* A = new Node(100);
    A->l_child = new Node(30);
    A->l_child->parent = A;
    A->l_child->l_child = new Node(25);
    A->l_child->l_child->parent = A->l_child;

    Node* B = A->l_child->l_child->swap_up_rec();
    TEST_ASSERT(B->value == 25);
    TEST_ASSERT(B == A);
}


void test_PriorityQueue_add() {
    PriorityQueue pq;
    Node* A = pq.add(10);
    TEST_ASSERT(A == pq._root);
    TEST_ASSERT(pq._root->value == 10);

    Node* B = pq.add(20);
    TEST_ASSERT(B != nullptr);
    TEST_ASSERT(B->value == 20);
    TEST_ASSERT(A->l_child == B);
    TEST_ASSERT(B->parent == A);

    Node* C = pq.add(12);
    TEST_ASSERT(C != nullptr);
    TEST_ASSERT(C->value == 20);
    TEST_ASSERT(C->parent->value == 12);

    Node* E = pq.add(7);
    TEST_ASSERT(E != nullptr);
    TEST_ASSERT(E->value == 10);
    TEST_ASSERT(pq._root->value == 7);
}


void test_Node_find_root_replacement_rec() {
    Node* A = new Node(0);
    Node* B = A->add_rec(10);
    Node* C = A->add_rec(20);
    Node* D = A->add_rec(30);
    Node* E = A->add_rec(40);
    Node* F = A->add_rec(50);
    Node* G = A->add_rec(60);

    Node* X = A->find_root_replacement_rec();
    TEST_ASSERT(X->value == 40);
    TEST_ASSERT(X->l_child == nullptr);
    TEST_ASSERT(X->r_child == nullptr);
}


void test_Node_swap_down_rec_ShouldChooseLeftPath() {
    Node* A = new Node(100);
    Node* B = A->add_rec(10);
    Node* C = A->add_rec(20);
    Node* D = A->add_rec(30);
    Node* E = A->add_rec(80);
    Node* F = A->add_rec(50);
    Node* G = A->add_rec(60);

    Node* X = A->swap_down_rec();

    TEST_ASSERT(X != nullptr);
    TEST_ASSERT(X->parent->value == 80);
    TEST_ASSERT(X->l_child == nullptr);
    TEST_ASSERT(X->r_child == nullptr);
}

void test_Node_swap_down_rec_ShouldChooseRightPath() {
    Node* A = new Node(100);
    Node* B = A->add_rec(10);
    Node* C = A->add_rec(20);
    Node* D = A->add_rec(8);
    Node* E = A->add_rec(80);
    Node* F = A->add_rec(5);
    Node* G = A->add_rec(60);

    Node* X = A->swap_down_rec();
//    Node* Y = X->parent->swap_up_rec();

    TEST_ASSERT(X != nullptr);
    TEST_ASSERT(X->parent->value == 5);
    TEST_ASSERT(X->l_child == nullptr);
    TEST_ASSERT(X->r_child == nullptr);
}


void test_PriorityQueue_remove() {
    PriorityQueue pq;
    pq.add(7);
    pq.add(10);
    pq.add(8);
    pq.add(20);
    pq.add(60);
    pq.add(80);

    pq.remove();

    TEST_ASSERT(pq._root->value == 8);
    TEST_ASSERT(pq._root->l_child->value == 10);
    TEST_ASSERT(pq._root->l_child->l_child->value == 60);
    TEST_ASSERT(pq._root->r_child->value == 20);
    TEST_ASSERT(pq._root->r_child->l_child->value == 80);
}


TEST_LIST = {
        { "Node_find_rec", test_Node_find_rec },
        { "find", test_find },
        { "Node_add_rec", test_Node_add_rec_root_empty },
        { "test_Node_swap_up_CASE1", test_Node_swap_up_CASE1 },
        { "test_Node_swap_up_CASE2", test_Node_swap_up_CASE2 },
        { "test_PriorityQueue_add", test_PriorityQueue_add },
        { "test_Node_find_root_replacement_rec", test_Node_find_root_replacement_rec },
        { "test_Node_swap_down_rec_ShouldChooseLeftPath", test_Node_swap_down_rec_ShouldChooseLeftPath },
        { "test_Node_swap_down_rec_ShouldChooseRightPath", test_Node_swap_down_rec_ShouldChooseRightPath },
        { "test_PriorityQueue_remove", test_PriorityQueue_remove },

        { NULL, NULL }     /* zeroed record marking the end of the list */
};