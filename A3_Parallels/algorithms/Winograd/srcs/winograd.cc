#include "../includes/winograd.h"

namespace s21{

WinogradParent::result_matrix_type WinogradParent::WinogradMultiplication(
                                        matrix_type_reference matrix_first, 
                                        matrix_type_reference matrix_second){
    if(!IsMatricesInvalid_(
        matrix_first.ColumnsSize(), matrix_second.RowsSize()
    )){
        ResultMatrixReserveRowsStorage_(matrix_first.RowsSize());
        MatrixMultiplication_(matrix_first, matrix_second);
    }
    
    return result_matrix_;
}

bool WinogradParent::IsMatricesInvalid_(
                                    column_size_type matrix_first_column_count, 
                                    row_size_type matrix_second_row_count){
    bool is_invalid;

    is_invalid = false;
    if (matrix_first_column_count != matrix_second_row_count){
        PRINT_ERROR(
            __FILE__, __FUNCTION__, __LINE__,  
            "Invalid matrix: Rows count of first matrix doesn't "
            "equal to columns count of second one"
        );
        is_invalid = true;
    }
    return is_invalid;
}

void WinogradParent::ResultMatrixReserveRowsStorage_(row_size_type row_count){
    result_matrix_.matrix_array.reserve(row_count);
}


WinogradUsual::result_matrix_type WinogradUsual::MatrixMultiplication_(
                            matrix_type_reference matrix_first, 
                            matrix_type_reference matrix_second){
    for(row_size_type of_first_row_i = matrix_first.RowsSize();
        of_first_row_i < matrix_first.ColumnsSize();
        of_first_row_i++
    ){
        RowFactorsDefine_(matrix_first[of_first_row_i]);
        RowColumnMultiplication_(matrix_first[of_first_row_i], matrix_second);
    }
}

void WinogradUsual::RowFactorsDefine_(row_matrix_type_reference matrix_row){
    // for(column_size_type ){

    // }
}

void WinogradUsual::RowColumnMultiplication_(
                            row_matrix_type_reference matrix_row,
                            matrix_type_reference matrix_second){
    
}

}