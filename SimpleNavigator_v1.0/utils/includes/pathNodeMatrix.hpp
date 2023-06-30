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

class BbmaUtils;

class PathNodeRootMatrix{
public:
    using row_matrix_pair         = row_matrix_pair_type;
    using matrix_pair             = matrix_pair_type;
    using row_matrix_iter         = typename matrix_pair::iterator;
    using column_matrix_iter      = typename row_matrix_pair::iterator;
    using matrix_pair_ref         = row_matrix_pair&;
    using matrix_const_pair_ref   = row_matrix_pair&;
    using matrix_map              = std::map<int, std::vector<int>>;

    PathNodeRootMatrix(void) = default;
    PathNodeRootMatrix(matrix_pair_unique_ptr matrix);

    matrix_pair_ref operator[](matrix_type::size_type pos);
    matrix_const_pair_ref operator[](matrix_type::size_type pos) const;

    /**
     * @return double value of choosed subpath of current Node
     */
    double GetWayCost(void) const;

    /**
     * @return coordinates of current Node's way
     */
    coordinates GetCurrentWay(void) const;

    /**
     * @return coordinate of current Node's subpath coordinates
     * @attention for root node from-to coordinates are [0; 0]
     */
    coordinate GetPathNodeVertices(void) const;

    /**
     * @return row_matrix_iter to finded element's row in current Node's matrix
     * @attention undefined behavior if next subpath not found before
     */
    row_matrix_iter GetFindedEdgeRowIter(void) const;

    /**
     * @return column_matrix_iter to finded element's column
     * in current Node's matrix
     * @attention undefined behavior if next subpath not found before
     */
    column_matrix_iter GetFindedEdgeColumnIter(void) const;

    /**
     * @return row_matrix_iter to first row in current Node's matrix
     */
    row_matrix_iter Begin() const;

    /**
     * @return matrix_pair_unique_ptr of current Node's matrix copy
     */
    matrix_pair_unique_ptr GetMatrixCopy(void) const;

    /**
     * @return -1 if current node is root node
     * @return 0 if current node's matrix doesn't include subpath
     * @return 1 if current node's matrix includes subpath
     */
    int IsIncludedEdgeNode(void) const;

    /**
     * @return true if node's matrix is empty
     * @return false if node's matrix isn't empty
     */
    bool IsMatrixEmpty(void) const;

    /**
     * Reducing and evaluating nodes current matrix for finding next subpath
     * @return coordinate of finded subpath
     */
    virtual coordinate ReducedCellsEvaluating(void);

protected:
    matrix_pair_unique_ptr matrix_;
    row_matrix_iter finded_edge_row_it_;
    column_matrix_iter finded_edge_column_it_;
    matrix_map reducing_nodes_;
    coordinates current_way_;
    int from_vertex_;
    int to_vertex_;
    double way_cost_;
    int is_included_;
    bool is_empty_;

    /**
     * Initalization protected variables in child objects
     */
    void FieldInitialization_(PathNodeRootMatrix& matrix_node);

    /**
     * Determining cost for every cell in current Node's matrix
     * @throw std::invalid_argument if RowCellsReduced_() or 
     * ColumnCellsReduced_() returned it
     */
    virtual void CostDeterminingPathNode_(void);

    /**
     * Reducing and evaluating nodes current matrix for finding next subpath
     * @return coordinate of finded subpath
     */
    coordinate CellsEvaluating_(void);

    /**
     * Reducing every elem in row in current Node's matrix
     * @throw std::invalid_argument if on some work stage selected_cell_value 
     * will be infinity(int_max)
     */
    void RowCellsReduced_(void);

    /**
     * Reducing every elem in column in current Node's matrix
     * @throw std::invalid_argument if on some work stage selected_cell_value 
     * will be infinity(int_max)
     */
    void ColumnCellsReduced_(void);

    /**
     * Finding element with minimum weight in row in [row_i][column] cell
     * @return int value of choosing node's column index in row
     */
    int FindMinInRow_(int row_i, int column);

    /**
     * Finding element with minimum weight in column in [row][column_i] cell
     * @return int value of choosing node's row index in column
     */
    int FindMinInColumn_(int column_i, int row);

    /**
     * Determining new future grade for [row_i][column_i] cell 
     * with the highest grade
     * @return double value of new grade: min_grade_in_row + min_grade_in_column
     */
    double CellGradeDeterminig_(int row_i, int column_i);

    /**
     * @return default coordinate of [row_i][column_i] cell
     */
    coordinate FindedCellCoordenates_(int row_i, int column_i);
};


class PathNodeIncludeMatrix : public PathNodeRootMatrix{
public:
    PathNodeIncludeMatrix(PathNodeRootMatrix& matrix_node);

private:
    /**
     * Determining cost for every cell and updating way_cost 
     * using [current_way_cost] in current Node's matrix
     */
    void CostDeterminingPathNode_(double current_way_cost);

    /**
     * Deleting row and column of node's cell in current node's matrix
     */
    void RestructMatrix_(PathNodeRootMatrix& matrix_node);

    /**
     * Setting infinity(max_int) to inverted of 
     * [row_coordinate][column_coordinate] cell
     */
    void InfToInversePath_(int row_coordinate, int column_coordinate);
};


class PathNodeNotIncludeMatrix : public PathNodeRootMatrix{
public:
    PathNodeNotIncludeMatrix(PathNodeRootMatrix& matrix_node);

    /**
     * Reducing and evaluating nodes current matrix for finding next subpath
     * @return coordinate of finded subpath
     * @throw std::invalid_argument if RowCellsReduced_() or 
     * ColumnCellsReduced_() returned it
     */
    coordinate ReducedCellsEvaluating(void);

private:
    /**
     * Updating way_cost using [current_way_cost] and [current_cell_score]
     * in current Node's matrix
     */
    void CostDeterminingPathNode_(double current_way_cost, 
                                int current_cell_score);

    /**
     * Setting infinity(max_int) in node's cell in current node's matrix
     */
    void RestructMatrix_(PathNodeRootMatrix& matrix_node);
};

};

#endif
