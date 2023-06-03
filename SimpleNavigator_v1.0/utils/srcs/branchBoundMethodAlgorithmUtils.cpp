#include "../includes/branchBoundMethodAlgorithmUtils.hpp"

namespace s21{

matrix_unique_ptr bbma_utils::InitialMatrix(
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

bool NodesCostCompare(const PathNodeRootMatrix& a, const PathNodeRootMatrix& b){
    return a.GetWayCost() < b.GetWayCost();
}

}