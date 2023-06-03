#ifndef BRANCH_BOUND_METHOD_ALGORITHM_UTILS
#define BRANCH_BOUND_METHOD_ALGORITHM_UTILS

#include <vector>
#include <limits>
#include <memory>
#include <set>

#include "utils.hpp"
#include "pathNodeMatrix.hpp"
#include "../../graph/includes/graph.hpp"

namespace s21{

bool NodesCostCompare(const PathNodeRootMatrix& a, const PathNodeRootMatrix& b);

class bbma_utils{
public:
    using multiset_type = std::multiset<PathNodeRootMatrix, 
                                        decltype(NodesCostCompare)*>;

    matrix_unique_ptr InitialMatrix(const Graph& graph);

    // return itertor to added PathNodeIncludeMatrix
    multiset_type::iterator AddWayNodesToUnforkedNodes(
                                multiset_type& unforked_nodes, 
                                PathNodeRootMatrix& matrix, 
                                int from_node, int to_node);
};


}

#endif
