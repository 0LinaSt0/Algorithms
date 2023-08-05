#include "../includes/winograd.h"

namespace s21{

WinogradParent::WinogradParent() { }

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
    if (!matrix_first_column_count){
        PRINT_ERROR(
            __FILE__, __FUNCTION__, __LINE__, 
            "Invalid matrices: Matrices are empty"
        );
        is_invalid = true;
    }
    return is_invalid;
}

void WinogradParent::ResultMatrixReserveRowsStorage_(row_size_type row_count){
    result_matrix_.matrix_array.reserve(row_count);
}


WinogradUsual::WinogradUsual() : WinogradParent() { }

void WinogradUsual::MatrixMultiplication_(matrix_type_reference matrix_first, 
                            matrix_type_reference matrix_second){
    multiply_func_signature element_calculation;
    
    if (matrix_first.RowsSize() % 2){
        element_calculation = 
            [&matrix_first, matrix_second]
            (row_size_type of_first_row_i, column_size_type of_second_column_i)
            -> elements_type {
                elements_type returned_multiplicator;

                returned_multiplicator = 
                    matrix_first[of_first_row_i].back() * 
                    matrix_second.Back()[of_second_column_i];
                return returned_multiplicator;
            };
    } else {
        element_calculation = 
            [](row_size_type, column_size_type) -> elements_type { return 0; };
    }
    RowsMultiplication_(
        matrix_first, 
        matrix_second, 
        element_calculation
    );
}

void WinogradUsual::RowsMultiplication_(matrix_type_reference matrix_first, 
                                matrix_type_reference matrix_second,
                                multiply_func_signature element_calculation){
    result_matrix_rows_unique_ptr current_result_row;
    
    for(row_size_type of_first_row_i = 0;
        of_first_row_i < matrix_first.RowsSize();
        of_first_row_i++
    ){
        current_result_row = RowCalculation_(
            matrix_first, 
            matrix_second,
            of_first_row_i,
            element_calculation
        );
        result_matrix_.matrix_array.push_back(current_result_row);
    }
}

WinogradUsual::result_matrix_rows_unique_ptr
    WinogradUsual::RowCalculation_(matrix_type_reference matrix_first, 
                                matrix_type_reference matrix_second,
                                row_size_type of_first_row_i,
                                multiply_func_signature element_calculation){
    result_matrix_rows_unique_ptr result_row(new result_matrix_rows_type());
    elements_type current_first_matrix_multiplicator;

    current_first_matrix_multiplicator = 0;
    for(column_size_type of_second_column_i = 0;
        of_second_column_i < matrix_second.ColumnsSize();
        of_second_column_i++
    ){
        for(column_size_type of_first_column_i = 0;
            of_first_column_i < matrix_first.ColumnsSize() - 1;
            of_first_column_i += 2
        ){
            OfFirstFactorsDefine_(matrix_first[of_first_row_i]);
        }
    }
    return result_row;
}

}