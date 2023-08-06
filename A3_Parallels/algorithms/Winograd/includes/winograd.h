#ifndef WINOGRAD
#define WINOGRAD

#include <functional>
#include <utility>
#include <vector>
#include <memory>
#include <thread>
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
    using matrix_type_reference     = matrix_type&;
    using result_matrix_type        = MatrixResult<elements_type>;
    using result_matrix_rows_type   = typename result_matrix_type::rows_type;
    using row_size_type             = typename matrix_type::row_size_type;
    using column_size_type          = typename matrix_type::column_size_type;
    // using iterator_type             = typename matrix_type::iterator_type;
    // using const_iterator_type       = typename matrix_type::const_iterator_type;
    using multiplicators_arrray     = std::map<row_size_type, elements_type>;
    using multiplicators_arrray_reference
                                    = multiplicators_arrray&;
    using matrices_pair             = std::pair<
                                        matrix_type_reference, 
                                        matrix_type_reference>;
    using matrices_pair_ptr         = matrices_pair*;

    //IN CHILD USUAL
    using matrix_rows_unique_ptr    = std::unique_ptr<result_matrix_rows_type>;
    using multiplications_calculate_pair
                                    = std::pair<
                                        WhitchMultiplicatorsCalculate, 
                                        WhitchMultiplicatorsCalculate>;
    using extra_multiplier_func     = std::function<elements_type(
                                            row_size_type,
                                            column_size_type)>;
    using multiplicators_func       = std::function<void(
                                        elements_type&,
                                        multiplicators_arrray_reference,
                                        row_size_type,
                                        column_size_type,
                                        column_size_type)>;
    // IN CHILE PARALLEL
    using mutex_type                 = std::recursive_mutex;

    WinogradParent();
    ~WinogradParent() = default;

    result_matrix_type WinogradMultiplication(
                            matrix_type_reference matrix_first, 
                            matrix_type_reference matrix_second);

protected:
    result_matrix_type result_matrix_;
    elements_type first_matrix_multiplicator_;
    multiplicators_arrray second_matrix_multiplicators_;

    bool IsMatricesInvalid_(column_size_type matrix_first_column_count, 
                        row_size_type matrix_second_row_count);

    void ResultMatrixReserveRowsStorage_(row_size_type row_count);

    void MatrixMultiplication_(matrices_pair_ptr matrices_ptr);
    
    virtual void RowsMultiplication_(matrices_pair_ptr matrices_ptr,
                            extra_multiplier_func element_calculation) = 0;

    multiplicators_func DefineMultiplicatorsFunc_(
                                    WhitchMultiplicatorsCalculate code,
                                    matrices_pair_ptr matrices_ptr);

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
                    multiplicators_func multiplicators_calculation);
};

class WinogradUsual : public WinogradParent{
public:
    WinogradUsual();

private:
    void RowsMultiplication_(matrices_pair_ptr matrices_ptr,
                        extra_multiplier_func element_calculation);

    // matrix_rows_unique_ptr CalculateRow_(
    //                     matrices_pair_reference matrices_ptr,
    //                     row_size_type of_first_row_i,
    //                     extra_multiplier_func extra_muliplier,
    //                     WhichMultiplicationCalculationSolution type_row_code);

    // elements_type CalculateElement_(matrices_pair_reference matrices_ptr,
    //                 row_size_type of_first_row_i,
    //                 column_size_type of_second_colum_i,
    //                 extra_multiplier_func extra_muliplier,
    //                 multiplicators_func multiplicators_calculation);
};

class WinogradParallel : public WinogradParent{
public:
    WinogradParallel();

private:
    mutex_type lock_;

    void RowsMultiplication_(matrices_pair_ptr matrices_ptr,
                        extra_multiplier_func element_calculation);

    void RowsParallelism_(matrices_pair_ptr matrices_ptr,
                    row_size_type of_first_row_i,
                    extra_multiplier_func extra_muliplier);
};

class WinograPipelineParallel : public WinogradParent{
public:
    WinograPipelineParallel();

private:


};

}

#endif