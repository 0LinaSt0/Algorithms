#ifndef PATH_NODE_MATRIX
#define PATH_NODE_MATRIX

#include <algorithm>
#include <limits>
#include <vector>
#include <memory>
#include <array>
#include <map>

#include "utils.hpp"
#include "branchBoundMethodAlgorithmUtils.hpp"

namespace s21{

class PathNodeRootMatrix{
public:
    using row_matrix_pair         = typename bbma_utils::row_matrix_pair_type;
    using matrix_pair             = typename bbma_utils::matrix_pair_type;
    using matrix_pair_unique_ptr  = typename bbma_utils::matrix_pair_unique_ptr;
    using row_matrix_iter         = typename matrix_pair::iterator;
    using column_matrix_iter      = typename row_matrix_pair::iterator;
    using matrix_pair_ref         = row_matrix_pair&;
    using matrix_const_pair_ref   = row_matrix_pair&;
    using matrix_map              = std::map<int, std::vector<int>>;

    PathNodeRootMatrix(void) = default;
    PathNodeRootMatrix(matrix_pair_unique_ptr matrix);

    matrix_pair_ref operator[](matrix_type::size_type pos);
    matrix_const_pair_ref operator[](matrix_type::size_type pos) const;

    double GetWayCost(void) const;

    coordinate GetPathNodeVertices(void) const;

    row_matrix_iter GetFindedEdgeRowIter(void) const;

    column_matrix_iter GetFindedEdgeColumnIter(void) const;

    matrix_pair_unique_ptr GetMatrixCopy(void) const;

    bool IsIncludedEdgeNode(void) const;

    bool IsMatrixEmpty(void) const;

    virtual coordinate ReducedCellsEvaluating(void);

protected:
    matrix_pair_unique_ptr matrix_;
    row_matrix_iter finded_edge_row_it_;
    column_matrix_iter finded_edge_column_it_;
    matrix_map reducing_nodes_;
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

    int FindMinInColumn_(int column_i);

    double CellGradeDeterminig_(int row_i, int column_i);

    coordinate FindedCellCoordenates_(int row_i, int column_i);
};

class PathNodeIncludeMatrix : public PathNodeRootMatrix{
public:
    PathNodeIncludeMatrix(PathNodeRootMatrix& matrix_node);

private:
    void CostDeterminingPathNode_(int current_way_cost);

    void RestructMatrix_(PathNodeRootMatrix& matrix_node);

    void InfToInversePath_(int row_coordinate, int column_coordinate);
};

class PathNodeNotIncludeMatrix : public PathNodeRootMatrix{
public:
    PathNodeNotIncludeMatrix(PathNodeRootMatrix& matrix_node);

    coordinate ReducedCellsEvaluating(void);

private:
    void CostDeterminingPathNode_(int current_way_cost, int current_cell_score);

    void RestructMatrix_(PathNodeRootMatrix& matrix_node);
};

};

#endif
