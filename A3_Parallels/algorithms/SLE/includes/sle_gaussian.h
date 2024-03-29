#ifndef ACO
#define ACO

#include <algorithm>
#include <memory>
#include <thread>
#include <mutex>

#include "../../../utils/includes/utils.h"
#include "../../../matrix/includes/sle.h"

namespace s21{

struct Multiplier;

class SleGaussianParent{
public:
    using matrix_type               = Sle<double>;
    using matrix_type_reference     = matrix_type&;
    using matrix_type_unique_ptr    = std::unique_ptr<matrix_type>;
    using result_roots_type         = SleResult;
    using row_size_type             = typename matrix_type::row_size_type;
    using column_size_type          = typename matrix_type::column_size_type;
    using iterator_type             = typename matrix_type::iterator_type;
    using const_iterator_type       = typename matrix_type::const_iterator_type;
    using reverse_iterator_type
                            = typename matrix_type::reverse_iterator_type;
    using reverse_const_iterator_type
                            = typename matrix_type::reverse_const_iterator_type;

    SleGaussianParent(matrix_type_reference matrix);
    ~SleGaussianParent() = default;

    result_roots_type GaussianElimination();

    bool CheckCalculatedFactors(matrix_type matrix);

protected:
    matrix_type_unique_ptr matrix_;
    result_roots_type roots_;
    column_size_type equations_count_;
    column_size_type roots_count_;

    /**
     * Swapping [swapped_i] row with next row which doesn't have a value
     * zero on same [swapped_i] position
     * @return true if all next rows have zero value on [swapped_i] position
     * @return false otherwise
     */
    bool SwapRow_(row_size_type swapped_i);

    virtual void ReduceRows_(row_size_type current_i) = 0;

    void DetermineResult_();

    /**
     * Printing error message if system is inconsistent or has many solutions
     * @return true if system is inconsistent or has many solutions
     * @return false otherwise
     */
    bool DetermineSingular_();

    void DetermineRoots_();

    double DetermineRoot_(reverse_const_iterator_type& row_rev_it);

    bool IsOneEquationSingular_();

    bool DeleteZeroFactorInOneEquation_(matrix_type_reference matrix);
};

class SleGaussianUsual : public SleGaussianParent{
public:
    SleGaussianUsual(matrix_type_reference matrix);

private:
    void ReduceRows_(row_size_type current_i);
};

class SleGaussianParellel : public SleGaussianParent{
public:
    using mutex_type            = std::recursive_mutex;

    SleGaussianParellel(matrix_type_reference matrix);

private:
    mutex_type lock_;

    void ReduceRows_(row_size_type current_i);

    void ParallelReducing_(row_size_type row_i, row_size_type current_i);

    void ParallelReduceRow_(row_size_type row_i,
                        column_size_type column_i,
                        row_size_type current_i,
                        double multiplier);
};

}

#endif
