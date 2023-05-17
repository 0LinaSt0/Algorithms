#pragma once

#include <initializer_list>
#include <algorithm>
#include <utility>
#include <vector>

#include "../../containers/stack/includes/stack.hpp"
#include "../../utils/includes/utils.hpp"
#include "graph.hpp"

namespace s21{

class GraphAlgorithms{
public:
    using elem_of_graph_type    = typename Graph::elem_of_graph_type;
    using graph_type            = typename Graph::graph_type;

    GraphAlgorithms() = default;
    GraphAlgorithms(const GraphAlgorithms& other) = default;
    GraphAlgorithms(GraphAlgorithms&& other) = default;
    ~GraphAlgorithms() = default;

    GraphAlgorithms& operator=(const GraphAlgorithms& other) = default;
    GraphAlgorithms& operator=(GraphAlgorithms&& other) = default;

    std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);

    Graph GetShortestPathsBetweenAllVertices(Graph &graph);
private:
    int MinWeight_(Graph &matrix, int column, int row, int throgh_node);
    std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);

    graph_type GetShortestPathsBetweenAllVertices(Graph &graph);
    Graph GetShortestPathsBetweenAllVerticesGr(Graph &graph);

    std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);

    Graph GetShortestPathsBetweenAllVertices(Graph &graph);
private:
    int MinWeight_(Graph &matrix, int column, int row, int throgh_node);
};

}
