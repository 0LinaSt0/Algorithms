#ifndef PATH_NODE_MATRIX
#define PATH_NODE_MATRIX

#include <algorithm>
#include <limits>
#include <vector>
#include <memory>
#include <array>
#include <map>

#include "utils.hpp"

namespace s21{

class PathNodeRootMatrix{
public:
    using column_matrix_iter_type   = typename row_matrix_type::iterator;
    using row_iter_pair             = std::pair<int, matrix_iterator_type>;
    using column_iter_pair          = std::pair<int, column_matrix_iter_type>;
    using matrix_map_type           = std::map<size_t, std::vector<size_t>>;

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
    matrix_map_type reducing_nodes_;
    int from_vertex_;
    int to_vertex_;
    double way_cost_;
    bool is_included_;
    bool is_empty_;

    void FieldInitialization_(int from_node, int to_node);

    virtual void CostDeterminingPathNode_(void);

    coordinate CellsEvaluating_(void);

    void RowCellsReduced_(void);

    void ColumnCellsReduced_(void);

    size_t FindMinInColumn_(size_t column_i);
};

class PathNodeIncludeMatrix : public PathNodeRootMatrix{
public:
    PathNodeIncludeMatrix(PathNodeRootMatrix& matrix_node);

private:
    void CostDeterminingPathNode_(int current_way_cost);

    void RestructMatrix_(PathNodeRootMatrix& matrix_node);
};

class PathNodeNotIncludeMatrix : public PathNodeRootMatrix{
public:
    PathNodeNotIncludeMatrix(PathNodeRootMatrix& matrix_node);

    coordinate ReducedCellsEvaluating(void);

private:
    void CostDeterminingPathNode_(int current_way_cost, int current_cell_score);

    void RestructMatrix_(PathNodeRootMatrix& matrix_node,
            column_matrix_iter_type& cell_it);
};

};

#endif
