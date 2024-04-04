#include <iostream>
#include <unordered_map>
#include <utility>
#include <ostream>
#pragma once
using namespace std;

namespace graph{

    template <typename Key, typename Value, typename Weight>
    class Graph {
    public:

        typedef Key key_type;
        typedef Value value_type;
        typedef Weight weight_type;
        class Node;
        typedef typename unordered_map<key_type, Node>::iterator iterator;
        typedef typename unordered_map<key_type, Node>::const_iterator const_iterator;

        Graph();
        Graph(const Graph &other);
        Graph(Graph &&other);

        Graph& operator=(const Graph &copy);
        Graph& operator=(Graph &&moved);
        value_type& operator[](key_type k) const;

        bool empty();
        size_t size();
        void clear();

        iterator begin();
        const_iterator cbegin();
        iterator end();
        const_iterator cend();

        void swap(Graph &graph2);

        template <typename Key2, typename Value2, typename Weight2>
        friend void swap(Graph<Key2, Value2, Weight2> &g1, Graph<Key2, Value2, Weight2> &g2);

        value_type& at(key_type k);
        size_t degree_in(key_type k);
        size_t degree_out(key_type k);
        bool loop(key_type k);

        std::pair<Graph::iterator, bool> insert_node(key_type k, value_type v);
        std::pair<Graph::iterator, bool> insert_or_assign_node(key_type k, value_type v);
        pair<typename Graph<Key, Value, Weight>::Node::iterator, bool> insert_edge(std::initializer_list<key_type> keys_from_to, weight_type W);
        pair<typename Graph<Key, Value, Weight>::Node::iterator, bool> insert_or_assign_edge(std::initializer_list<key_type> keys_from_to, weight_type W);

        void view();
        size_t delete_node(key_type k);
        void RenderDot(std::ostream& out);


    private:
        unordered_map<key_type, Node> vertices;
    };



    template <typename Key, typename Value, typename Weight>
    class Graph<Key, Value, Weight>::Node{
    private:
        friend Graph;
        value_type values = 0;
        unordered_map<Key, Weight> edges;

    public:
        Node();
        Node(value_type);
        Node(const Node &other);
        Node(Node &&other);

        Node& operator=(const Node &copy);
        Node& operator=(Node &&moved);

        bool empty();
        size_t size();
        value_type& value();
        const value_type& value() const;
        void clear();

        typedef typename unordered_map<key_type, weight_type>::iterator iterator;
        typedef typename unordered_map<key_type, weight_type>::const_iterator const_iterator;

        iterator begin();
        const_iterator cbegin();
        iterator end();
        const_iterator cend();
    };
};

#include "Graph.hpp"
