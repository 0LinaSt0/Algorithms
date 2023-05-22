#ifndef ANT_HPP
#define ANT_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>
#include <numeric>
#include <cmath>

#include "../../utils/includes/utils.hpp"
#include "graphAlgorithms.hpp"
#include "graph.hpp"

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

}

#endif
