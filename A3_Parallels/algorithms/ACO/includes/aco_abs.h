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

class AcoAbs{
public:
    template <typename T>
    AcoAbs(const Graph<T>& graph)
        : graph_(Graph<Edge>::ConvertFromGraph(graph)) {

    }
    AcoAbs(const AcoAbs& other) = delete;
    AcoAbs(AcoAbs&& other) = delete;
    virtual ~AcoAbs() = default;

    AcoAbs& operator=(const AcoAbs& other) = delete;
    AcoAbs& operator=(AcoAbs&& other) = delete;

    ::s21::TsmResult run(
        int iters_count = 10,
        int ants_count = 10
    );

protected:
    class AcoException : public ::s21::Exception{
    public:
        AcoException() = delete;
        AcoException(const std::string& msg);
        AcoException(AcoException&&) = delete;
        ~AcoException() = default;

        AcoException& operator=(const AcoException&) = delete;
        AcoException& operator=(AcoException&&) = delete;

        std::string GetMessage() const;
    };

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

    // Main algorithm logic
    virtual void AlgoBody_(std::vector<Ant>& ants) = 0;
    // Update finished ants count
    virtual void UpdateAntsCount_() = 0;
    // Update pointers to solutions
    virtual void SuccessfullSolutions_(Ant& ant) = 0;

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