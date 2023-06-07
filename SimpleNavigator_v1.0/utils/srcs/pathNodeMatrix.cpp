#include "../includes/pathNodeMatrix.hpp"

namespace s21{

PathNodeRootMatrix::PathNodeRootMatrix(matrix_unique_ptr matrix)
    : matrix_(std::move(matrix)), from_vertex_(0),
    to_vertex_(0), is_included_(false), is_empty_(false){
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

coordinate PathNodeRootMatrix::CellsEvaluating_(void){

}

void PathNodeRootMatrix::RowCellsReduced_(void){
    if (is_empty_) { return ; }

    column_matrix_iter_type current_column_it;
    size_t selected_column_i;
    size_t selected_cell_value;

    for (size_t row_i = 0; row_i != matrix_->size(); row_i++){
        current_column_it = std::min_element(
            (*matrix_)[row_i].begin(), (*matrix_)[row_i].end()
        );
        selected_cell_value = *current_column_it;
        selected_column_i = current_column_it - (*matrix_)[row_i].begin();
        reducing_nodes_[selected_column_i].push_back(row_i);
        if (selected_cell_value){
            for (size_t column_i = 0;
                    column_i != (*matrix_)[row_i].size();
                    column_i++){
                if ((*matrix_)[row_i][column_i] !=
                        std::numeric_limits<int>::max()){
                    (*matrix_)[row_i][column_i] -= selected_cell_value;
                }
            }
            way_cost_ += selected_cell_value;
        }
    }
}

void PathNodeRootMatrix::ColumnCellsReduced_(void){
    if (is_empty_) { return ; }

    size_t selected_row_i;
    size_t selected_cell_value;

    for (size_t column_i = 0; column_i != (*matrix_)[0].size(); column_i++){
        selected_row_i = FindMinInColumn_(column_i);
        selected_cell_value = (*matrix_)[selected_row_i][column_i];
        if (std::find(
                reducing_nodes_.find(column_i)->second.begin(),
                reducing_nodes_.find(column_i)->second.end(),
                selected_row_i
                ) == reducing_nodes_.find(column_i)->second.end()){
            reducing_nodes_[column_i].push_back(selected_row_i);
        }
        if (selected_cell_value){
            for (size_t row_i = 0; row_i != matrix_->size(); row_i++){
                if ((*matrix_)[row_i][column_i] !=
                        std::numeric_limits<int>::max()){
                    (*matrix_)[row_i][column_i] -= selected_cell_value;
                }
            }
            way_cost_ += selected_cell_value;
        }
    }
}

size_t PathNodeRootMatrix::FindMinInColumn_(size_t column_i){
    size_t min_i;

    min_i = 0;
    for (size_t row_i = 0; row_i != matrix_->size(); row_i++){
        if ((*matrix_)[row_i][column_i] < (*matrix_)[min_i][column_i]){
            min_i = row_i;
        }
    }
    return min_i;
}



PathNodeIncludeMatrix::PathNodeIncludeMatrix(PathNodeRootMatrix& matrix_node){
    is_included_ = true;
    FieldInitialization_(
        matrix_node.GetFindedEdgeRowIter().first,
        matrix_node.GetFindedEdgeColumnIter().first
    );
    RestructMatrix_(matrix_node);
    CostDeterminingPathNode_(matrix_node.GetWayCost());
}

void PathNodeIncludeMatrix::RestructMatrix_(PathNodeRootMatrix& matrix_node){
    matrix_iterator_type from_row_it;
    column_matrix_iter_type to_column_it;
    row_matrix_type::size_type deleted_index;

    matrix_ = matrix_node.GetMatrixCopy();
    from_row_it = matrix_node.GetFindedEdgeRowIter().second;
    to_column_it = matrix_node.GetFindedEdgeColumnIter().second;
    deleted_index = to_column_it - from_row_it->begin();
    matrix_->erase(from_row_it);
    for (auto row : (*matrix_)){
        row.erase(row.begin() + deleted_index);
    }
    if (matrix_->empty()){ is_empty_ = true; }
}

void PathNodeIncludeMatrix::CostDeterminingPathNode_(int current_way_cost){
    RowCellsReduced_();
    ColumnCellsReduced_();
    way_cost_ += current_way_cost;
}



PathNodeNotIncludeMatrix::PathNodeNotIncludeMatrix(
                            PathNodeRootMatrix& matrix_node){
    row_iter_pair& from_node = matrix_node.GetFindedEdgeRowIter();
    column_iter_pair& to_node = matrix_node.GetFindedEdgeColumnIter();

    is_included_ = false;
    FieldInitialization_(from_node.first, to_node.first);
    CostDeterminingPathNode_(matrix_node.GetWayCost(), *(to_node.second));
    RestructMatrix_(matrix_node, to_node.second);
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

void PathNodeNotIncludeMatrix::RestructMatrix_(PathNodeRootMatrix& matrix_node,
                                    column_matrix_iter_type& cell_it){
    matrix_ = matrix_node.GetMatrixCopy();
    *(cell_it) = std::numeric_limits<int>::max();
}

}
