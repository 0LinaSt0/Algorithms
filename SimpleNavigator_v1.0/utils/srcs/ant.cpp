#include "../includes/ant.hpp"

namespace s21{

Ant::Ant(int start_node) : start_node_(start_node), best_way_count_(0),
        bad_way_count_(0), end_status_(0){
    current_way_.vertices.push_back(start_node_);
}

int Ant::ChooseNextNode(Ant::elem_of_graph_type& available_nodes,
            std::vector<double>& pheromones){
    int next_node;
    probability_pair_matrix_unique_ptr node_and_probability =
        (NodeSelectionProbability_(available_nodes, pheromones));

    next_node = (
        node_and_probability->first[
            std::distance(
                node_and_probability->second.begin(),
                std::max_element(
                    node_and_probability->second.begin(),
                    node_and_probability->second.end()
                )
            )
        ]
    );
    if (next_node == -1){
        best_way_count_ = 0;
        ResetCurrentWay_();
        bad_way_count_++;
        next_node = start_node_;
    } else {
        bad_way_count_ = 0;
        current_way_.vertices.push_back(next_node);
        current_way_.distance += available_nodes[next_node];
        if (next_node == start_node_){
            UpdateBestWay_();
            ResetCurrentWay_();
        }
    }
    UpdateEndStatus_();
    return next_node;
}

TsmResult& Ant::CurrentWay(){
    return current_way_;
}

TsmResult& Ant::BestWay(){
    return best_way_;
}

int Ant::StartNode(){
    return start_node_;
}

int Ant::FromNode(){
    return current_way_.vertices.end()[-2];
}

int Ant::CurrentNode(){
    return current_way_.vertices.back();
}

int Ant::EndCodeStatus(){
    return end_status_;
}

int Ant::BestWayCount(){
    return best_way_count_;
}

int Ant::BadWayCount(){
    return bad_way_count_;
}

Ant::probability_pair_matrix_unique_ptr
    Ant::NodeSelectionProbability_(Ant::elem_of_graph_type& available_nodes,
                                    std::vector<double>& pheromones){
    std::vector<int>& current_way = current_way_.vertices;
    auto is_permitted_node = [&current_way](int node) -> bool{
        auto nodeIt = std::find(current_way.begin(), current_way.end(), node);
        return nodeIt == current_way.end();
    };
    auto node_probability = [](double pheromone, double visible) -> double{
        return (std::pow(pheromone, TSM_ALPHA) * std::pow(visible, TSM_BETA));
    };
    probability_pair_matrix_unique_ptr node_and_probability(
        new probability_pair_matrix()
    );

    /////// TEST
    // {
    //     std::cout << "\t available_nodes: ";
    //     for (auto& elem : available_nodes){
    //         std::cout << elem << "  ";
    //     }
    //     std::cout << std::endl;
    // } //////////
    
    for (int i = 0; i < (int)available_nodes.size(); i++){
        int node_value = available_nodes[i];
        if ((node_value && is_permitted_node(i)) ||
            (i == start_node_ &&
                current_way.size() == (available_nodes.size()))){
            // std::cout << current_way.size() << " --- " << node_value << "       ";
            node_and_probability->first.push_back(i);
            node_and_probability->second.push_back(
                node_probability(pheromones[i], ((double)1 / (double)node_value))
            );
        }
    }
    if (node_and_probability->first.empty()){
        node_and_probability->first.push_back(-1);
        node_and_probability->second.push_back(-1);
    } else {
        double probability_sum = std::reduce(
            node_and_probability->second.begin(),
            node_and_probability->second.end()
        );

        for (size_t i = 0; i < node_and_probability->first.size(); i++){
            node_and_probability->second[i] = (
                node_and_probability->second[i] / probability_sum
            );
        }
    }
    return (node_and_probability);
}

void Ant::UpdateBestWay_(){
    if (best_way_.vertices.empty() ||
        current_way_.distance < best_way_.distance){
        best_way_ = current_way_;
        best_way_count_ = 1;
    } else if (current_way_.distance == best_way_.distance && 
                current_way_.vertices == best_way_.vertices) {
        best_way_count_++;
    }
}

void Ant::UpdateEndStatus_(){
    if (best_way_count_ >= TSM_SAME_ROAD_LIMIT){
        end_status_ = 1;
    } else if (bad_way_count_ >= TSM_SAME_ROAD_LIMIT){
        end_status_ = 2;
    }
}

void Ant::ResetCurrentWay_(){
    current_way_.vertices.clear();
    current_way_.vertices.push_back(start_node_);
    current_way_.distance = 0;
}

}