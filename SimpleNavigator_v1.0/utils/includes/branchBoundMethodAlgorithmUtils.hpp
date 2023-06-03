#ifndef BRANCH_BOUND_METHOD_ALGORITHM_UTILS
#define BRANCH_BOUND_METHOD_ALGORITHM_UTILS

#include <vector>
#include <limits>
#include <memory>

#include "utils.hpp"
#include "../../graph/includes/graph.hpp"
#include "../../graph/includes/graphAlgorithms.hpp"

namespace s21{

class BranchBoundMethodAlgoritmUtils{
public:
    matrix_unique_ptr InitialMatrix(const Graph& graph);

    int CostDeterminingIncludingPathNode(int current_way_cost, 
                            matrix_type& matrix, coordinates& reducing_nodes);

    int CostDeterminingNotIncludingPathNode(int current_way_cost, 
                            matrix_type& matrix, coordinates& reducing_nodes);
};

}

#endif
