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

}
