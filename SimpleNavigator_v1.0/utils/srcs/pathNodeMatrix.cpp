#include "../includes/pathNodeMatrix.hpp"

namespace s21{

PathNodeMatrix::PathNodeMatrix(matrix_unique_ptr matrix, 
    int from_node, int to_node, int current_way_cost, 
    int(*costDetermining)(int, matrix_type&, coordinates&)) : 
    matrix_(std::move(matrix)){
    tree_node_.from_vertex_ = from_node;
    tree_node_.to_vertex_ = to_node;
    costDetermining(current_way_cost, *matrix_, reducing_nodes_);
}

int PathNodeMatrix::GetWayCost(void) const{
    return tree_node_.way_cost_;
}

coordinate PathNodeMatrix::GetPathNodeVertices(void) const{
    return coordinate{tree_node_.from_vertex_, tree_node_.to_vertex_};
}

coordinate PathNodeMatrix::ReducedCellsEvaluating(void){
    return coordinate();
}

}