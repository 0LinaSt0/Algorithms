#ifndef ACO_MULTI_H
#define ACO_MULTI_H

#include <mutex>
#include <thread>

#include "aco_abs.h"

namespace s21{

class AcoMulti : public AcoAbs {
public:
    template <typename T>
    AcoMulti(const Graph<T>& graph) 
        : AcoAbs(graph) {
        
    }
    AcoMulti(const AcoMulti&) = delete;
    AcoMulti(AcoMulti&&) = delete;
    ~AcoMulti() = default;

    AcoMulti& operator=(const AcoMulti&) = delete;
    AcoMulti& operator=(AcoMulti&&) = delete;

protected:
    void AlgoBody_(std::vector<Ant>& ants);
    void UpdateAntsCount_();
    void SuccessfullSolutions_(Ant& ant);

private:
    std::mutex finished_ants_mutex_;
    std::mutex id_to_edge_solution_mutex_;

};

}

#endif
