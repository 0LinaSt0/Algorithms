#include "../includes/pathNodeMatrix.hpp"

namespace s21{

PathNodeRootMatrix::PathNodeRootMatrix(matrix_pair_unique_ptr matrix)
    : matrix_(std::move(matrix)), from_vertex_(0),
    to_vertex_(0), way_cost_(0), is_included_(-1), is_empty_(false){
    // {
    //     for (auto& row : (*matrix_)){
    //         for (auto& elem : row){
    //             std::cout << elem.second << "\t";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    // }
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

coordinates PathNodeRootMatrix::GetCurrentWay(void) const{
    return current_way_;
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

PathNodeRootMatrix::row_matrix_iter PathNodeRootMatrix::Begin() const{
    return matrix_->begin();
}

matrix_pair_unique_ptr PathNodeRootMatrix::GetMatrixCopy(void) const{
    return matrix_pair_unique_ptr(new matrix_pair(*matrix_));
}

int PathNodeRootMatrix::IsIncludedEdgeNode(void) const{
    return is_included_;
}

bool PathNodeRootMatrix::IsMatrixEmpty(void) const{
    return is_empty_;
}

coordinate PathNodeRootMatrix::ReducedCellsEvaluating(void){
    return CellsEvaluating_();
}

void PathNodeRootMatrix::FieldInitialization_(PathNodeRootMatrix& matrix_node){
    current_way_ = matrix_node.GetCurrentWay();
    from_vertex_ = matrix_node.GetFindedEdgeColumnIter()->first[0];
    to_vertex_ = matrix_node.GetFindedEdgeColumnIter()->first[1];
    way_cost_ = 0;
    is_empty_ = 0;
}

void PathNodeRootMatrix::CostDeterminingPathNode_(void){
    RowCellsReduced_();
    ColumnCellsReduced_();
}

coordinate PathNodeRootMatrix::CellsEvaluating_(void){
    double selected_grade;
    int selected_column_i;
    int selected_row_i;
    int current_grade;

    selected_row_i = reducing_nodes_.begin()->second[0];
    selected_column_i = reducing_nodes_.begin()->first;
    selected_grade = CellGradeDeterminig_(selected_row_i, selected_column_i);
    for (matrix_map::iterator column_it = reducing_nodes_.begin();
            column_it != reducing_nodes_.end();
            ++column_it){
        for (auto row_it = column_it->second.begin(); 
                row_it < column_it->second.end(); 
                ++row_it){
                    // std::cout << "\t Grade: " << selected_grade
                    //         << "\t Row: " << (*row_it)
                    //         << "\t Column: " << column_it->first 
                    //         << std::endl;
                    // std::cout << "\t Grade: " << selected_grade
                    //         << "\t Row: " << (*matrix_)[*row_it][column_it->first].first[0]
                    //         << "\t Column: " << (*matrix_)[*row_it][column_it->first].first[1] 
                    //         << std::endl;
            current_grade = CellGradeDeterminig_((*row_it), column_it->first);
            if (current_grade > selected_grade){
                selected_row_i = (*row_it);
                selected_column_i = column_it->first;
                selected_grade = current_grade;
                if (selected_grade == std::numeric_limits<int>::max()){
                    // std::cout << "\t grade: " << selected_grade
                    //         << "\t row: " << selected_row_i
                    //         << "\t column: " << selected_column_i 
                    //         << std::endl;
                    break;
                }
            }
        }
        if (selected_grade == std::numeric_limits<int>::max()){
            break;
        }
    }
    (*matrix_)[selected_row_i][selected_column_i].second = selected_grade;
    return FindedCellCoordenates_(selected_row_i, selected_column_i);
}

void PathNodeRootMatrix::RowCellsReduced_(void){
    if (is_empty_) { return ; }

    int selected_column_i;
    int selected_cell_value;

    //  {
    //     for (auto& row : (*matrix_)){
    //         for (auto& elem : row){
    //             std::cout << elem.second << "   ";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    for (int row_i = 0; row_i != (int)matrix_->size(); row_i++){
        // for (auto& elem : (*matrix_)[row_i]){
        //     std::cout << elem.second << "  ";
        // }
        // std::cout << std::endl;
        selected_column_i = FindMinInRow_(row_i, -1);
        selected_cell_value = (*matrix_)[row_i][selected_column_i].second;
        if (selected_cell_value == std::numeric_limits<int>::max()){
            throw std::invalid_argument(
                "Throw from PathNodeRootMatrix::RowCellsReduced_()"
            );
        }
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
            if (is_included_ || is_included_ == -1){ 
                way_cost_ += selected_cell_value;
            }
        }
    }
}

void PathNodeRootMatrix::ColumnCellsReduced_(void){
    if (is_empty_) { return ; }

    int selected_row_i;
    int selected_cell_value;

    // {
    //     for (auto& row : (*matrix_)){
    //         for (auto& elem : row){
    //             std::cout << elem.second << "\t";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    for (int column_i = 0; column_i != (int)(*matrix_)[0].size(); column_i++){
        selected_row_i = FindMinInColumn_(column_i, -1);
        // std::cout << "MIN_ROW_I: " << selected_row_i << "  MIN_COLUMN: " << column_i << std::endl;
        if ((*matrix_)[selected_row_i][column_i].second == 
                std::numeric_limits<int>::max()){
            throw std::invalid_argument(
                "Throw from PathNodeRootMatrix::ColumnCellsReduced_()"
            );
        }
        selected_cell_value = (*matrix_)[selected_row_i][column_i].second;
            // {
            //     std::cout << "FROM_VERTEX: " << from_vertex_ << std::endl;
            //     std::cout << "FOR_COLUMN: " << column_i << std::endl;
            //     for (auto& elem : reducing_nodes_.find(column_i)->second){
            //             std::cout << elem << "\t";
            //         }
            //         std::cout << std::endl;
            //     std::cout << selected_row_i << std::endl;
            // }
        if ((reducing_nodes_.find(column_i)) == reducing_nodes_.end() || 
                std::find(
                reducing_nodes_.find(column_i)->second.begin(),
                reducing_nodes_.find(column_i)->second.end(),
                selected_row_i
            ) == reducing_nodes_.find(column_i)->second.end()){
            // std::cout << "\t Row: " << (*matrix_)[selected_row_i][column_i].first[0]
            //                 << "\t Column: " << (*matrix_)[selected_row_i][column_i].first[1] 
            //                 << std::endl;
            reducing_nodes_[column_i].push_back(selected_row_i);
        }
        if (selected_cell_value){
            for (int row_i = 0; row_i != (int)matrix_->size(); row_i++){
                if ((*matrix_)[row_i][column_i].second !=
                        std::numeric_limits<int>::max()){
                    (*matrix_)[row_i][column_i].second -= selected_cell_value;
                }
            }
            if (is_included_ || is_included_ == -1){ 
                way_cost_ += selected_cell_value;
            }
        }
    }
    // for(auto& column : reducing_nodes_){
    //     std::cout << "in column " << column.first << ": ";
    //     for(auto& elem : column.second){
    //         std::cout << elem << "  ";
    //     }
    //     std::cout << std::endl;
    // }
}

int PathNodeRootMatrix::FindMinInRow_(int row_i, int column){
    int min_i;

    min_i = 0;
        // std::cout << column << std::endl;
    for (int column_i = 0; column_i != (int)matrix_->size(); column_i++){
        // std::cout << (*matrix_)[row_i][column_i].second << "  ";
        if (((*matrix_)[row_i][column_i].second <
                (*matrix_)[row_i][min_i].second &&
                column_i != column) ||
                (min_i == column && column_i != column)
            ){
            min_i = column_i;
        }
    }
        // std::cout  << std::endl;
        // std::cout << min_i << std::endl << std::endl;
    return min_i;
}

int PathNodeRootMatrix::FindMinInColumn_(int column_i, int row){
    int min_i;

    min_i = 0;
    for (int row_i = 0; row_i != (int)matrix_->size(); row_i++){
        if (((*matrix_)[row_i][column_i].second <
                (*matrix_)[min_i][column_i].second &&
                row_i != row) ||
                (min_i == row && row_i != row)
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

    // {
    //     for (auto& row : (*matrix_)){
    //         for (auto& elem : row){
    //             std::cout << elem.second << "\t";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    min_row_elem = (*matrix_)[row_i][FindMinInRow_(row_i, column_i)].second;
    // std::cout << "\tMIN: " << min_row_elem << std::endl;
    // exit(0);
    if (min_row_elem == std::numeric_limits<int>::max()){
        result = min_row_elem;
    } else {
        min_column_elem = 
                    (*matrix_)[FindMinInColumn_(column_i, row_i)][column_i].second;
        if (min_column_elem == std::numeric_limits<int>::max()){
            result = min_column_elem;
        } else {
            result = min_row_elem + min_column_elem;
        }
    }
    return result;
}

coordinate PathNodeRootMatrix::FindedCellCoordenates_(int row_i, int column_i){
    coordinate returned{
        (*matrix_)[row_i][column_i].first[0],
        (*matrix_)[row_i][column_i].first[1]
    };
    finded_edge_row_it_ = matrix_->begin() + row_i;
    finded_edge_column_it_ = (*matrix_)[row_i].begin() + column_i;

    // for(auto& column : reducing_nodes_){
    //     std::cout << "in column " << column.first << ": ";
    //     for(auto& elem : column.second){
    //         std::cout << elem << "  ";
    //     }
    //     std::cout << std::endl;
    // }

    // {
    //     for (auto& row : (*matrix_)){
    //         for (auto& elem : row){
    //             std::cout << elem.second << "\t";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << (*matrix_)[row_i][column_i].first[0] << std::endl
    //         << (*matrix_)[row_i][column_i].first[1] << std::endl << std::endl;
    // std::cout << "Is_include: " << is_included_ << "   -> " << way_cost_ << std::endl;
    return returned;
}



PathNodeIncludeMatrix::PathNodeIncludeMatrix(PathNodeRootMatrix& matrix_node){
    is_included_ = true;
    FieldInitialization_(matrix_node);
    current_way_.push_back(
        coordinate{
            matrix_node.GetFindedEdgeColumnIter()->first[0],
            matrix_node.GetFindedEdgeColumnIter()->first[1]
        });
    RestructMatrix_(matrix_node);
    // {
    //     std::cout << "INCLUDE" << std::endl;
    //     for (auto& row : (*matrix_)){
    //         for (auto& elem : row){
    //             std::cout << elem.second << "\t";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    // }
    CostDeterminingPathNode_(matrix_node.GetWayCost());
}

void PathNodeIncludeMatrix::RestructMatrix_(PathNodeRootMatrix& matrix_node){
    int row_i;
    int column_i;

    matrix_ = matrix_node.GetMatrixCopy();
    row_i = matrix_node.GetFindedEdgeRowIter() - matrix_node.Begin();
    column_i = matrix_node.GetFindedEdgeColumnIter() -
                                    matrix_node.GetFindedEdgeRowIter()->begin();
    // std::cout << (*matrix_)[row_i][column_i].first[0] << "  " << (*matrix_)[row_i][column_i].first[1] << std::endl;
    InfToInversePath_((*matrix_)[row_i][column_i].first[0], (*matrix_)[row_i][column_i].first[1]);
        // for (auto& row : (*matrix_)){
        //         for (auto& elem : row){
        //             std::cout << "[" << elem.first[0] << "; " << elem.first[1] << "]" << "(" << elem.second << ")" << " ";
        //         }
        //         std::cout << std::endl;
        // }
    // std::cout << "\t\tDELETED_ROW: " << (*matrix_)[row_i][column_i].first[0]
    //          << "  DELETED_COLUMN: " << (*matrix_)[row_i][column_i].first[1]
    //          << std::endl;
    matrix_->erase(matrix_->begin() + row_i);
    for (auto& row : (*matrix_)){
        row.erase(row.begin() + column_i);
    }
    if (matrix_->empty()){
        is_empty_ = true;
    }
}

void PathNodeIncludeMatrix::CostDeterminingPathNode_(double current_way_cost){
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
    for (current_i = 0; current_i < (int)(*matrix_).size(); current_i++){
        if ((*matrix_)[current_i][0].first[0] == column_coordinate){
            row_elem_i = current_i;
            break ;
        } else if ((*matrix_)[current_i][0].first[0] > column_coordinate){
            return ;
        }
    }
    if (row_elem_i == 0 && current_i == (int)(*matrix_).size()) { return ; }
    for (current_i = 0; 
            current_i < (int)(*matrix_)[row_elem_i].size(); 
            current_i++){
        if ((*matrix_)[row_elem_i][current_i].first[1] == row_coordinate){
            column_elem_i = current_i;
            break ;
        } else if ((*matrix_)[row_elem_i][current_i].first[1] >
                    row_coordinate){
            return ;
        }
    }
    if (column_elem_i == 0 && current_i == (int)(*matrix_)[row_elem_i].size()) {
        return ;
    }
    // std::cout << "INV from " << (*matrix_)[row_elem_i][column_elem_i].first[0] 
    //          << " to " << (*matrix_)[row_elem_i][column_elem_i].first[1] << std::endl;
    (*matrix_)[row_elem_i][column_elem_i].second =
                                                std::numeric_limits<int>::max();
}



PathNodeNotIncludeMatrix::PathNodeNotIncludeMatrix(
                            PathNodeRootMatrix& matrix_node){
    column_matrix_iter node_it = matrix_node.GetFindedEdgeColumnIter();
    // std::cout << "NOT INCLUDE" << std::endl;
    // {
    //     std::cout << "NOT INCLUDE" << std::endl;
    //     for (auto& row : (*matrix_)){
    //         for (auto& elem : row){
    //             std::cout << elem.second << "\t";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    // }

    is_included_ = false;
    FieldInitialization_(matrix_node);
    CostDeterminingPathNode_(matrix_node.GetWayCost(), node_it->second);
    RestructMatrix_(matrix_node);
        // std::cout << "\tway_cost: " << way_cost_ << std::endl;

}

coordinate PathNodeNotIncludeMatrix::ReducedCellsEvaluating(void){
    RowCellsReduced_();
    ColumnCellsReduced_();
    return CellsEvaluating_();
}

void PathNodeNotIncludeMatrix::CostDeterminingPathNode_(double current_way_cost,
                                                    int current_cell_score){
    // std::cout << current_way_cost << "  -  " << current_cell_score << std::endl;
                                                        
    if (current_cell_score == std::numeric_limits<int>::max() ||
        current_way_cost == std::numeric_limits<int>::max()){
        way_cost_ = current_cell_score;
    } else {
        way_cost_ = current_way_cost + current_cell_score;
    }
}

void PathNodeNotIncludeMatrix::RestructMatrix_(PathNodeRootMatrix& matrix_node){
    int row_i;
    int column_i;

    matrix_ = matrix_node.GetMatrixCopy();
    row_i = matrix_node.GetFindedEdgeRowIter() - matrix_node.Begin();
    column_i = matrix_node.GetFindedEdgeColumnIter() -
                                    matrix_node.GetFindedEdgeRowIter()->begin();
    (*matrix_)[row_i][column_i].second = std::numeric_limits<int>::max();

    // std::cout << "INV from " << (*matrix_)[row_i][column_i].first[0] 
    //          << " to " << (*matrix_)[row_i][column_i].first[1] << std::endl;
    // for (auto& row : (*matrix_)){
    //             for (auto& elem : row){
    //                 std::cout << "[" << elem.first[0] << "; " << elem.first[1] << "]" << "(" << elem.second << ")" << " ";
    //             }
    //             std::cout << std::endl;
    //     }
}

}
