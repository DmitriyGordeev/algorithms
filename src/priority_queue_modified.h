#ifndef ALGORITHMS_PRIORITY_QUEUE_H
#define ALGORITHMS_PRIORITY_QUEUE_H

#include <unordered_map>
#include <iostream>

// TODO: пояснить, что здесь не используется heap-struct
// TODO: обобщить на template

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
