#include "../includes/pathNodeMatrix.hpp"

namespace s21{

PathNodeRootMatrix::PathNodeRootMatrix(matrix_pair_unique_ptr matrix)
    : matrix_(std::move(matrix)), from_vertex_(0),
    to_vertex_(0), is_included_(false), is_empty_(false){
    CostDeterminingPathNode_();
}

PathNodeRootMatrix::matrix_pair_ref PathNodeRootMatrix::operator[](
                                                matrix_type::size_type pos){
    return (*matrix_).operator[](pos);
}

PathNodeRootMatrix::matrix_const_pair_ref PathNodeRootMatrix::operator[](
                                             matrix_type::size_type pos) const{
    return (*matrix_).operator[](pos);
}

double PathNodeRootMatrix::GetWayCost(void) const{
    return way_cost_;
}

coordinate PathNodeRootMatrix::GetPathNodeVertices(void) const{
    return coordinate{from_vertex_, to_vertex_};
}

PathNodeRootMatrix::row_matrix_iter
        PathNodeRootMatrix::GetFindedEdgeRowIter(void) const{
    return finded_edge_row_it_;
}

PathNodeRootMatrix::column_matrix_iter
        PathNodeRootMatrix::GetFindedEdgeColumnIter(void) const{
    return finded_edge_column_it_;
}

matrix_pair_unique_ptr PathNodeRootMatrix::GetMatrixCopy(
                                                                    void) const{
    return matrix_pair_unique_ptr(new matrix_pair(*matrix_));
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
    matrix_map::iterator selected_column_it;
    double selected_grade;
    int selected_row_i;
    int current_grade;

    selected_row_i = 0;
    selected_column_it = reducing_nodes_.begin();
    selected_grade = 0;
    for (matrix_map::iterator column_it = reducing_nodes_.begin();
            column_it != reducing_nodes_.end();
            ++column_it){
        for (int row_i = 0; row_i < (int)column_it->second.size(); row_i++){
            current_grade = CellGradeDeterminig_(row_i, column_it->first);
            if (current_grade > selected_grade){
                selected_row_i = row_i;
                selected_column_it = column_it;
                selected_grade = current_grade;
                if (selected_grade == std::numeric_limits<int>::max()){
                    break;
                }
            }
        }
    }
    (*matrix_)[selected_row_i][selected_column_it->first].second =
                                                                selected_grade;
    return FindedCellCoordenates_(selected_row_i, selected_column_it->first);
}

void PathNodeRootMatrix::RowCellsReduced_(void){
    if (is_empty_) { return ; }

    column_matrix_iter current_column_it;
    int selected_column_i;
    int selected_cell_value;

    for (int row_i = 0; row_i != (int)matrix_->size(); row_i++){
        current_column_it = std::min_element(
            (*matrix_)[row_i].begin(), (*matrix_)[row_i].end()
        );
        if (current_column_it->second == std::numeric_limits<int>::max()){
            throw "Throw from PathNodeRootMatrix::RowCellsReduced_()";
        }
        selected_cell_value = current_column_it->second;
        selected_column_i = current_column_it - (*matrix_)[row_i].begin();
        reducing_nodes_[selected_column_i].push_back(row_i);
        if (selected_cell_value){
            for (int column_i = 0;
                    column_i != (int)(*matrix_)[row_i].size();
                    column_i++){
                if ((*matrix_)[row_i][column_i].second !=
                                            std::numeric_limits<int>::max()){
                    (*matrix_)[row_i][column_i].second -= selected_cell_value;
                }
            }
            way_cost_ += selected_cell_value;
        }
    }
}

void PathNodeRootMatrix::ColumnCellsReduced_(void){
    if (is_empty_) { return ; }

    int selected_row_i;
    int selected_cell_value;

    for (int column_i = 0; column_i != (int)(*matrix_)[0].size(); column_i++){
        selected_row_i = FindMinInColumn_(column_i);
        if ((*matrix_)[selected_row_i][column_i].second == 
                std::numeric_limits<int>::max()){
            throw "Throw from PathNodeRootMatrix::ColumnCellsReduced_()";
        }
        selected_cell_value = (*matrix_)[selected_row_i][column_i].second;
        if (std::find(
                reducing_nodes_.find(column_i)->second.begin(),
                reducing_nodes_.find(column_i)->second.end(),
                selected_row_i
                ) == reducing_nodes_.find(column_i)->second.end()){
            reducing_nodes_[column_i].push_back(selected_row_i);
        }
        if (selected_cell_value){
            for (int row_i = 0; row_i != (int)matrix_->size(); row_i++){
                if ((*matrix_)[row_i][column_i].second !=
                        std::numeric_limits<int>::max()){
                    (*matrix_)[row_i][column_i].second -= selected_cell_value;
                }
            }
            way_cost_ += selected_cell_value;
        }
    }
}

int PathNodeRootMatrix::FindMinInColumn_(int column_i){
    int min_i;

    min_i = 0;
    for (int row_i = 0; row_i != (int)matrix_->size(); row_i++){
        if ((*matrix_)[row_i][column_i].second <
                (*matrix_)[min_i][column_i].second
            ){
            min_i = row_i;
        }
    }
    return min_i;
}

double PathNodeRootMatrix::CellGradeDeterminig_(int row_i, int column_i){
    double result;
    int min_row_elem;
    int min_column_elem;

    min_row_elem = std::min_element(
        (*matrix_)[row_i].begin(), (*matrix_)[row_i].end()
    )->second;
    if (min_row_elem == std::numeric_limits<int>::max()){
        result = min_row_elem;
    } else {
        min_column_elem = FindMinInColumn_(column_i);
        if (min_column_elem == std::numeric_limits<int>::max()){
            result = min_column_elem;
        } else {
            result = min_row_elem + min_column_elem;
        }
    }
    return result;
}

coordinate PathNodeRootMatrix::FindedCellCoordenates_(int row_i, int column_i){
    finded_edge_row_it_ = matrix_->begin() + row_i;
    finded_edge_column_it_ = (*matrix_)[row_i].begin() + column_i;

    return coordinate{
        (*matrix_)[row_i][column_i].first[0],
        (*matrix_)[row_i][column_i].first[1]
    };
}



PathNodeIncludeMatrix::PathNodeIncludeMatrix(PathNodeRootMatrix& matrix_node){
    is_included_ = true;
    FieldInitialization_(
        matrix_node.GetFindedEdgeColumnIter()->first[0],
        matrix_node.GetFindedEdgeColumnIter()->first[1]
    );
    RestructMatrix_(matrix_node);
    CostDeterminingPathNode_(matrix_node.GetWayCost());
}

void PathNodeIncludeMatrix::RestructMatrix_(PathNodeRootMatrix& matrix_node){
    int row_i;
    int column_i;

    matrix_ = matrix_node.GetMatrixCopy();
    row_i = matrix_node.GetFindedEdgeRowIter() - matrix_->begin();
    column_i = matrix_node.GetFindedEdgeColumnIter() -
                                                    (*matrix_)[row_i].begin();
    matrix_->erase(matrix_->begin() + row_i);
    for (auto& row : (*matrix_)){
        row.erase(row.begin() + column_i);
    }
    if (matrix_->empty()){
        is_empty_ = true;
    } else {
        InfToInversePath_(column_i, row_i);
    }
}

void PathNodeIncludeMatrix::CostDeterminingPathNode_(int current_way_cost){
    PathNodeRootMatrix::CostDeterminingPathNode_();
    way_cost_ += current_way_cost;
}

void PathNodeIncludeMatrix::InfToInversePath_(int row_coordinate,
                                int column_coordinate){
    int current_i;
    int row_elem_i;
    int column_elem_i;

    row_elem_i = 0;
    column_elem_i = 0;
    for (;current_i < (int)(*matrix_).size(); current_i++){
        if ((*matrix_)[current_i][0].first[0] == row_coordinate){
            row_elem_i = current_i;
            break ;
        } else if ((*matrix_)[current_i][0].first[0] > row_coordinate){
            return ;
        }
    }
    if (row_elem_i == 0 && current_i == (int)(*matrix_).size()) { return ; }
    for (;current_i < (int)(*matrix_)[row_elem_i].size(); current_i++){
        if ((*matrix_)[row_elem_i][current_i].first[1] == column_coordinate){
            column_elem_i = current_i;
            break ;
        } else if ((*matrix_)[row_elem_i][current_i].first[1] >
                    column_coordinate){
            return ;
        }
    }
    if (column_elem_i == 0 && current_i == (int)(*matrix_)[row_elem_i].size()) {
        return ;
    }
    (*matrix_)[row_elem_i][column_elem_i].second =
                                                std::numeric_limits<int>::max();
}



PathNodeNotIncludeMatrix::PathNodeNotIncludeMatrix(
                            PathNodeRootMatrix& matrix_node){
    column_matrix_iter node_it = matrix_node.GetFindedEdgeColumnIter();

    is_included_ = false;
    FieldInitialization_(node_it->first[0], node_it->first[1]);
    CostDeterminingPathNode_(matrix_node.GetWayCost(), node_it->second);
    RestructMatrix_(matrix_node);
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

void PathNodeNotIncludeMatrix::RestructMatrix_(PathNodeRootMatrix& matrix_node){
    int row_i;
    int column_i;

    matrix_ = matrix_node.GetMatrixCopy();
    row_i = matrix_node.GetFindedEdgeRowIter() - matrix_->begin();
    column_i = matrix_node.GetFindedEdgeColumnIter() -
                                                    (*matrix_)[row_i].begin();
    (*matrix_)[row_i][column_i].second = std::numeric_limits<int>::max();
}

}
