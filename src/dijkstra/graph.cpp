
#include <iostream>
using std::cout;

#include "graph.h"

graph::~graph() {
    for(int i = 0; i < nodes.size(); i++)
        delete nodes[i];
}

node* graph::add(const string& name) {
    node* n = new node(name);
    nodes.emplace_back(n);
    return n;
}

int graph::run_dijkstra(node *start, node* end, string& path) {
    if (start == end)
        return 0;

    if (!start || !end)
        return 0;

    unordered_map<string, int> min_cost;

    node* cursor = start;
    node* next = nullptr;
    int next_weight = 0;
    int cost_spent_so_far = 0;

    path = cursor->name;

    while(cursor != end && cursor) {

        for (auto &edge: cursor->edges) {

            // Обновляем новые пути, обнаруживая новые ноды
            string name = edge->next->name;
            int new_path_cost = cost_spent_so_far + edge->weight;
            auto itr = min_cost.find(name);
            if (itr != min_cost.end()) {
                if (new_path_cost < itr->second)
                    itr->second = new_path_cost;
            } else
                min_cost[name] = new_path_cost;

            // Выбираем следующий node по принципу минимального edge
            if (!next) {
                next = edge->next;
                next_weight = edge->weight;
            } else {
                if (edge->weight < next_weight) {
                    next = edge->next;
                    next_weight = edge->weight;
                }
            }
        }

        cost_spent_so_far += next_weight;
        cursor = next;
        if (!cursor)
            return cost_spent_so_far;

        path += cursor->name;

        // Если можно было найти путь быстрее,
        // это будет отображено в map, находим и сравниваем с путем,
        // через который мы пришли
        if (min_cost[cursor->name] < cost_spent_so_far)
            cost_spent_so_far = min_cost[cursor->name];

        next_weight = 0;
        next = nullptr;
    }

    return cost_spent_so_far;
}




