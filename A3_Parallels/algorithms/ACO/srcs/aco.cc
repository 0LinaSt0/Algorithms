#include "../includes/aco.h"

namespace s21{
    
Aco::Aco(const std::string& filename)
    : graph_(::s21::Graph<Edge>::LoadFromFile(filename)) {

}

::s21::TsmResult Aco::run(int iters_count, int ants_count){
    // Algorithm iterations
    for (int current_inter = 0; current_inter < iters_count; current_inter++){
    for (int start_vertex; 
        start_vertex < static_cast<int>(graph_.NodesSize()); 
        start_vertex++){
        
        // Refresh values
        finished_ants_ = 0;
        id_to_edge.clear();
        id_to_solutions.clear();
        // Array of ants for current algo iter
        Ant init_ant;
        init_ant.AddVertex(start_vertex);
        std::vector<Ant> ants(ants_count, init_ant);
        
        // Algo body
        while (true){
            // Each ant makes a step
            for (Ant& ant : ants){
                MakeStep_(ant);
            }
            // Check if all ants are in the end
            if (finished_ants_ == static_cast<int>(ants.size())) break;
        }

        UpdatePheromones_();
    }
    }

    return best_solution;
}

// const Graph<Edge>& Aco::GetGraph() const{
//     return graph_;
// }

// Implementation of formula from the Internet
void Aco::UpdatePheromones_(){
    for (size_t from = 0; from < graph_.NodesSize(); from++){
    for (size_t to = 0; to < graph_.NodesSize(); to++){
        Edge& edge = graph_[from][to];
        int id = edge.id;
        double full_delta = 0;
        std::vector<std::vector<int> const *>& solutions = id_to_solutions[id];
        for (std::vector<int> const * sol_ptr : solutions){
            double tmp_len = 0;
            // Calculate path's length
            for (size_t i = 0; i + 1 < sol_ptr->size(); i++){
                Edge& tmp_edge = graph_[sol_ptr->at(i)][sol_ptr->at(i + 1)];
                tmp_len += tmp_edge.value;
            }
            // Update the best solution
            if (tmp_len < best_solution.distance){
                best_solution.distance = tmp_len;
                best_solution.vertices = *sol_ptr;
            }
            full_delta += 1.0 / tmp_len;
        }
        // Update pheromone
        edge.pheromone = (1.0 - EVAPOR) * edge.pheromone + full_delta;
    }
    }
}

void Aco::MakeStep_(Ant& ant){
    int current_node_num = ant.GetPath().back();
    std::vector<int> available_nodes = GetAllAvailableNodes_(ant);
    if (available_nodes.size() == 0) {
        // Update ants counter
        finished_ants_++;
        // Ant finished it's route
        ant.SetEnd(true);
        // Is route complete
        ant.SetSuccess(
            ant.GetPath().size() == graph_.NodesSize() &&
            graph_.At(ant.GetPath().back(), ant.GetPath().front()) != 0
        );
        // Save pointers to solution
        if (ant.IsSuccess()){
            ant.AddVertex(ant.GetPath().front());
            const std::vector<int>& path = ant.GetPath();
            for (size_t i = 0; i + 1 < path.size(); i++){
                Edge& edge = graph_[path[i]][path[i + 1]];
                id_to_edge[edge.id] = &edge;
                id_to_solutions[edge.id].push_back(&ant.GetPath());
            }
        }
    } else {
        // Random numbers generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 100);

        // Attractivity sum by all available nodes
        double attr_sum = 0.0;
        for (int available_node : available_nodes){
            attr_sum += GetEdgeAttractiveness_(
                graph_.At(current_node_num, available_node)
            );
        }
        // Find the best node to go to
        std::pair<int, double> max_node_to_p {0, 0};
        for (int available_node : available_nodes){
            double p = GetEdgeAttractiveness_(
                graph_.At(current_node_num, available_node)
            ) / attr_sum;
            if (
                p > max_node_to_p.second ||
                (
                    ::s21::DoubleCompare(p, max_node_to_p.second) &&
                    distrib(gen) % 2 == 0
                )
            ){
                max_node_to_p.first = available_node;
                max_node_to_p.second = p;
            }
        }
        ant.AddVertex(max_node_to_p.first);
    }
}

std::vector<int> Aco::GetAllAvailableNodes_(const Ant& ant) const{
    // Position where ant is now
    int from = ant.GetPath().back();

    // Find next nodes to go to
    std::vector<int> available_nodes;
    for (int to = 0; to < static_cast<int>(graph_.NodesSize()); to++){
        if (ant.IsInPath(to)) continue;
        if (graph_.At(from, to) == 0) continue;
        available_nodes.push_back(to);
    }

    return available_nodes;
}

double Aco::GetEdgeAttractiveness_(const Edge& edge) const{
    return std::pow(edge.pheromone, ALPHA) *
            std::pow(1.0 / edge.value, BETA);
}

}
