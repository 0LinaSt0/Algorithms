#ifndef ANT_HPP
#define ANT_HPP

#include <algorithm>
#include <functional>

#include "graphAlgorithms.hpp"
#include "graph.hpp"

namespace s21{

// struct TsmResult;
class Ant;

class Ant{
public:
    using graph_type            = Graph;
    using elem_of_graph_type    = typename graph_type::elem_of_graph_type;

    Ant();
    Ant(const Ant& other) = default;
    Ant(Ant&& other) = default;
    ~Ant() = default;

    Ant& operator=(const Ant& other) = default;
    Ant& operator=(Ant&& other) = default;

    int ChooseNextNode(elem_of_graph_type& available_nodes,
            elem_of_graph_type& pheromones);

    int CurrentWayLength();

    int EndCodeStatus();
private:
    TsmResult current_way_;
    TsmResult best_way_;
    int ant_start_node_;
    int best_way_count_;
    int bad_way_count_;
    int end_status_; // 0 -> continue; 1 -> best end; 2 -> bad end
};

}

#endif
