#ifndef ANT_ALGORITHM_UTILS
#define ANT_ALGORITHM_UTILS

#include <utility>
#include <vector>

#include "../../graph/includes/graph.hpp"
#include "../../graph/includes/graphAlgorithms.hpp"
#include "utils.hpp"


namespace s21{

class GraphAlgorithms;
class Graph;

class Ant{
public:
    using graph_type            = Graph;
    using elem_of_graph_type    = typename graph_type::elem_of_graph_type;

    Ant(int start_node);
    Ant(const Ant& other) = default;
    Ant(Ant&& other) = default;
    ~Ant() = default;

    Ant& operator=(const Ant& other) = default;
    Ant& operator=(Ant&& other) = default;

    int ChooseNextNode(elem_of_graph_type& available_nodes,
            std::vector<double>& pheromones);

    TsmResult& CurrentWay();

    int StartNode();

    int FromNode();

    int CurrentNode();

    int EndCodeStatus();

    int BestWayCount();

    int BadWayCount();
private:
    TsmResult current_way_;
    TsmResult best_way_;
    int start_node_;
    int best_way_count_;
    int bad_way_count_;
    int end_status_; // 0 -> continue; 1 -> best end; 2 -> bad end

    std::pair<std::vector<int>, std::vector<double>>&&
        NodeSelectionProbability_(elem_of_graph_type& available_nodes,
                                    std::vector<double>& pheromones);

    void UpdateBestWay_();

    void UpdateEndStatus_();

    void ResetCurrentWay_();
};


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
