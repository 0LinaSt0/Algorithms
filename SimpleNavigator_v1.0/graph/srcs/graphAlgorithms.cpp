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

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph){
    Graph pheromones(
        std::vector<elem_of_graph_type>(
            graph.Size(), std::vector<int>(graph.Size(), 0)
        )
    );
    std::vector<Ant> ants(graph.Size());
    std::vector<int> current_ant_nodes(graph.Size());
    TsmResult return_path;
    // float q_parameter;

    // q_parameter = AverageDistance_(graph);
    std::iota(current_ant_nodes.begin(), current_ant_nodes.end(), 0);
    while (!ants.empty()){
        for (int /*choosed_node, */ant_index = 0; !ants.empty(); ant_index++){
            // choosed_node = ants[ant_index].ChooseNextNode(
            //     graph[current_ant_nodes[ant_index]],
            //     pheromones[current_ant_nodes[ant_index]]
            // );


            if (!ants.empty() && ant_index == static_cast<int>(ants.size() - 1)){
                ant_index = 0;
            }
        }
    }
    return return_path;
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

float GraphAlgorithms::AverageDistance_(Graph& graph){
    int edges_count;
    int total_length_count;

    edges_count = 0;
    total_length_count = 0;
    for (graph_iterator row = graph.Begin(); row != graph.End(); ++row){
        for (auto weight : *row){
            if (weight){
                edges_count++;
                total_length_count++;
            }
        }
    }
    return (float)total_length_count / (float)edges_count;
}

}
