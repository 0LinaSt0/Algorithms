#ifndef BRANCH_BOUND_METHOD_ALGORITHM_UTILS
#define BRANCH_BOUND_METHOD_ALGORITHM_UTILS

#include <vector>
#include <limits>

#include "../../graph/includes/graph.hpp"
#include "../../graph/includes/graphAlgorithms.hpp"

namespace s21{

class BranchBoundMethodAlgoritmUtils{
public:
    std::vector<std::vector<int>> InitialMatrix(const Graph& graph);
    
};

}

#endif