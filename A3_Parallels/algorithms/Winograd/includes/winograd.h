#ifndef WINOGRAD
#define WINOGRAD

// #include <functional>
#include <vector>
#include <memory>
#include <thread>
#include <map>

#include "../../../utils/includes/utils.h"
#include "../../../matrix/includes/matrix.h"

namespace s21{

class WinogradParent{
public:
    using elements_type             = double;
    using matrix_type               = Matrix<elements_type>;
    using matrix_type_reference     = matrix_type&;
    using result_matrix_type        = MatrixResult<elements_type>;
    using result_matrix_rows_type   = typename result_matrix_type::rows_type;
    using row_matrix_type           = typename matrix_type::row_matrix_type;
    using row_matrix_type_reference = row_matrix_type&;
    using row_size_type             = typename matrix_type::row_size_type;
    using column_size_type          = typename matrix_type::column_size_type;
    using iterator_type             = typename matrix_type::iterator_type;
    using const_iterator_type       = typename matrix_type::const_iterator_type;
    using multiplicators_arrray     = std::map<row_size_type, elements_type>;
    using matrix_type_unique_ptr    = std::unique_ptr<matrix_type>;
    //IN CHILD USUAL
    using result_matrix_rows_unique_ptr 
                                    = std::unique_ptr<result_matrix_rows_type>;
    using multiply_func_signature   = std::function<elements_type(
                                            row_size_type,
                                            column_size_type)>;

    WinogradParent();
    ~WinogradParent() = default;

    result_matrix_type WinogradMultiplication(
                            matrix_type_reference matrix_first, 
                            matrix_type_reference matrix_second);

protected:
    result_matrix_type result_matrix_;
    multiplicators_arrray second_matrix_multiplicators_;

    bool IsMatricesInvalid_(column_size_type matrix_first_column_count, 
                        row_size_type matrix_second_row_count);

    void ResultMatrixReserveRowsStorage_(row_size_type row_count);

    virtual void MatrixMultiplication_(matrix_type_reference matrix_first, 
                            matrix_type_reference matrix_second) = 0;

    virtual void OfFirstFactorsDefine_(row_matrix_type& matrix_row) = 0;

    virtual void RowColumnMultiplication_(row_matrix_type_reference matrix_row,
                                    matrix_type_reference matrix_second) = 0;
};

class WinogradUsual : public WinogradParent{
public:
    WinogradUsual();

private:
   void MatrixMultiplication_(matrix_type_reference matrix_first, 
                            matrix_type_reference matrix_second);

    void RowsMultiplication_(matrix_type_reference matrix_first, 
                            matrix_type_reference matrix_second,
                            multiply_func_signature element_calculation);

    result_matrix_rows_unique_ptr RowCalculation_(
                                matrix_type_reference matrix_first, 
                                matrix_type_reference matrix_second,
                                row_size_type of_first_row_i,
                                multiply_func_signature element_calculation);
};

class WinogradParellel : public WinogradParent{
public:
    WinogradParellel();

private:


};

class WinograPipelineParellel : public WinogradParent{
public:
    WinograPipelineParellel();

private:


};

}

#endif