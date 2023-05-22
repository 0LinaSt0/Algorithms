#include "../includes/antAlgorithmUtils.hpp"

namespace s21{

double AntAlgorithmUtils::AverageDistance(const Graph& graph){
    int edges_count;
    int total_length_count;

    edges_count = 0;
    total_length_count = 0;
    for (Graph::const_iterator_type row = graph.Begin();
            row != graph.End(); ++row){
        for (auto weight : *row){
            if (weight){
                edges_count++;
                total_length_count++;
            }
        }
    }
    return (float)total_length_count / (float)edges_count;
}

std::vector<Ant>&& AntAlgorithmUtils::AntsColony(const Graph& graph){
    std::vector<Ant> ants;

    for(size_t i = 0; i < graph.Size(); i++){
        ants.push_back(Ant(i));
    }
    return std::move(ants);
}

TsmResult&& AntAlgorithmUtils::UpdateReturnedWay(TsmResult& new_way,
                                TsmResult& best_way){
    if (best_way.vertices.empty() ||
        new_way.distance < best_way.distance){
        return std::move(new_way);
    } else {
        return std::move(best_way);
    }
}

void AntAlgorithmUtils::RefreshPheromones(int from_node, int to_node,
        const Graph &graph, std::vector<std::vector<double>>& pheromones){
    double q_parameter;

    q_parameter = AverageDistance(graph);
    pheromones[from_node][to_node] +=
        q_parameter / (double)(graph[from_node][to_node]);
}

void AntAlgorithmUtils::PheromoneEvaporation(
        std::vector<std::vector<double>>& pheromones){
    for (auto& string_pheromones : pheromones){
        for (auto& node_pheromone : string_pheromones){
            node_pheromone = ((double)1 - TSM_PYRA) * node_pheromone;
        }
    }
}

}
