#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP

#include <initializer_list>
#include <algorithm>
#include <float.h>
#include <climits>
#include <utility>
#include <numeric>
#include <vector>
#include <limits>
#include <set>

#include "../../containers/stack/includes/stack.hpp"
#include "../../containers/queue/includes/queue.hpp"
#include "../../utils/includes/branchBoundMethodAlgorithmUtils.hpp"
#include "../../utils/includes/antAlgorithmUtils.hpp"
#include "../../utils/includes/pathNodeMatrix.hpp"
#include "../../utils/includes/utils.hpp"
#include "../../utils/includes/ant.hpp"
#include "s21_graph.h"

namespace s21{

class Ant;
class AntAlgorithmUtils;
class BranchBoundMethodAlgoritmUtils;

class GraphAlgorithms{
public:
    using aa_utils                  = AntAlgorithmUtils;
    using bbma_utils                = BbmaUtils;
    using aa_utils_shared_ptr       = std::shared_ptr<aa_utils>;
    using bbma_utils_shared_ptr     = std::shared_ptr<bbma_utils>;
    using elem_of_graph_type        = typename Graph::elem_of_graph_type;
    using graph_type                = typename Graph::graph_type;
    using graph_iterator            = typename Graph::iterator_type;
    using multyset_type             = BbmaUtils::multiset_type;
    using multyset_iterator_type    = multyset_type::iterator;

    GraphAlgorithms();
    GraphAlgorithms(const GraphAlgorithms& other) = default;
    GraphAlgorithms(GraphAlgorithms&& other) = default;
    ~GraphAlgorithms() = default;

    GraphAlgorithms& operator=(const GraphAlgorithms& other) = default;
    GraphAlgorithms& operator=(GraphAlgorithms&& other) = default;

    /**
     * Finding a non-recursive depth-first search in the [graph]
     * from a given [start_vertex]
     * @return std::vector<int> with the traversed vertices in the order
     *         they were traversed
     */
    std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);

    /**
     * Finding a breadth-first search in the [graph] from a given [start_vertex]
     * @return std::vector<int> with the traversed vertices in the order
     *         they were traversed
     */
    std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);

    /**
     * Searching the shortest path between two vertices [vertex1] and [vertex2]
     * in a [graph] using Dijkstra's algorithm
     * @return int value of the smallest distance of the shortest path
     */
    int GetShortestPathBetweenVertices(Graph& graph, int vertex1, int vertex2);

    /**
     * Searching the shortest paths between all pairs of vertices in a [graph]
     * using the Floyd-Warshall algorithm
     * @return Graph with the shortest paths between all vertices
     */
    Graph GetShortestPathsBetweenAllVertices(Graph& graph);

    /**
     * Searching the minimal spanning tree in a [graph] using Prim's algorithm
     * @return Graph for the minimal spanning tree
     * @throw std::invalid_argument if couldn't find the least spanning tree
     */
    Graph GetLeastSpanningTree(Graph &graph);

    /**
     * Solving the traveling salesman's problem using the ant colony algorithm:
     * to find the shortest path that goes through all vertices of the [graph]
     * @return TsmResult structure with the row and the length of the row
     */
    TsmResult SolveTravelingSalesmanProblem(Graph &graph);

    /**
     * Solving the traveling salesman's problem using the branch and bound
     * method algorithm: to find the shortest path that goes through all
     * vertices of the [graph]
     * @return TsmResult structure with the row and the length of the row
     */
    TsmResult STSPBranchBoundMethodAlgorithm(Graph &graph);

    /**
     * Solving the traveling salesman's problem using the brute force
     * method algorithm: to find the shortest path that goes through all
     * vertices of the [graph]
     * @return TsmResult structure with the row and the length of the row
     */
    TsmResult ExhaustiveSearch(Graph &graph);

private:
    aa_utils_shared_ptr ants_utils_;
    bbma_utils_shared_ptr bbmethod_utils_;

    /**
     * Helper method of GetShortestPathsBetweenAllVertices for choosing minimum
     * weight between direct path [row][column] and indirect path
     * [row][throgh_node] + [through_node][column]
     * @return int value of chooding minimum weight
     */
    int MinWeight_(Graph &matrix, int column, int row, int throgh_node);

    /**
     * Helper method of ExhaustiveSearch for all implementation
     */
    void ExhaustiveSearch_(double& min_row_weight,
                            std::vector<int>& min_row,
                            const std::vector<int>& parent_row,
                            const Graph& graph) const;

    /**
     * Printing error for TSP methods if the [graph] is empty or not connected
     * @return true if the [graph] is inappropriate
     * @return false if the [graph] is appropriate
     */
    bool IsInappropriateGraph_(const Graph& graph) const;

};

}

#endif
