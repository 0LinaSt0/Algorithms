#ifndef ANT
#define ANT

#include <memory>
#include <cmath>

#include "../../graph/includes/s21_graph_algorithms.h"

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

    /**
     * Choosing next node for Ant from [available_nodes]
     * including magnitude of [pheromones] exposure
     * @return int value of choosed node number
     */
    int ChooseNextNode(elem_of_graph_type& available_nodes,
            std::vector<double>& pheromones);

    /**
     * @return reference to TsmResult Ant's current way
     */
    TsmResult& CurrentWay();

    /**
     * @return reference to TsmResult Ant's best way
     */
    TsmResult& BestWay();

    /**
     * @return int value of Ant's start node number
     */
    int StartNode();

    /**
     * @return int value of Ant's start node number of last subpath
     * @attention if current way is empty undefined behavior
     */
    int FromNode();

    /**
     * @return int value of Ant's last visited node
     * @attention if current way is empty undefined behavior
     */
    int CurrentNode();

    /**
     * @return 0 if continue Ant's way
     * @return 1 if the Ant has passed a successful full path - best end
     * @return 2 if the Ant couldn't passed full path - bad end
     */
    int EndCodeStatus();

    /**
     * @return int value of Ant's best way counter
     */
    int BestWayCount();

    /**
     * @return int value of Ant's bad way counter
     */
    int BadWayCount();
private:
    TsmResult current_way_;
    TsmResult best_way_;
    int start_node_;
    int best_way_count_;
    int bad_way_count_;
    int iterations_count_;
    int end_status_;

    /**
     * Updating selection probability of [available_nodes] for Ant
     * including magnitude of [pheromones] exposure
     * @return probability_pair_matrix_unique_ptr includes available
     * nodes with probability to be chosen
     */
    probability_pair_matrix_unique_ptr NodeSelectionProbability_(
                                    elem_of_graph_type& available_nodes,
                                    std::vector<double>& pheromones);

    void UpdateBestWay_();

    void UpdateEndStatus_();

    void ResetCurrentWay_();
};

}

#endif
