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
    PathNodeMatrix(matrix_ptr matrix, int from_node, int to_node,
        int(*costDetermining)(matrix_ptr, coordinates&));

    int GetWayCost(void) const;

    coordinate GetPathNodeVertices(void) const;
private:
    matrix_ptr matrix_;
    coordinates reducing_nodes_;
    PathNode tree_node_;
};

};

#endif
