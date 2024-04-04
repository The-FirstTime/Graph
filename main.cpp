#include <iostream>
#include <fstream>
#include "Graph.h"
using namespace std;

int main(){
    graph::Graph<int, int, int> n;
    n.insert_node(123, 500);
    n.insert_node(7, 1000);
    n.insert_node(9, 10);
    std::initializer_list<int> l1 = {123, 7};
    std::initializer_list<int> l2 = {9, 7};
    std::initializer_list<int> l3 = {9, 123};
    std::initializer_list<int> l4 = {9, 9};
    n.insert_edge(l1, 6);
    n.insert_edge(l2, 6);
    n.insert_edge(l3, -3);
    n.insert_edge(l4, 5);
    n.view();
    std::ofstream out("out.gv");
    n.RenderDot(out);

}