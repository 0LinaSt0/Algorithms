#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

#include <initializer_list>
#include <algorithm>
#include <climits>
#include <utility>
#include <numeric>
#include <vector>

#include "../../containers/stack/includes/stack.hpp"
#include "../../containers/queue/includes/queue.hpp"
#include "../../utils/includes/antAlgorithmUtils.hpp"
#include "../../utils/includes/utils.hpp"
#include "../../utils/includes/ant.hpp"
#include "graph.hpp"

namespace s21{

class Ant;
class AntAlgorithmUtils;

class GraphAlgorithms{
public:
    using elem_of_graph_type    = typename Graph::elem_of_graph_type;
    using graph_type            = typename Graph::graph_type;
    using graph_iterator        = typename Graph::iterator_type;

    GraphAlgorithms() = default;
    GraphAlgorithms(const GraphAlgorithms& other) = default;
    GraphAlgorithms(GraphAlgorithms&& other) = default;
    ~GraphAlgorithms() = default;

    GraphAlgorithms& operator=(const GraphAlgorithms& other) = default;
    GraphAlgorithms& operator=(GraphAlgorithms&& other) = default;

    std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);

    std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);

    int GetShortestPathBetweenVertices(Graph& graph, int vertex1, int vertex2);

    Graph GetShortestPathsBetweenAllVertices(Graph& graph);

    Graph GetLeastSpanningTree(Graph &graph);

    // average_distance_length
    TsmResult SolveTravelingSalesmanProblem(Graph &graph);

    TsmResult STSPBranchBoundMethodAlgorithm(Graph &graph);
private:
    AntAlgorithmUtils* ants_utils_;

    int MinWeight_(Graph &matrix, int column, int row, int throgh_node);
};

}

#endif
