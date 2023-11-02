#ifndef WINOGRAD
#define WINOGRAD

#include <condition_variable>
#include <functional>
#include <unistd.h>
#include <utility>
#include <vector>
#include <memory>
#include <limits>
#include <thread>
#include <queue>
#include <cmath>
#include <mutex>
#include <map>

#include "../../../utils/includes/utils.h"
#include "../../../matrix/includes/matrix.h"

namespace s21{

enum class WhitchMultiplicatorsCalculate {
    FIRST = 0,
    FIRST_SECOND = 1,
    SECOND = 2,
    NO_ONE = 3
};

enum class WhichMultiplicationCalculationSolution{
    FOR_FIRST_ELEM = 0,
    FOR_NEXT_ELEMS = 1
};

class WinogradParent{
public:
    using elements_type             = double;
    using matrix_type               = Matrix<elements_type>;
    using matrix_type_const_ref     = const matrix_type&;
    using result_matrix_type        = MatrixResult<elements_type>;
    using result_matrix_rows_type   = typename result_matrix_type::rows_type;
    using row_size_type             = typename matrix_type::row_size_type;
    using column_size_type          = typename matrix_type::column_size_type;
    using multiplicators_arrray     = std::map<row_size_type, elements_type>;
    using multiplicators_arrray_reference
                                    = multiplicators_arrray&;
    using matrices_pair             = std::pair<
                                        matrix_type_const_ref,
                                        matrix_type_const_ref>;
    using matrices_pair_ptr         = matrices_pair*;
    using matrix_rows_unique_ptr    = std::unique_ptr<result_matrix_rows_type>;
    using multiplications_calculate_pair
                                    = std::pair<
                                        WhitchMultiplicatorsCalculate,
                                        WhitchMultiplicatorsCalculate>;
    using extra_multiplier_func     = std::function<elements_type(
                                            row_size_type,
                                            column_size_type)>;
    using multiplicators_func       = std::function<elements_type(
                                        elements_type,
                                        multiplicators_arrray_reference,
                                        row_size_type,
                                        column_size_type,
                                        column_size_type)>;

    WinogradParent();
    ~WinogradParent() = default;

    /**
     * Multiplying [matrix_first] and [matrix_second] by Winograd method
     * @return result_matrix_type object
     */
    result_matrix_type WinogradMultiplication(
                            matrix_type_const_ref matrix_first,
                            matrix_type_const_ref matrix_second);

protected:
    result_matrix_type result_matrix_;
    multiplicators_arrray second_matrix_multiplicators_;

    /**
     * Check if matrices' sizes [matrix_first_column_count] and 
     * [matrix_second_row_count] are ok for multiplication
     * @return true if size if valid
     * @return false otherwise
     */
    bool IsMatricesInvalid_(column_size_type matrix_first_column_count,
                        row_size_type matrix_second_row_count);

    void StartMultiplication_(matrices_pair_ptr matrices_ptr);

    /**
     * Creating lambda function which returns extra multiplicator for
     * [matrices_ptr] first matrix, if odd size of elements in row, or zero
     * @return extra_multiplier_func object
     */
    extra_multiplier_func MatrixMultiplication_(matrices_pair_ptr matrices_ptr);

    virtual void RowsMultiplication_(matrices_pair_ptr matrices_ptr,
                            extra_multiplier_func element_calculation) = 0;

    /**
     * Defining pattern for calculating multiplicators depending 
     * of the calculating element of matrices in [matrices_ptr]
     * @return multiplicators_func object
     */
    multiplicators_func DefineMultiplicatorsFunc_(
                                    WhitchMultiplicatorsCalculate code,
                                    matrices_pair_ptr matrices_ptr);

    /**
     * Defining ways for calculating multiplicators depending 
     * of the calculating element of matrices in [matrices_ptr]
     * @return multiplications_calculate_pair object
     */
    multiplications_calculate_pair DefineMultiplicationCalculationSolution_(
                                WhichMultiplicationCalculationSolution code);

    matrix_rows_unique_ptr CalculateRow_(
                        matrices_pair_ptr matrices_ptr,
                        row_size_type of_first_row_i,
                        extra_multiplier_func extra_muliplier,
                        WhichMultiplicationCalculationSolution type_row_code);

    elements_type CalculateElement_(matrices_pair_ptr matrices_ptr,
                    row_size_type of_first_row_i,
                    column_size_type of_second_colum_i,
                    extra_multiplier_func extra_muliplier,
                    multiplicators_func multiplicators_calculation, 
                    elements_type& first_matrix_multiplicator);
};

class WinogradUsual : public WinogradParent{
public:
    WinogradUsual();

private:
    void RowsMultiplication_(matrices_pair_ptr matrices_ptr,
                        extra_multiplier_func element_calculation);
};

class WinogradParallel : public WinogradParent{
public:
    using mutex_type    = std::recursive_mutex;

    WinogradParallel(size_t threads_count);

private:
    size_t threads_count_;
    mutex_type lock_;

    void ResultMatrixDefaultInitialization_(row_size_type of_first_rows_count);

    void RowsMultiplication_(matrices_pair_ptr matrices_ptr,
                        extra_multiplier_func element_calculation);

    void RowsParallelism_(matrices_pair_ptr matrices_ptr,
                    extra_multiplier_func extra_muliplier);
};

class WinograPipelineParallel : public WinogradParent{
public:
    WinograPipelineParallel();

private:
    struct Stage{
        Stage() = default;
        Stage(const Stage&) = delete;
        Stage(Stage&& st) = default;
        ~Stage() = default;

        Stage& operator=(const Stage&) = delete;
        Stage& operator=(Stage&&) = default;

        std::queue<row_size_type> rows;
        std::thread thread;
        int id;
    };

    const row_size_type MAX_STAGES = 4;
    // Count of finished rows in result matrix
    row_size_type rows_done_;
    // Value to make threads wait for signal
    std::condition_variable cv_;
    // Stages
    std::vector<Stage> stages_;
    // Stages mutex
    std::vector<std::mutex> stages_mutexes_;
    // Start stages' threads muteces
    std::vector<std::mutex> start_mutexes_;
    // Multiplicators for columns
    std::vector<double> multiplicators_b_;
    // Mutex for columns' multiplicators
    std::mutex multiplicators_b_mutex_;

    void RowsMultiplication_(
        matrices_pair_ptr matrices_ptr,
        extra_multiplier_func extra_muliplier
    );

    // Fill result mtrx with default values
    void InitResultMtrx_(matrices_pair_ptr matrices_ptr);
    // Fill field multiplicators_b_ with NANs
    void InitMultiplicators_(matrices_pair_ptr matrices_ptr);
    // Return lambda function to run in thread
    std::function<void ()> GetThreadBody_(
        Stage& stage,
        row_size_type max_stage,
        matrices_pair_ptr matrices_ptr
    );
};

}

#endif
