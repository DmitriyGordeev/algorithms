#ifndef ALGORITHMS_PRIORITY_QUEUE_H
#define ALGORITHMS_PRIORITY_QUEUE_H

#include <unordered_map>
#include <iostream>

// This is a priority queue version different from classic priority_queue which based on heap,
// this structure is based on double linked list, and useful when max amount of possible priorities is relatively low
// compared to the number of elements in queue.
// This structure stores hash table of entries <priority -> node*> which allows to extract
// the last element in queue for previous lower priority and append new element with given priority to it

namespace priority_queue_mod {

    struct node {
        node() = default;
        node(int value, node* next, node* prev, int priority) :
            m_value(value), m_next(next), m_prev(prev), m_priority(priority) {}

        virtual ~node() {
            std::cout << "node(" << m_value << ", " << m_priority <<") destroyed\n";
        }

        int m_value {0};
        node* m_next {nullptr};
        node* m_prev {nullptr};
        int m_priority {0};
    };

    class priority_queue {
    public:
        priority_queue(int max_priority);
        virtual ~priority_queue();

        node* enqueue(int value, int priority);
        int dequeue();

    public: // todo: protected
        node* m_head {nullptr};
        node* m_tail {nullptr};
        int m_maxPriority {0};
        std::unordered_map<int, node*> m_priorityEndNodes;
    };
}


#endif //ALGORITHMS_PRIORITY_QUEUE_H
