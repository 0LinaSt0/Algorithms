#ifndef BRANCH_BOUND_METHOD_ALGORITHM_UTILS
#define BRANCH_BOUND_METHOD_ALGORITHM_UTILS

#include <vector>
#include <limits>
#include <memory>
#include <set>

#include "utils.hpp"
#include "pathNodeMatrix.hpp"
#include "../../graph/includes/s21_graph.h"

namespace s21{

class PathNodeRootMatrix;
class PathNodeIncludeMatrix;
class PathNodeNotIncludeMatrix;

using node_shared_ptr   = std::shared_ptr<PathNodeRootMatrix>;

/**
 * Compare function for multiset with tree Nodes which didn't forked still. 
 * Compare way_cost of [a] and [b] tree Nodes during adding their to multiset 
 * @return true if [a].cost_way < [b].cost_way
 * @return false if [a].cost_way >= [b].cost_way
 */
bool NodesCostCompare(const node_shared_ptr& a, const node_shared_ptr& b);

class BbmaUtils{
public:

    using multiset_type = std::multiset<node_shared_ptr,
                            decltype(NodesCostCompare)*>;

    /**
     * Creating the new restructed Node's matrix based on [graph].matrix. 
     * Every cell is std::pair with default cell's coordinate and weight. 
     * The weight is set as infinity(max_int) if default value of weight  
     * is zero or there is from_node == to_node
     * @return matrix_pair_unique_ptr to new Node's matrix
     */
    matrix_pair_unique_ptr InitialMatrix(const Graph& graph);

    /**
     * Adding new unforkted [matrix_node] to multiset [unforked_nodes]
     * @return multiset_type::iterator to added PathNodeIncludeMatrix
     */
    multiset_type::iterator AddWayNodesToUnforkedNodes(
                                multiset_type& unforked_nodes,
                                PathNodeRootMatrix& matrix_node);

    TsmResult FinalPathFormation(coordinates way, double way_cost);

private:
    coordinates_iter FindNextNode_(coordinates& way, int finded_from);
};

}

#endif
