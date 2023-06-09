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

using node_shared_ptr   = std::shared_ptr<PathNodeRootMatrix>;

bool NodesCostCompare(const node_shared_ptr& a, const node_shared_ptr& b);

class bbma_utils{
public:
    using coordinates_iter          = typename coordinates::iterator;
    using coorsinate_cell           = std::pair<const coordinate, int>;
    using row_matrix_pair_type      = std::vector<coorsinate_cell>;
    using matrix_pair_type          = std::vector<row_matrix_pair_type>;
    using matrix_pair_unique_ptr    = std::unique_ptr<matrix_pair_type>;
    using multiset_type             = std::multiset<node_shared_ptr,
                                            decltype(NodesCostCompare)*>;

    matrix_pair_unique_ptr InitialMatrix(const Graph& graph);

    // return itertor to added PathNodeIncludeMatrix
    multiset_type::iterator AddWayNodesToUnforkedNodes(
                                multiset_type& unforked_nodes,
                                PathNodeRootMatrix& matrix_node,
                                int from_node, int to_node);

    TsmResult FinalPathFormation(coordinates way, double way_cost);

    private:
        coordinates_iter FindNextNode_(const coordinates& way, int finded_from);
};

}

#endif
