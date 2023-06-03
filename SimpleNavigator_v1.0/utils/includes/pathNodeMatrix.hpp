#ifndef PATH_NODE_MATRIX
#define PATH_NODE_MATRIX

#include <limits>
#include <vector>
#include <memory>
#include <array>

#include "utils.hpp"

namespace s21{

class PathNodeRootMatrix{
public:
    PathNodeRootMatrix(void) = default;
    PathNodeRootMatrix(matrix_unique_ptr matrix);

    matrix_reference operator[](matrix_type::size_type pos);
    matrix_const_reference operator[](matrix_type::size_type pos) const;

    int GetWayCost(void) const;

    coordinate GetPathNodeVertices(void) const;

    matrix_unique_ptr GetMatrixCopy(void) const;

    virtual coordinate ReducedCellsEvaluating(void);

protected:
    matrix_unique_ptr matrix_;
    coordinates reducing_nodes_;
    int from_vertex_;
    int to_vertex_;
    int way_cost_;

    virtual void CostDeterminingPathNode_(void);

    void FieldInitialization_(int from_node, int to_node);
};

class PathNodeIncludeMatrix : public PathNodeRootMatrix{
public:
    PathNodeIncludeMatrix(PathNodeRootMatrix& matrix, int from_node, 
                        int to_node);
    
    coordinate ReducedCellsEvaluating(void);

private:
    void CostDeterminingPathNode_(int current_way_cost);

    void RestructMatrix_(PathNodeRootMatrix& matrix, int from_node, 
                        int to_node);
};

class PathNodeNotIncludeMatrix : public PathNodeRootMatrix{
public:
    PathNodeNotIncludeMatrix(PathNodeRootMatrix& matrix, int from_node, 
                        int to_node);

    coordinate ReducedCellsEvaluating(void);

private:
    void CostDeterminingPathNode_(int current_way_cost, int current_cell_score);

    void RestructMatrix_(PathNodeRootMatrix& matrix, int from_node, 
                        int to_node);
};

};

#endif
