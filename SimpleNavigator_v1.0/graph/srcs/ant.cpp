#include "../includes/ant.hpp"

namespace s21{

Ant::Ant(int start_node) : start_node_(start_node), best_way_count_(0), 
        bad_way_count_(0), end_status_(0){
    current_way_.vertices.push_back(start_node_);
}

int Ant::ChooseNextNode(Ant::elem_of_graph_type& available_nodes,
            std::vector<double>& pheromones){
    int next_node;
    std::pair<std::vector<int>, std::vector<double>> node_and_probability =
        std::move(NodeSelectionProbability_(available_nodes, pheromones));

    next_node = (
        node_and_probability.first[
            std::distance(
                node_and_probability.second.begin(),
                std::max_element(
                    node_and_probability.second.begin(), 
                    node_and_probability.second.end()
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

int Ant::StartNode(){
    return start_node_;
}

int Ant::CurrentNode(){
    return current_way_.vertices.back();
}

int Ant::EndCodeStatus(){
    return end_status_;
}

std::pair<std::vector<int>, std::vector<double>>&& 
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
    std::pair<std::vector<int>, std::vector<double>> node_and_probability;

    for (size_t i = 0; i < available_nodes.size(); i++){
        int node = available_nodes[i];
        if ((node && is_permitted_node(node)) || 
            (node == start_node_ && 
                current_way.size() == (available_nodes.size() - 1))){
            node_and_probability.first.push_back(node);
            node_and_probability.second.push_back(
                node_probability(pheromones[i], ((double)1 / (double)node))
            );
        }
    }
    if (node_and_probability.first.empty()){
        node_and_probability.first.push_back(-1);
        node_and_probability.second.push_back(-1);
    } else {
        double probability_sum = std::reduce(
            node_and_probability.second.begin(), 
            node_and_probability.second.end()
        );

        for (int i = 0; i < node_and_probability.first.size(); i++){
            node_and_probability.second[i] = (
                node_and_probability.second[i] / probability_sum
            );
        }
    }
    return std::move(node_and_probability);
}

void Ant::UpdateBestWay_(){
    if (best_way_.vertices.empty() || 
        current_way_.distance < best_way_.distance){
        best_way_ = current_way_;
        best_way_count_ = 1;
    } else {
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
