#ifndef WINOGRAD
#define WINOGRAD

#include <vector>
#include <memory>
#include <thread>

#include "../../../utils/includes/utils.h"
#include "../../../matrix/includes/matrix.h"

namespace s21{

class WinogradParent{
public:
    using elements_type             = double;
    using matrix_type               = Matrix<elements_type>;
    using matrix_type_reference     = matrix_type&;
    using matrix_type_unique_ptr    = std::unique_ptr<matrix_type>;
    using factors_arrray_type       = std::vector<elements_type>;
    using result_matrix_type        = MatrixResult<elements_type>;
    using row_matrix_type           = typename matrix_type::row_matrix_type;
    using row_matrix_type_reference = row_matrix_type&;
    using row_size_type             = typename matrix_type::row_size_type;
    using column_size_type          = typename matrix_type::column_size_type;
    using iterator_type             = typename matrix_type::iterator_type;
    using const_iterator_type       = typename matrix_type::const_iterator_type;

    WinogradParent() = default;
    ~WinogradParent() = default;

    result_matrix_type WinogradMultiplication(
                            matrix_type_reference matrix_first, 
                            matrix_type_reference matrix_second);

protected:
    result_matrix_type result_matrix_;
    factors_arrray_type first_matrix_common_factor_;
    std::vector<factors_arrray_type> second_matrix_common_factors_;

    bool IsMatricesInvalid_(column_size_type matrix_first_column_count, 
                        row_size_type matrix_second_row_count);

    void ResultMatrixReserveRowsStorage_(row_size_type row_count);

    virtual result_matrix_type MatrixMultiplication_(
                            matrix_type_reference matrix_first, 
                            matrix_type_reference matrix_second) = 0;

    virtual void RowFactorsDefine_(row_matrix_type& matrix_row) = 0;

    virtual void RowColumnMultiplication_(row_matrix_type_reference matrix_row,
                                    matrix_type_reference matrix_second) = 0;
};

class WinogradUsual : public WinogradParent{
public:
    WinogradUsual();

private:
   result_matrix_type MatrixMultiplication_(
                            matrix_type_reference matrix_first, 
                            matrix_type_reference matrix_second);

    void RowFactorsDefine_(row_matrix_type_reference matrix_row);

    void RowColumnMultiplication_(row_matrix_type_reference matrix_row,
                            matrix_type_reference matrix_second);
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