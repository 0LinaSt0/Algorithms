#include "../includes/aco_multi.h"
#include "../../../cli/includes/timer.h"

namespace s21{

void AcoMulti::AlgoBody_(std::vector<Ant>& ants){    
    std::vector<std::thread> threads;
    threads.reserve(ants.size());
    
    // All ant do steps 'till they are in the end
    for (Ant& ant : ants){
        threads.push_back(
            std::thread(
                [this, &ant](){
                    while (!ant.IsEnd()){
                        this->MakeStep_(ant);
                    }
                }
            )
        );
    }

    // Wait ants finish their work
    for (std::thread& thread : threads){
        thread.join();
    }
}

void AcoMulti::UpdateAntsCount_(){
    std::lock_guard<std::mutex> lock_guard(finished_ants_mutex_);
    finished_ants_++;
}

void AcoMulti::SuccessfullSolutions_(Ant& ant){
    ant.AddVertex(ant.GetPath().front());
    const std::vector<int>& path = ant.GetPath();
    for (size_t i = 0; i + 1 < path.size(); i++){
        Edge& edge = graph_[path[i]][path[i + 1]];
        std::lock_guard<std::mutex> lock_guard(id_to_edge_solution_mutex_);
        id_to_solutions[edge.id].push_back(&ant.GetPath());
    }
}

}
