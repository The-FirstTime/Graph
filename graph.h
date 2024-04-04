//
// Created by Арсений  Ростовщиков on 11.02.2024.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#endif //GRAPH_GRAPH_H

#include <unordered_map>
#include <iostream>

namespace graph{
    template<typename key_type, typename value_type, typename weight_type>
    class Graph{
    public:
        key_type key;
        value_type value;
        weight_type weight;

        class Node{
        public:
            value_type value;
            std::unordered_map<key_type, weight_type> edges;
        };

        void addNode(const key_type& key, const value_type& value)
        {
            nodes[key] = Node{value};
        }

        void addEdge(const key_type& from, const key_type& to, const weight_type& weight)
        {
            nodes[from].edges[to] = weight;
        }

    private:
        std::unordered_map<key_type, Node> nodes;
    };
}

