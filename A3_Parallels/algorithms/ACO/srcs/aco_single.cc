#include "../includes/aco_single.h"
#include "../../../cli/includes/timer.h"

namespace s21{

void AcoSingle::AlgoBody_(std::vector<Ant>& ants){    
    // Algo body
    while (true){
        // Each ant makes a step
        for (Ant& ant : ants){
            MakeStep_(ant);
        }

        // Check if all ants are in the end
        if (finished_ants_ == static_cast<int>(ants.size())) break;
    }
}

void AcoSingle::UpdateAntsCount_(){
    finished_ants_++;
}

void AcoSingle::SuccessfullSolutions_(Ant& ant){
    ant.AddVertex(ant.GetPath().front());
    const std::vector<int>& path = ant.GetPath();
    for (size_t i = 0; i + 1 < path.size(); i++){
        Edge& edge = graph_[path[i]][path[i + 1]];
        id_to_solutions[edge.id].push_back(&ant.GetPath());
    }
}

}
