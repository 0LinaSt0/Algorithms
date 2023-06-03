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
    const size_t size = graph.Size();

    std::vector<int> values(size, INT_MAX);
    std::vector<bool> visited(size, false);
    values[vertex1] = 0;

    auto find_min = [](const std::vector<int>& values,
                        const std::vector<bool>& visited){
        int minValue = -1, minIdx = -1;

        for (size_t i = 0; i < values.size(); i++){
            if (values[i] == -1 || visited[i]) continue;
            if (minValue == -1 || values[i] < minValue){
                minValue = values[i];
                minIdx = static_cast<int>(i);
            }
        }

        return minIdx;
    };

    int start;
    while (true){
        start = find_min(values, visited);
        if (start == -1) break;

        for (size_t i = 0; i < size; i++){
            if (visited[i]) continue;
            if (graph[start][i] == 0) continue;
            int newVal = values[start] + graph[start][i];
            if (newVal < values[i]) values[i] = newVal;
        }
        visited[start] = true;
    }

    return values[vertex2];
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

    std::vector<bool> visited(graph.Size(), false);
    visited[0] = true;
    size_t visited_count = 1;
    Graph::size_type spanning_tree_size = 0;

    std::vector<std::vector<int>> matrix(graph.Size(),
                                            std::vector<int>(graph.Size(), 0));

    auto find_min = [](const Graph& graph, const std::vector<bool>& visited){
        const int size = static_cast<int>(graph.Size());
        int min_edge_value = INT_MAX;
        edge_type min_edge = {-1, -1};

        for (int begin = 0; begin < size; begin++){
            if (!visited[begin]) continue;
            for (int end = 0; end < size; end++){
                if (visited[end]) continue;
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
        if (min_edge.first == -1) return Graph(matrix);
        matrix[min_edge.first][min_edge.second] =
            matrix[min_edge.second][min_edge.first] =
                graph.at(min_edge.first, min_edge.second);
        visited_count++;
        visited[min_edge.second] = true;
        spanning_tree_size += graph.at(min_edge.first, min_edge.second);
        if (visited_count == graph.Size()) {
            return Graph(matrix, spanning_tree_size);
        }
    }
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph){
    std::vector<std::vector<double>> pheromones(
        graph.Size(), std::vector<double>(graph.Size(), 0)
    );
    std::vector<Ant> ants(std::move(ants_utils_->AntsColony(graph)));
    TsmResult return_path;

    while (!ants.empty()){
        Ant* ant;
        for (size_t ant_index = 0; ant_index < ants.size(); ant_index++){
            ant = &ants[ant_index];
            ant->ChooseNextNode(
                graph[ant->CurrentNode()],
                pheromones[(ant->CurrentNode())]
            );
        }
        for (size_t ant_index = 0; ant_index < ants.size(); ant_index++){
            ant = &ants[ant_index];
            if (ant->BadWayCount() == 0){
                ants_utils_->RefreshPheromones(
                    ant->FromNode(), ant->CurrentNode(), graph, pheromones
                );
                if (ant->EndCodeStatus() == 1){
                    return_path = std::move(ants_utils_->UpdateReturnedWay(
                        ant->CurrentWay(), return_path
                    ));
                    ants.erase(ants.begin() + ant_index);
                }
            } else {
                if (ant->EndCodeStatus() == 2){
                    ants.erase(ants.begin() + ant_index);
                }
            }
        }
        ants_utils_->PheromoneEvaporation(pheromones);
    }
    // IF WAY EMPTY ADD ERROR TO TERMINAL
    return return_path;
}

TsmResult GraphAlgorithms::STSPBranchBoundMethodAlgorithm(Graph &graph){
    (void)graph;
    return TsmResult();
}

TsmResult GraphAlgorithms::ExhaustiveSearch(Graph &graph) const{
    if (graph.Size() == 0){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                        std::string("It is impossible to solve travelling ") +
                        std::string("salesman problem with current graph"));
    }
    
    std::vector<int> root_row;
    root_row.push_back(0);
    int min_row_weight = INT_MAX;
    std::vector<int> min_row;

    ExhaustiveSearch_(
        min_row_weight,
        min_row,
        root_row,
        graph
    );

    return { min_row, static_cast<double>(min_row_weight) };
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

void GraphAlgorithms::ExhaustiveSearch_(int& min_row_weight,
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
        // parent's copy to be appended
        std::vector<int> new_row(parent_row);
        new_row.push_back(y);
        const size_t size = new_row.size();
        // check if there is no loop
        if (size > graph.Size() * 10) continue;
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
}

}
