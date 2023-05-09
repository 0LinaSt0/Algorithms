#include "../includes/graph.hpp"

namespace s21{

Graph::Graph(){

}
Graph::Graph(const Graph& other){
    (void)other;
}
Graph::Graph(Graph&& other){
    (void)other;
}
Graph::~Graph(){

}

Graph& Graph::operator=(const Graph& other){
    (void)other;
    return *this;
}
Graph& Graph::operator=(Graph&& other){
    (void)other;
    return *this;
}

}
