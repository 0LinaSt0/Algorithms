#ifndef PATH_NODE_MATRIX
#define PATH_NODE_MATRIX

#include <vector>
#include <memory>
#include <array>

#include "utils.hpp"

namespace s21{

struct PathNode{
    int from_vertex_;
    int to_vertex_;
    int way_cost_;
};

class PathNodeMatrix{
public:
    PathNodeMatrix(matrix_unique_ptr matrix,
        int from_node, int to_node, int current_way_cost, 
        int(*costDetermining)(int, matrix_type&, coordinates&));

    int GetWayCost(void) const;

    coordinate GetPathNodeVertices(void) const;

    coordinate ReducedCellsEvaluating(void);
private:
    matrix_unique_ptr matrix_;
    coordinates reducing_nodes_;
    PathNode tree_node_;
};

};

#endif
