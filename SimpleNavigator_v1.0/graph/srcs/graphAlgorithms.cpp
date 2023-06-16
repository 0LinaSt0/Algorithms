#include "../includes/graphAlgorithms.hpp"

namespace s21{

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                        int start_vertex){
    (void)graph; (void)start_vertex;

    if (start_vertex < 0 || start_vertex > static_cast<int>(graph.Size())){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,  "Invalid vertex number");
        return {};
    }

    std::vector<int> result;
    result.reserve(graph.Size());
    std::vector<bool> visited(graph.Size(), false);
    s21::Queue<int> q;

    q.push(start_vertex);
    visited[start_vertex] = true;

    while (q.size()){
        int start = q.front();
        q.pop();
        result.push_back(start);

        for (int v = 0; v < static_cast<int>(graph.Size()); v++){
            if (visited[v] || !graph.at(start, v)) continue;
            q.push(v);
            visited[v] = true;
        }
    }

    return result;
}

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                    int start_vertex){
    if(!graph.Size()) { return std::vector<int>(); }

    std::vector<int> nodes_road;
    s21::Stack<int> current_vertices;
    std::vector<int> is_in_sets(graph.Size(), 0); // -1 - in stack; 0 - not in sets; 1 - in arr
    int current_vertex;

    current_vertex = start_vertex;
    nodes_road.push_back(current_vertex);
    is_in_sets[current_vertex] = 1;
    while (true){
        for(int bind_vertex_i = graph[current_vertex].size() - 1;
            bind_vertex_i >= 0;
            bind_vertex_i--
        ){
            if (graph[current_vertex][bind_vertex_i] > 0 &&
                is_in_sets[bind_vertex_i] == 0
            ){
                current_vertices.push(bind_vertex_i);
                is_in_sets[bind_vertex_i] = -1;
            }
        }
        current_vertex = current_vertices.top();
        nodes_road.push_back(current_vertex);
        current_vertices.pop();
        is_in_sets[current_vertex] = 1;
        if (current_vertices.empty()){ break; }
    }
    return nodes_road;
}

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph& graph, int vertex1,
                                                        int vertex2){
    Queue<int> q;
    std::vector<bool> visited(graph.Size(), false);
    std::vector<int> values(graph.Size(), INT_MAX);
    q.push(vertex1);
    values[vertex1] = 0;

    while (q.size()){
        int start = q.front();

        for (int i = 0; i < static_cast<int>(graph.Size()); i++){
            if (i == start) continue;
            if (graph.at(start, i) == 0) continue;
            int new_val = values[start] + graph.at(start, i);
            if (new_val < values[i]) values[i] = new_val;
            if (!visited[i]) q.push(i);
        }

        visited[start] = true;
        q.pop();
    }

    return (values[vertex2] == INT_MAX) ? 0 : values[vertex2];
}

Graph GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph){
    if(!graph.Size()) { return Graph(); }

    std::size_t graph_size = graph.Size();
    Graph FWL_matrix(graph);

    for (std::size_t throgh_node = 0; throgh_node < graph_size; throgh_node++){
        for (std::size_t row = 0; row < graph_size; row++){
            for (std::size_t column = 0; column < graph_size; column++){
                if (row == column) {
                    FWL_matrix[row][column] = 0;
                } else {
                    FWL_matrix[row][column] = MinWeight_(
                        FWL_matrix, column, row, throgh_node
                    );
                }
            }
        }
    }
    return FWL_matrix;
}

Graph GraphAlgorithms::GetLeastSpanningTree(Graph& graph){
    using edge_type = std::pair<int, int>;
    if (!graph.Size()) return Graph();

    size_t min_spanning_tree_size = SIZE_T_MAX;
    Graph result_graph;

    for (size_t i = 0; i < graph.Size(); i++){
        std::vector<bool> visited(graph.Size(), false);
        visited[i] = true;
        size_t visited_count = 1;
        size_t spanning_tree_size = 0;

        // new matrix with min spanning tree only 
        std::vector<std::vector<int>> mtrx(graph.Size(),
                                            std::vector<int>(graph.Size(), 0));

        // find non visited min edge
        auto find_min = [](const Graph& graph,
                            const std::vector<bool>& visited){
            const int size = static_cast<int>(graph.Size());
            int min_edge_value = INT_MAX;
            edge_type min_edge = {-1, -1};

            for (int begin = 0; begin < size; begin++){
                for (int end = 0; end < size; end++){
                    if (visited[begin] == visited[end]) continue;
                    if (graph[begin][end] == 0) continue;
                    if (graph[begin][end] < min_edge_value){
                        min_edge_value = graph[begin][end];
                        min_edge.first = begin;
                        min_edge.second = end;
                    }
                }
            }

            return min_edge;
        };

        while (true){
            edge_type min_edge = find_min(graph, visited);
            if (min_edge.first == -1) {
                break;
            }

            mtrx[min_edge.first][min_edge.second] = 
                graph.at(min_edge.first, min_edge.second);
            if (graph.at(min_edge.first, min_edge.second) == 
                    graph.at(min_edge.second, min_edge.first)){
                mtrx[min_edge.second][min_edge.first] = 
                    graph.at(min_edge.second, min_edge.first);
            }
                    
            visited_count++;
            visited[min_edge.first] = visited[min_edge.second] = true;
            spanning_tree_size += graph.at(min_edge.first, min_edge.second);
            if (visited_count == graph.Size()) {
                if (spanning_tree_size < min_spanning_tree_size){
                    min_spanning_tree_size = spanning_tree_size;
                    result_graph = std::move(Graph(std::move(mtrx),
                                                    spanning_tree_size));
                }
            }
        }
    }

    if (!result_graph.Size())
        throw std::invalid_argument("Cannot find least spanning tree");
    return result_graph;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph){
    if (IsInappropriateGraph_(graph)){ return {}; }

    TsmResult return_path;
    std::vector<std::vector<double>> pheromones(
        graph.Size(), std::vector<double>(graph.Size(), 0)
    );
    std::unique_ptr<std::vector<Ant>> ants = ants_utils_->AntsColony(graph);

    while (!ants->empty()){
        Ant* ant;
        for (size_t ant_index = 0; ant_index < ants->size(); ant_index++){
            ant = &(*ants)[ant_index];
            ant->ChooseNextNode(
                graph[ant->CurrentNode()],
                pheromones[(ant->CurrentNode())]
            );
            // if (ant->StartNode() == 1){
            //     std::cout << "ANT NO " << ant->StartNode() << ":";
            //     ant->CurrentWay().tmp_print_DELETEME();
            //     std::cout << "\t end status: " << ant->EndCodeStatus() <<std::endl;
            // }
        }
        // std::cout << "HEEEEEEEEEEEEE" <<std::endl;
        for (std::vector<Ant>::iterator ant_it = ants->begin(); 
                ant_it < ants->end();){
            ant = &(*ant_it);
            if (ant->BadWayCount() == 0){
                if (ant->CurrentWay().vertices.size() > 1){
                    ants_utils_->RefreshPheromones(
                        ant->FromNode(), ant->CurrentNode(), graph, pheromones
                    );
                }
                if (ant->EndCodeStatus() == 1){
                    return_path = std::move(ants_utils_->UpdateReturnedWay(
                        ant->BestWay(), return_path
                    ));
                    ant_it = ants->erase(ant_it);
                } else {
                    ++ant_it;
                }
            } else {
                if (ant->EndCodeStatus() == 2){
                    ant_it = ants->erase(ant_it);
                } else {
                    ++ant_it;
                }
            }
        }
        ants_utils_->PheromoneEvaporation(pheromones);
    }
    if (return_path.vertices.empty()){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, INAPPROPRIATE_GRAPH_MSG);
    }
    return return_path;
}

TsmResult GraphAlgorithms::STSPBranchBoundMethodAlgorithm(Graph &graph){
    if (IsInappropriateGraph_(graph)){ return {}; }
    
    try {
        node_shared_ptr current_node(
            new PathNodeRootMatrix(bbmethod_utils_->InitialMatrix(graph))
        );
        multyset_type unforked_nodes(NodesCostCompare);
        coordinate current_edge{current_node->ReducedCellsEvaluating()};
        coordinates way;
        multyset_iterator_type current_included_it;

        while(1){
            current_included_it = bbmethod_utils_->AddWayNodesToUnforkedNodes(
                unforked_nodes, *current_node
            );
            current_node = *current_included_it;
            if (current_node->IsMatrixEmpty()){
                way.push_back(current_edge);
                break ;
            }
            if ((*current_included_it)->GetWayCost() >
                (*unforked_nodes.begin())->GetWayCost()){
                current_included_it = unforked_nodes.begin();
                current_node = *current_included_it;
            }
            if (current_node->IsIncludedEdgeNode()){
                way.push_back(current_edge);
            }
            current_edge = current_node->ReducedCellsEvaluating();
            unforked_nodes.erase(current_included_it);
        }
        return bbmethod_utils_->FinalPathFormation(
            way, current_node->GetWayCost()
        );
    } catch (std::invalid_argument& e) {
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, INAPPROPRIATE_GRAPH_MSG);
        std::cout << std::string(e.what()) << std::endl;
        return TsmResult();
    }
}

TsmResult GraphAlgorithms::ExhaustiveSearch(Graph &graph) const{
    if (IsInappropriateGraph_(graph)) return {};

    double res_row_weight = DBL_MAX;
    std::vector<int> res_row;

    for (size_t i = 0; i < graph.Size(); i++){
        std::vector<int> root_row;
        root_row.push_back(static_cast<int>(i));
        double row_weight = DBL_MAX;
        std::vector<int> row;

        ExhaustiveSearch_(
            row_weight,
            row,
            root_row,
            graph
        );

        if (row.size() && row_weight < res_row_weight){
            res_row_weight = row_weight;
            res_row = std::move(row);
        }
    }

    if (!res_row.size()) {
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, INAPPROPRIATE_GRAPH_MSG);
    }
    return { res_row, res_row_weight };
}

int GraphAlgorithms::MinWeight_(Graph &matrix, int column, int row,
                        int throgh_node){
    int direct_weight, indirect_weight, result_weight;

    direct_weight = matrix[row][column];
    indirect_weight = matrix[row][throgh_node] && matrix[throgh_node][column] ?
                    (matrix[row][throgh_node] + matrix[throgh_node][column]) :
                    0;

    if (!direct_weight) {
        result_weight = indirect_weight;
    } else if (!indirect_weight) {
        result_weight = direct_weight;
    } else {
        result_weight = std::minmax(
            std::initializer_list<int>{direct_weight, indirect_weight}
        ).first;
    }
    return result_weight;
}

bool GraphAlgorithms::ExhaustiveSearch_(double& min_row_weight,
                                            std::vector<int>& min_row,
                                            const std::vector<int>& parent_row,
                                            const Graph& graph) const{
    // to calculate weight of graph row
    auto row_weight = [](const std::vector<int>& row, const Graph& graph){
        int weight = 0;

        for (size_t i = 0; i + 1 < row.size(); i++){
            weight += graph.at(row[i], row[i + 1]);
        }

        return weight;
    };
    // check if row contains all verticex
    auto check_if_full = [](const std::vector<int>& row, const Graph& graph){
        std::set<int> unique_values(row.begin(), row.end());
        return row.front() == 0 && row.back() == 0 &&
                unique_values.size() == graph.Size();
    };
    
    for (size_t y = 0; y < graph.Size(); y++){
        // check if edge exists
        if (graph.at(parent_row.back(), y) == 0) continue;

        // check if new element is already in row
        std::vector<int>::const_iterator iter = std::find(
            parent_row.begin(),
            parent_row.end(),
            y
        );
            
        if (parent_row.size() == graph.Size()) {
            if (y != static_cast<size_t>(parent_row.front())){
                continue;
            }
        } else if (iter != parent_row.end()) {
            continue;
        }
        
        // parent's copy to be appended
        std::vector<int> new_row(parent_row);
        new_row.push_back(y);

        const bool is_full = check_if_full(new_row, graph);
        const int new_row_weight = row_weight(new_row, graph);
        if (new_row_weight >= min_row_weight) continue;
        if (is_full){
            if (new_row_weight < min_row_weight) {
                min_row_weight = new_row_weight;
                min_row = std::move(new_row);
            }
        } else {
            ExhaustiveSearch_(
                min_row_weight,
                min_row,
                new_row,
                graph
            );
        }
    }

    return true;
}

bool GraphAlgorithms::IsInappropriateGraph_(const Graph& graph) const{
    if (!graph.Size() || !graph.IsConnected()){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, INAPPROPRIATE_GRAPH_MSG);
        return true;
    }
    return false;
}

}
