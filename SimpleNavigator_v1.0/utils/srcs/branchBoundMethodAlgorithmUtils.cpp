#include "../includes/branchBoundMethodAlgorithmUtils.hpp"

namespace s21{

matrix_unique_ptr BranchBoundMethodAlgoritmUtils::InitialMatrix(
                    const Graph& graph){
    matrix_unique_ptr matrix(new matrix_type);
    std::vector<int> current_row;
    int current_cell_value;

    for(Graph::const_iterator_type row = graph.Begin(); 
        row < graph.End(); 
        ++row){
        for(auto cell : (*row)){
            current_cell_value = !cell ? std::numeric_limits<int>::max() : cell;
            current_row.push_back(current_cell_value);
        }
        matrix->push_back(std::move(current_row));
    }
    return matrix;
}

int BranchBoundMethodAlgoritmUtils::CostDeterminingIncludingPathNode(
        int current_way_cost, matrix_type& matrix, coordinates& reducing_nodes){
    (void)current_way_cost;
    (void)matrix;
    (void)reducing_nodes;
    return 0;
}

int BranchBoundMethodAlgoritmUtils::CostDeterminingNotIncludingPathNode(
        int current_way_cost, matrix_type& matrix, coordinates& reducing_nodes){
    (void)current_way_cost;
    (void)matrix;
    (void)reducing_nodes;
    return 0;
}

}