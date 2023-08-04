#ifndef ACO
#define ACO

#include <map>
#include <cmath>
#include <string>
#include <random>
#include <numeric>

#include "ant.h"
#include "../../../matrix/includes/s21_graph.h"

namespace s21{

class Aco{
public:
    template <typename T>
    Aco(const Graph<T>& graph)
    : graph_(Graph<Edge>::ConvertFromGraph(graph)) {

}

    Aco(const std::string& filename);
    Aco(const Aco& other) = delete;
    Aco(Aco&& other) = delete;
    ~Aco() = default;

    Aco& operator=(const Aco& other) = delete;
    Aco& operator=(Aco&& other) = delete;

    ::s21::TsmResult run(int iters_count = 5, int ants_count = 10);

    const Graph<Edge>& GetGraph() const;

private:
    const double ALPHA = 1.0;
    const double BETA = 1.0;
    const double EVAPOR = 0.5;
    int finished_ants_ = 0;
    Graph<Edge> graph_;
    std::map<int, Edge const *> id_to_edge;
    std::map<int, std::vector<std::vector<int> const *>> id_to_solutions;
    ::s21::TsmResult best_solution {
        {},
        std::numeric_limits<double>::max()
    };

    // Convert input graph to ::s21::Edge Graph
    // template<typename T>
    // Graph<Edge> templateToEdge_(const Graph<T>& graph);

    // Update pheromone values in graph
    void UpdatePheromones_();
    // Ant makes step
    void MakeStep_(Ant& ant);
    // Get list of nodes which ant can go to
    std::vector<int> GetAllAvailableNodes_(const Ant& ant) const;
    // Calculate (Tij^alpha)*(Nij^BETA) for specified edge
    double GetEdgeAttractiveness_(const Edge& edge) const;

};

}

#endif