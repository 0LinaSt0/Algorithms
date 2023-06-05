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
    using row_iter_pair = std::pair<int, matrix_iterator_type>;
    using column_iter_pair = std::pair<int, typename row_matrix_type::iterator>;

    PathNodeRootMatrix(void) = default;
    PathNodeRootMatrix(matrix_unique_ptr matrix);

    matrix_reference operator[](matrix_type::size_type pos);
    matrix_const_reference operator[](matrix_type::size_type pos) const;

    double GetWayCost(void) const;

    coordinate GetPathNodeVertices(void) const;

    row_iter_pair GetFindedEdgeRowIter(void) const;

    column_iter_pair GetFindedEdgeColumnIter(void) const;

    matrix_unique_ptr GetMatrixCopy(void) const;

    bool IsIncludedEdgeNode(void) const;

    bool IsMatrixEmpty(void) const;

    virtual coordinate ReducedCellsEvaluating(void);

protected:
    matrix_unique_ptr matrix_;
    row_iter_pair finded_included_edge_row_;
    column_iter_pair finded_included_edge_column_;
    coordinates reducing_nodes_;
    int from_vertex_;
    int to_vertex_;
    double way_cost_;
    bool is_included_;
    bool is_empty_;

    virtual void CostDeterminingPathNode_(void);

    void FieldInitialization_(int from_node, int to_node);

    void RowCellsReduced_(void);

    void ColumnCellsReduced_(void);

    coordinate CellsEvaluating_(void);
};

class PathNodeIncludeMatrix : public PathNodeRootMatrix{
public:
    PathNodeIncludeMatrix(PathNodeRootMatrix& matrix);

private:
    void CostDeterminingPathNode_(int current_way_cost);

    void RestructMatrix_(PathNodeRootMatrix& matrix);
};

class PathNodeNotIncludeMatrix : public PathNodeRootMatrix{
public:
    PathNodeNotIncludeMatrix(PathNodeRootMatrix& matrix);

    coordinate ReducedCellsEvaluating(void);

private:
    void CostDeterminingPathNode_(int current_way_cost, int current_cell_score);

    void RestructMatrix_(PathNodeRootMatrix& matrix, int from_node,
                        int to_node);
};

};

#endif
