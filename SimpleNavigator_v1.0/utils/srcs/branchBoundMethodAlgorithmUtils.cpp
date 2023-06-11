#include "../includes/branchBoundMethodAlgorithmUtils.hpp"

namespace s21{

matrix_pair_unique_ptr BbmaUtils::InitialMatrix(
                    const Graph& graph){
    matrix_pair_unique_ptr matrix(new matrix_pair_type);
    std::vector<coorsinate_cell> current_row;
    int current_cell_value;

    for(int row_i = 0; row_i < (int)graph.Size(); row_i++){
        for(int column_i = 0; column_i < (int)graph[row_i].size(); column_i++){
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

BbmaUtils::multiset_type::iterator BbmaUtils::AddWayNodesToUnforkedNodes(
                                multiset_type& unforked_nodes,
                                PathNodeRootMatrix& matrix_node){
    multiset_type::iterator included_path_it;

    included_path_it = unforked_nodes.insert(
        node_shared_ptr(new PathNodeIncludeMatrix(matrix_node))
    );
    unforked_nodes.insert(
        node_shared_ptr(new PathNodeNotIncludeMatrix(matrix_node))
    );
    return included_path_it;
}

TsmResult BbmaUtils::FinalPathFormation(coordinates way, double way_cost){
    if (way.empty()) {
        throw "Throw from BbmaUtils::FinalPathFormation(): empty way";
    }
    TsmResult hamiltonian_path;
    coordinates_iter current_edge_it;
    int current_from;
    int current_to;

    hamiltonian_path.distance = way_cost;
    current_edge_it = way.begin();
    current_from = (*current_edge_it)[0];
    hamiltonian_path.vertices.push_back(current_from);
    while (!way.empty()){
        current_to = (*current_edge_it)[1];
        hamiltonian_path.vertices.push_back(current_to);
        way.erase(current_edge_it);
        current_from = current_to;
        current_edge_it = FindNextNode_(way, current_from);
    }
    return hamiltonian_path;
}

coordinates_iter BbmaUtils::FindNextNode_(coordinates way,
                                                int finded_from){
    if (way.empty()) { return way.end(); }
    for (coordinates_iter edge = way.begin(); edge != way.end(); ++edge){
        if ((*edge)[0] == finded_from) {
            return edge;
        }
    }
    throw "Throw from BbmaUtils::FindNextNode_(): ";
}



bool NodesCostCompare(const node_shared_ptr& a, const node_shared_ptr& b){
    return a->GetWayCost() < b->GetWayCost();
}

}
