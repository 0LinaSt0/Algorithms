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

bbma_utils::multiset_type::iterator bbma_utils::AddWayNodesToUnforkedNodes(
                                multiset_type& unforked_nodes,
                                PathNodeRootMatrix& matrix_node,
                                int from_node, int to_node){
    multiset_type::iterator included_path_it;

    included_path_it = unforked_nodes.insert(
        node_shared_ptr(
            new PathNodeIncludeMatrix(matrix_node, from_node, to_node)
        )
    );
    unforked_nodes.insert(
        node_shared_ptr(
            new PathNodeNotIncludeMatrix(matrix_node, from_node, to_node)
        )
    );
    return included_path_it;
}



bool NodesCostCompare(const node_shared_ptr& a, const node_shared_ptr& b){
    return a->GetWayCost() < b->GetWayCost();
}

}
