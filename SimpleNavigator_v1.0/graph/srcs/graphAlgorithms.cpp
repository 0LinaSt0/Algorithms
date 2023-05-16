#include "../includes/graphAlgorithms.hpp"

namespace s21{

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

GraphAlgorithms::graph_type
        GraphAlgorithms::GetShortestPathsBetweenAllVerticesTMP(Graph &graph){
    std::size_t graph_size = graph.Size();
    graph_type FWL_matrix(graph_size, elem_of_graph_type(graph_size, 0));

    for (std::size_t throgh_node = 0; throgh_node < graph_size; throgh_node++){
        for (std::size_t row = 0; row < graph_size; row++){
            for (std::size_t column = 0; column < graph_size; column++){
                FWL_matrix[row][column] = std::minmax(
                    std::initializer_list<int>{
                        graph[row][column],
                        (graph[row][throgh_node] + graph[throgh_node][column])
                    }
                ).first;
            }
        }
        std::cout << std::endl << "Graph with throgh_node = " << throgh_node << std::endl;
        for (std::size_t i = 0; i < graph_size; i++){
            for (std::size_t j = 0; j < graph_size; j++){
                std::cout << FWL_matrix[i][j] << "  ";
            }
            std::cout << std::endl;
        }
    }
    return FWL_matrix;
}

Graph GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph){
    std::size_t graph_size = graph.Size();
    Graph FWL_matrix(graph_type(graph_size, elem_of_graph_type(graph_size, 0)));

    for (std::size_t throgh_node = 0; throgh_node < graph_size; throgh_node++){
        for (std::size_t row = 0; row < graph_size; row++){
            for (std::size_t column = 0; column < graph_size; column++){
                FWL_matrix[row][column] = std::minmax(
                    std::initializer_list<int>{
                        graph[row][column],
                        (graph[row][throgh_node] + graph[throgh_node][column])
                    }
                ).first;
            }
        }
        std::cout << std::endl << "Graph with throgh_node = " << throgh_node << std::endl;
        FWL_matrix.tmp_print_graph_DELETEME();
    }
    return FWL_matrix;
}

}
