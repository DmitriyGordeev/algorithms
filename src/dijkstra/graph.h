#ifndef ALGORITHMS_GRAPH_H
#define ALGORITHMS_GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
using std::string;
using std::vector;
using std::unordered_map;

struct node;

struct edge {
    edge(node* n, int w): next(n), weight(w) {}

    node* next {nullptr};
    int weight {0};

};


struct node {
    node(const string& n): name(n) {}

    edge* add(node* next, int weight) {
        if (!next || weight == 0)
            return nullptr;

        edge* out = new edge(next, weight);
        edges.push_back(out);
        return out;
    }

    ~node() {
        for(int i = 0; i < edges.size(); i++)
            delete edges[i];
    }

    string name;

    // TODO: поменять на priority queue
    vector<edge*> edges;
};



class graph {
public:

    node* add(const string& name);

    virtual ~graph();

    int run_dijkstra(node* start, node* end, string& path);

#ifdef TEST
public:
#else
protected:
#endif

    vector<node*> nodes;

};


#endif //ALGORITHMS_GRAPH_H
