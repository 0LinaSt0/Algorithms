#ifndef ACO
#define ACO

#include <memory>

#include "../../utils/includes/utils.h"
#include "../../graph/includes/s21_graph.h"

namespace s21{

class SleGaussianParent{
public:
    using result_roots_type         = SleResult;
    using matrix_type               = Graph;
    using matrix_type_reference     = matrix_type&;
    using matrix_size_type          = typename matrix_type::size_type;
    using iterator_type             = typename matrix_type::iterator_type;
    using const_iterator_type       = typename matrix_type::const_iterator_type;
    using matrix_type_unique_ptr    = std::unique_ptr<matrix_type>;

    SleGaussianParent(matrix_type_reference graph);
    ~SleGaussianParent();

    result_roots_type GaussianElimination();

private:
    matrix_type_unique_ptr matrix_;
    result_roots_type roots;
    bool isSingular_; // inconsistent system or has many solutions

    virtual void ReduceRows_() = 0;

    void SwapRow_(matrix_size_type swap_row_i);

    void DetermineResult_();

    void DetermineRoots_(); 

};

class SleGaussianUsual : public SleGaussianParent{
public:

private:
    void ReduceRows_();
};

class SleGaussianParellel : public SleGaussianParent{
public:

private:
    void ReduceRows_();
};

}

#endif