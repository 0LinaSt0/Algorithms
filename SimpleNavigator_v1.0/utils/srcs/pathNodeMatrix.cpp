#include "../includes/pathNodeMatrix.hpp"

namespace s21{

PathNodeRootMatrix::PathNodeRootMatrix(matrix_unique_ptr matrix) 
    : matrix_(std::move(matrix)), from_vertex_(0), to_vertex_(0){
    CostDeterminingPathNode_();
}

matrix_reference PathNodeRootMatrix::operator[](matrix_type::size_type pos){
    return (*matrix_).operator[](pos);
}

matrix_const_reference PathNodeRootMatrix::operator[](
                                matrix_type::size_type pos) const{
    return (*matrix_).operator[](pos);
}

int PathNodeRootMatrix::GetWayCost(void) const{
    return way_cost_;
}

coordinate PathNodeRootMatrix::GetPathNodeVertices(void) const{
    return coordinate{from_vertex_, to_vertex_};
}

matrix_unique_ptr PathNodeRootMatrix::GetMatrixCopy(void) const{
    return matrix_unique_ptr(new matrix_type(*matrix_));
}

coordinate PathNodeRootMatrix::ReducedCellsEvaluating(void){
    void;
}

void PathNodeRootMatrix::FieldInitialization_(int from_node, int to_node){
    from_vertex_ = from_node; 
    to_vertex_ = to_node;
}

void PathNodeRootMatrix::CostDeterminingPathNode_(void){
    void;
}


PathNodeIncludeMatrix::PathNodeIncludeMatrix(PathNodeRootMatrix& matrix, 
    int from_node, int to_node){
    FieldInitialization_(from_node, to_node);
    RestructMatrix_(matrix, from_node, to_node);
    CostDeterminingPathNode_(matrix.GetWayCost());
}

coordinate PathNodeIncludeMatrix::ReducedCellsEvaluating(void){
    void;
}

void PathNodeIncludeMatrix::RestructMatrix_(PathNodeRootMatrix& matrix, 
                                        int from_node, int to_node){
    void;
}

void PathNodeIncludeMatrix::CostDeterminingPathNode_(int current_way_cost){
    void;
}



PathNodeNotIncludeMatrix::PathNodeNotIncludeMatrix(PathNodeRootMatrix& matrix, 
    int from_node, int to_node){
    FieldInitialization_(from_node, to_node);
    CostDeterminingPathNode_(matrix.GetWayCost(), matrix[from_node][to_node]);
    RestructMatrix_(matrix, from_node, to_node);
}

coordinate PathNodeNotIncludeMatrix::ReducedCellsEvaluating(void){
    void;
}

void PathNodeNotIncludeMatrix::CostDeterminingPathNode_(int current_way_cost, 
                                                    int current_cell_score){
    way_cost_ = current_way_cost + current_cell_score;
}

void PathNodeNotIncludeMatrix::RestructMatrix_(PathNodeRootMatrix& matrix, 
                                        int from_node, int to_node){
    matrix_ = matrix.GetMatrixCopy();
    (*matrix_)[from_node][to_node] = std::numeric_limits<int>::max();
}

}