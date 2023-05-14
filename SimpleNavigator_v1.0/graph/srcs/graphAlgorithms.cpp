#include "../includes/graphAlgorithms.hpp"

namespace s21{

auto GraphAlgorithms::DepthFirstSearch(Graph &graph, int start_vertex){
    const std::size_t graph_size = graph.Size();
    std::array<bool, graph_size> is_in_set;
    std::array<int, graph_size> nods_road;

    is_in_set.fill(false); nods_road.fill(-1);
    return nods_road;
}

}
