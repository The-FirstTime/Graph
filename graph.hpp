#include "Graph.h"

namespace graph{

    //++++++++++++++++++++++++++++++       NODE       ++++++++++++++++++++++++++++++++//

//constructors

    template <typename Key, typename Value, typename Weight>
    Graph<Key, Value, Weight>::Node::Node() = default;

    template <typename Key, typename Value, typename Weight>
    Graph<Key, Value, Weight>::Node::Node(value_type val){
        values = val;
    };

    template <typename Key, typename Value, typename Weight>
    Graph<Key, Value, Weight>::Node::Node(const Node &other){
        values = other.values;
        edges = other.edges;
    }

    template <typename Key, typename Value, typename Weight>
    Graph<Key, Value, Weight>::Node::Node(Node &&other){
        values = other.values;
        edges = other.edges;
        other.clear();
    }


//methods

    template <typename Key, typename Value, typename Weight>
    bool Graph<Key, Value, Weight>::Node::empty(){
        return edges.empty();
    }

    template <typename Key, typename Value, typename Weight>
    size_t Graph<Key, Value, Weight>::Node::size(){
        return edges.size();
    }

    template <typename Key, typename Value, typename Weight>
    Value& Graph<Key, Value, Weight>::Node::value(){
        return values;
    }

    template <typename Key, typename Value, typename Weight>
    const Value& Graph<Key, Value, Weight>::Node::value() const{
        return values;
    }

    template <typename Key, typename Value, typename Weight>
    void Graph<Key, Value, Weight>::Node::clear(){
        edges.clear();
        values = 0;
    }


//operators

    template <typename Key, typename Value, typename Weight>
    typename Graph<Key, Value, Weight>::Node& Graph<Key, Value, Weight>::Node::operator=(const Node &copy){
        values = copy.values;
        edges = copy.edges;
        return *this;
    }

    template <typename Key, typename Value, typename Weight>
    typename Graph<Key, Value, Weight>::Node& Graph<Key, Value, Weight>::Node::operator=(Node &&moved){
        if(&moved != this){
            values = moved.values;
            edges = moved.edges;
            moved.clear();
        }
        return *this;
    }


//iterators

    template <typename Key, typename Value, typename Weight>
    typename Graph<Key, Value, Weight>::Node::iterator Graph<Key, Value, Weight>::Node::begin(){
        return edges.begin();
    }

    template <typename Key, typename Value, typename Weight>
    typename Graph<Key, Value, Weight>::Node::const_iterator Graph<Key, Value, Weight>::Node::cbegin(){
        return edges.cbegin();
    }

    template <typename Key, typename Value, typename Weight>
    typename Graph<Key, Value, Weight>::Node::iterator Graph<Key, Value, Weight>::Node::end(){
        return edges.end();
    }

    template <typename Key, typename Value, typename Weight>
    typename Graph<Key, Value, Weight>::Node::const_iterator Graph<Key, Value, Weight>::Node::cend(){
        return edges.cend();
    }




    //++++++++++++++++++++++++++++++        GRAPH        ++++++++++++++++++++++++++++++++//

//constructors

    template <typename Key, typename Value, typename Weight>
    Graph<Key, Value, Weight>::Graph() = default;

    template <typename Key, typename Value, typename Weight>
    Graph<Key, Value, Weight>::Graph(const Graph &other){
        vertices = other.vertices;
    }

    template <typename Key, typename Value, typename Weight>
    Graph<Key, Value, Weight>::Graph(Graph &&other){
        vertices = other.vertices;
        other.clear();
    }


//methods

    template <typename Key, typename Value, typename Weight>
    bool Graph<Key, Value, Weight>::empty(){
        return vertices.empty();
    }

    template <typename Key, typename Value, typename Weight>
    size_t Graph<Key, Value, Weight>::size(){
        return vertices.size();
    }

    template <typename Key, typename Value, typename Weight>
    void Graph<Key, Value, Weight>::clear(){
        vertices.clear();
    }

    template <typename Key, typename Value, typename Weight>
    void Graph<Key, Value, Weight>::swap(Graph &graph2){
        std::swap(vertices, graph2.vertices);
    }

    template <typename Key2, typename Value2, typename Weight2>
    void swap(Graph<Key2, Value2, Weight2> &g1, Graph<Key2, Value2, Weight2> &g2){
        std::swap(g1.nodes, g2.nodes);
    }

    template <typename Key, typename Value, typename Weight>
    Value& Graph<Key, Value, Weight>::at(Key k){
        if(vertices.find(k) == vertices.end()){
            throw runtime_error("\nError: no vertices with such a key.");}
        return vertices.at(k).values;
    }

    template <typename Key, typename Value, typename Weight>
    size_t Graph<Key, Value, Weight>::degree_in(Key k){
        size_t degree = 0;
        for(auto i = vertices.begin(); i != vertices.end(); i++){
            Graph<Key, Value, Weight>::Node currentN = (i->second);

            if(currentN.edges.find(k) != currentN.edges.end()){
                degree++;
            }
        }
        return degree;
    }

    template <typename Key, typename Value, typename Weight>
    size_t Graph<Key, Value, Weight>::degree_out(Key k){
        if(vertices.find(k) == vertices.end()){
            throw runtime_error("\nError: no vertices with such a key.");}
        return vertices[k].size();
    }

    template <typename Key, typename Value, typename Weight>
    bool Graph<Key, Value, Weight>::loop(Key k){
        if(vertices.find(k) == vertices.end()){
            throw runtime_error("\nError: no vertices with such a key.");}
        return vertices[k].edges.find(k) != vertices[k].edges.end();
    }

    template <typename Key, typename Value, typename Weight>
    std::pair<typename Graph<Key, Value, Weight>::iterator, bool>  Graph<Key, Value, Weight>::insert_node(key_type k, value_type v){
        return vertices.insert({k, v});
    }

    template <typename Key, typename Value, typename Weight>
    std::pair<typename Graph<Key, Value, Weight>::iterator, bool>  Graph<Key, Value, Weight>::insert_or_assign_node(key_type k, value_type v){
        return vertices.insert_or_assign({k, v});
    }


    template <typename Key, typename Value, typename Weight>
    std::pair<typename Graph<Key, Value, Weight>::Node::iterator, bool> Graph<Key, Value, Weight>::insert_edge(std::initializer_list<key_type> keys_from_to, weight_type W){
        Key from = *(keys_from_to.begin());
        Key to = *(keys_from_to.begin()+1);
        if(vertices.find(from) == vertices.end() || vertices.find(to) == vertices.end()){
            throw runtime_error("\nError: no such vertices.");
        }
        return vertices[from].edges.insert({to, W});
    }


    template <typename Key, typename Value, typename Weight>
    std::pair<typename Graph<Key, Value, Weight>::Node::iterator, bool> Graph<Key, Value, Weight>::insert_or_assign_edge(std::initializer_list<key_type> keys_from_to, weight_type W){
        Key from = *(keys_from_to.begin());
        Key to = *(keys_from_to.begin()+1);
        if(vertices.find(from) == vertices.end() || vertices.find(to) == vertices.end()){
            throw runtime_error("\nError: no such vertices.");
        }
        return from.edges.insert_or_assign({to, W});
    }


//dops

    template <typename Key, typename Value, typename Weight>
    void Graph<Key, Value, Weight>::view(){
        int j = 1;
        cout << "\n\nAmout of vertices: " << vertices.size() << "\n";
        for(auto i = vertices.begin(); i != vertices.end(); i++){
            cout << "\nVertex #" << j << ": " << "\n\tKey: " << i->first;
            cout << "\n\tValue: " << i->second.values;
            cout << "\n\tAll edges: " << degree_out(i->first) + degree_in(i->first);
            cout << "\n\tIncoming edges: " << degree_in(i->first);
            cout << "\n\tOutcoming edges: " << degree_out(i->first);
            cout << "\n\tLoops: (true/false): " << loop(i->first);
            j++;
        }
    }

    template <typename Key, typename Value, typename Weight>
    size_t Graph<Key, Value, Weight>::delete_node(key_type k){
        return vertices.erase(k);
    }

    template <typename Key, typename Value, typename Weight>
    void Graph<Key, Value, Weight>::RenderDot(std::ostream& out){
        out << "digraph G" << " {\n";
        out << "node [shape=record fontname=Arial]\n";

        for(auto i = vertices.begin(); i != vertices.end(); i++){
            out << vertices[i->first].values << " [label=\"Key: " << i->first << "; Value: " << vertices[i->first].values << "\"]\n";
        }

        for(auto i = vertices.begin(); i != vertices.end(); i++){
            for(auto j = vertices[i->first].edges.begin(); j != vertices[i->first].edges.end(); j++){
                out << vertices[i->first].values << " -> " << vertices[j->first].values << "\n";
            }
        }
        out << "}";
    }



//operators

    template <typename Key, typename Value, typename Weight>
    Graph<Key, Value, Weight>& Graph<Key, Value, Weight>::operator=(const Graph &copy){
        vertices = copy.vertices;
        return *this;
    }

    template <typename Key, typename Value, typename Weight>
    Graph<Key, Value, Weight>& Graph<Key, Value, Weight>::operator=(Graph &&moved){
        vertices = moved.vertices;
        moved.clear();
        return *this;
    }

    //return value (cppreference):
    //A reference to the mapped value of the new element if no element with key key existed.
    //Otherwise, a reference to the mapped value of the existing element whose key is equivalent to key.
    template <typename Key, typename Value, typename Weight>
    Value& Graph<Key, Value, Weight>::operator[](Key k) const{
        return vertices[k].values;
    }


//iterators

    template <typename Key, typename Value, typename Weight>
    typename Graph<Key, Value, Weight>::iterator Graph<Key, Value, Weight>::begin(){
        return vertices.begin();
    }

    template <typename Key, typename Value, typename Weight>
    typename Graph<Key, Value, Weight>::const_iterator Graph<Key, Value, Weight>::cbegin(){
        return vertices.cbegin();
    }

    template <typename Key, typename Value, typename Weight>
    typename Graph<Key, Value, Weight>::iterator Graph<Key, Value, Weight>::end(){
        return vertices.end();
    }

    template <typename Key, typename Value, typename Weight>
    typename Graph<Key, Value, Weight>::const_iterator Graph<Key, Value, Weight>::cend(){
        return vertices.cend();
    }

    // std::ostream& operator<<(std::ostream& out, const Edge& edge) {
    //     out << edge.from << " -> " << edge.to << edge.properties << ";\n";
    //     return out;
    // }





};