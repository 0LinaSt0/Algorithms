#ifndef ANT_ALGORITHM_UTILS
#define ANT_ALGORITHM_UTILS

#include <utility>
#include <vector>

#include "../../graph/includes/graph.hpp"
#include "../../graph/includes/ant.hpp"
#include "utils.hpp"


namespace s21{

class AntAlgorithmUtils{
public:
    double AverageDistance(const Graph& graph);

    std::vector<Ant>&& AntsColony(const Graph& graph);

    TsmResult&& UpdateReturnedWay(TsmResult& new_way,
                    TsmResult& best_way);

    void RefreshPheromones(int from_node, int to_node, const Graph &graph,
            std::vector<std::vector<double>>& pheromones);

    void PheromoneEvaporation(std::vector<std::vector<double>>& pheromones);
};

}

#endif
