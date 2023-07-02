#ifndef ANT_ALGORITHM_UTILS
#define ANT_ALGORITHM_UTILS

#include <utility>
#include <vector>

#include "../../graph/includes/s21_graph.h"
#include "ant.hpp"
#include "utils.hpp"

namespace s21{

class Ant;

class AntAlgorithmUtils{
public:
    /**
     * Counting average distance between [graph] nodes as:
     * total length / edges numbers
     * @return double value of average distance between all nodes;
     */
    double AverageDistance(const Graph& graph);

    /**
     * Generating ants colony [graph].Size() ants numbers
     * @return std::unique_ptr<std::vector<Ant>> of ants colony
     */
    std::unique_ptr<std::vector<Ant>> AntsColony(const Graph& graph);

    /**
     * Updating the [best_way] current way if [new_way] is better
     * @return TsmResult with new best way
     */
    TsmResult UpdateBestWay(TsmResult& new_way,
                    TsmResult& best_way);

    /**
     * Refreshing pheromones on [from_node] [to_node] way in [pheromones] matrix
     */
    void RefreshPheromones(int from_node, int to_node, const Graph &graph,
            std::vector<std::vector<double>>& pheromones);

    /**
     * Evaporating pheromones in [pheromones] matrix
     */
    void PheromoneEvaporation(std::vector<std::vector<double>>& pheromones);
};

}

#endif
