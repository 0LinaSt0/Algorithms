#include "../includes/pathNodeMatrix.hpp"

namespace s21{

PathNodeRootMatrix::PathNodeRootMatrix(matrix_unique_ptr matrix)
    : matrix_(std::move(matrix)), from_vertex_(0),
    to_vertex_(0), is_included_(0), is_empty_(0){
    CostDeterminingPathNode_();
}

matrix_reference PathNodeRootMatrix::operator[](matrix_type::size_type pos){
    return (*matrix_).operator[](pos);
}

matrix_const_reference PathNodeRootMatrix::operator[](
                                matrix_type::size_type pos) const{
    return (*matrix_).operator[](pos);
}

double PathNodeRootMatrix::GetWayCost(void) const{
    return way_cost_;
}

coordinate PathNodeRootMatrix::GetPathNodeVertices(void) const{
    return coordinate{from_vertex_, to_vertex_};
}

PathNodeRootMatrix::row_iter_pair
        PathNodeRootMatrix::GetFindedEdgeRowIter(void) const{
    return finded_included_edge_row_;
}

PathNodeRootMatrix::column_iter_pair
        PathNodeRootMatrix::GetFindedEdgeColumnIter(void) const{
    return finded_included_edge_column_;
}

matrix_unique_ptr PathNodeRootMatrix::GetMatrixCopy(void) const{
    return matrix_unique_ptr(new matrix_type(*matrix_));
}

bool PathNodeRootMatrix::IsIncludedEdgeNode(void) const{
    return is_included_;
}

bool PathNodeRootMatrix::IsMatrixEmpty(void) const{
    return is_empty_;
}

coordinate PathNodeRootMatrix::ReducedCellsEvaluating(void){
    return CellsEvaluating_();
}

void PathNodeRootMatrix::FieldInitialization_(int from_node, int to_node){
    from_vertex_ = from_node;
    to_vertex_ = to_node;
    is_empty_ = 0;
}

void PathNodeRootMatrix::CostDeterminingPathNode_(void){
    RowCellsReduced_();
    ColumnCellsReduced_();
}



PathNodeIncludeMatrix::PathNodeIncludeMatrix(PathNodeRootMatrix& matrix){
    is_included_ = 1;
    FieldInitialization_(
        matrix.GetFindedEdgeRowIter().first,
        matrix.GetFindedEdgeColumnIter().first
    );
    RestructMatrix_(matrix);
    CostDeterminingPathNode_(matrix.GetWayCost());
}

void PathNodeIncludeMatrix::RestructMatrix_(PathNodeRootMatrix& matrix){
    matrix_ = matrix.GetMatrixCopy();
    for (auto row : (*matrix_)){
        row.erase(row.begin() + to_node);
    }

}

void PathNodeIncludeMatrix::CostDeterminingPathNode_(int current_way_cost){
    RowCellsReduced_();
    ColumnCellsReduced_();
    way_cost_ += current_way_cost;
}



PathNodeNotIncludeMatrix::PathNodeNotIncludeMatrix(PathNodeRootMatrix& matrix){
    row_iter_pair& from_node = matrix.GetFindedEdgeRowIter();
    column_iter_pair& to_node = matrix.GetFindedEdgeColumnIter();

    is_included_ = 0;
    FieldInitialization_(from_node.first, to_node.first);
    CostDeterminingPathNode_(matrix.GetWayCost(), *(to_node.second));
    RestructMatrix_(matrix, to_node.second);
}

coordinate PathNodeNotIncludeMatrix::ReducedCellsEvaluating(void){
    RowCellsReduced_();
    ColumnCellsReduced_();
    return CellsEvaluating_();
}

void PathNodeNotIncludeMatrix::CostDeterminingPathNode_(int current_way_cost,
                                                    int current_cell_score){
    way_cost_ = current_way_cost + current_cell_score;
}

void PathNodeNotIncludeMatrix::RestructMatrix_(PathNodeRootMatrix& matrix,
                                    row_matrix_type::iterator& cell_it){
    matrix_ = matrix.GetMatrixCopy();
    (*(matrix.GetFindedEdgeColumnIter().second)) = std::numeric_limits<int>::max();
}

}
