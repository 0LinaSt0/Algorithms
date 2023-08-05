#pragma once

#include "aco_abs.h"

namespace s21{

class AcoSingle : public AcoAbs {
public:
    template <typename T>
    AcoSingle(const Graph<T>& graph) : AcoAbs(graph) {

    }
    AcoSingle(const AcoSingle&) = delete;
    AcoSingle(AcoSingle&&) = delete;
    ~AcoSingle() = default;

    AcoSingle& operator=(const AcoSingle&) = delete;
    AcoSingle& operator=(AcoSingle&&) = delete;

protected:
    void AlgoBody_(std::vector<Ant>& ants);
    void UpdateAntsCount_();
    void SuccessfullSolutions_(Ant& ant);

};

}
