#ifndef ANT
#define ANT

#include <memory>

#include "../../graph/includes/graphAlgorithms.hpp"

namespace s21{

class GraphAlgorithms;
class Graph;

class Ant{
public:
    using graph_type                            = Graph;
    using elem_of_graph_type                    = typename graph_type::
                                                            elem_of_graph_type;
    using probability_pair_matrix               = std::pair<std::vector<int>, 
                                                        std::vector<double>>;
    using probability_pair_matrix_unique_ptr    = std::unique_ptr<
                                                    probability_pair_matrix>;

    Ant(int start_node);
    Ant(const Ant& other) = default;
    Ant(Ant&& other) = default;
    ~Ant() = default;

    Ant& operator=(const Ant& other) = default;
    Ant& operator=(Ant&& other) = default;

    int ChooseNextNode(elem_of_graph_type& available_nodes,
            std::vector<double>& pheromones);

    TsmResult& CurrentWay();

    TsmResult& BestWay();

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

    probability_pair_matrix_unique_ptr NodeSelectionProbability_(
                                    elem_of_graph_type& available_nodes,
                                    std::vector<double>& pheromones);

    void UpdateBestWay_();

    void UpdateEndStatus_();

    void ResetCurrentWay_();
};

}

#endif