#pragma once

#include "../../containers/stack/includes/stack.hpp"
#include "graph.hpp"

namespace s21{

class GraphAlgorithms{
public:
    GraphAlgorithms() = default;
    GraphAlgorithms(const GraphAlgorithms& other) = default;
    GraphAlgorithms(GraphAlgorithms&& other) = default;
    ~GraphAlgorithms() = default;

    GraphAlgorithms& operator=(const GraphAlgorithms& other) = default;
    GraphAlgorithms& operator=(GraphAlgorithms&& other) = default;

    auto DepthFirstSearch(Graph &graph, int start_vertex);

private:

};

}
