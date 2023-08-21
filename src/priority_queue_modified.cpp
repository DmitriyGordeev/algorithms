#include "priority_queue_modified.h"

namespace priority_queue_mod {
    priority_queue::priority_queue(int max_priority) : m_maxPriority(max_priority) {}

    priority_queue::~priority_queue() {
        // todo
    }

    node* priority_queue::enqueue(int value, int priority) {
        if (!m_head) {
            m_head = new node(value, nullptr, priority);
            m_tail = m_head;
            m_priorityEndNodes[priority] = m_head;
            return m_head;
        }

        // if priority is higher than so far added into queue, append new element to the tail,
        // update tail and priority map
        if (priority > m_tail->m_priority) {
            m_tail->m_next = new node(value, nullptr, priority);
            m_tail = m_tail->m_next;
            m_priorityEndNodes[priority] = m_tail;
            return m_tail;
        }

        // search for previous node with the lower priority
        int next_lower_priority = priority - 1;
        while(m_priorityEndNodes.find(next_lower_priority) == m_priorityEndNodes.end()) {
            next_lower_priority--;
            if (next_lower_priority < 0)
                break;
        }

        if (next_lower_priority < 0) {
            // todo: не будет работать с отрицательными priority-значениями
            // current priority is the lowest we've added so far,
            // replace head with this value
            node* new_element = new node(value, m_head, priority);
            m_head = new_element;
            m_priorityEndNodes[priority] = m_head;
            return m_head;
        }
        else {
            auto prev_node = m_priorityEndNodes[next_lower_priority];
            node* new_element = new node(value, prev_node->m_next, priority);
            prev_node->m_next = new_element;
            return new_element;
        }
    }

    void priority_queue::dequeue() {}
}