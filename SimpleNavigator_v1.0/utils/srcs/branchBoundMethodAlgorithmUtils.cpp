#include "../includes/branchBoundMethodAlgorithmUtils.hpp"

namespace s21{

bbma_utils::matrix_pair_unique_ptr bbma_utils::InitialMatrix(
                    const Graph& graph){
    matrix_pair_unique_ptr matrix(new matrix_pair_type);
    std::vector<coorsinate_cell> current_row;
    int current_cell_value;

    for(int row_i = 0; row_i < graph.Size(); row_i++){
        for(int column_i = 0; column_i < graph[row_i].size(); column_i++){
            current_cell_value = !graph[row_i][column_i] ?
                                std::numeric_limits<int>::max() :
                                graph[row_i][column_i];
            current_row.push_back(
                std::pair<coordinate, int>(
                    std::array<int, 2>{row_i, column_i},
                    current_cell_value
                )
            );
        }
        matrix->push_back(std::move(current_row));
    }
    return matrix;
}

bbma_utils::multiset_type::iterator bbma_utils::AddWayNodesToUnforkedNodes(
                                multiset_type& unforked_nodes,
                                PathNodeRootMatrix& matrix_node,
                                int from_node, int to_node){
    multiset_type::iterator included_path_it;

    included_path_it = unforked_nodes.insert(
        node_shared_ptr(new PathNodeIncludeMatrix(matrix_node))
    );
    unforked_nodes.insert(
        node_shared_ptr(new PathNodeNotIncludeMatrix(matrix_node))
    );
    return included_path_it;
}

TsmResult bbma_utils::FinalPathFormation(const coordinates& way,
                                double way_cost){

}


bool NodesCostCompare(const node_shared_ptr& a, const node_shared_ptr& b){
    return a->GetWayCost() < b->GetWayCost();
}

}
