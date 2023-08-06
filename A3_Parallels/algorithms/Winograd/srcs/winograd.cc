#include "../includes/winograd.h"

namespace s21{

WinogradParent::WinogradParent() : first_matrix_multiplicator_(0) { }

WinogradParent::result_matrix_type WinogradParent::WinogradMultiplication(
                                        matrix_type_reference matrix_first, 
                                        matrix_type_reference matrix_second){
    if(!IsMatricesInvalid_(
        matrix_first.ColumnsSize(), matrix_second.RowsSize()
    )){
        matrices_pair matrices{matrix_first, matrix_second};

        ResultMatrixReserveRowsStorage_(matrix_first.RowsSize());
        MatrixMultiplication_(matrices);
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

void WinogradUsual::MatrixMultiplication_(matrices_pair_reference matrices_ref){
    extra_multiplier_func extra_muliplier;
    
    if (matrices_ref.first.ColumnsSize() % 2){
        extra_muliplier = 
            [matrices_ref]
            (row_size_type of_first_row_i, column_size_type of_second_column_i)
            -> elements_type {
                elements_type returned_multiplicator;

                returned_multiplicator = 
                    matrices_ref.first[of_first_row_i].back() * 
                    matrices_ref.second.Back()[of_second_column_i];
                return returned_multiplicator;
            };
    } else {
        extra_muliplier = 
            [](row_size_type, column_size_type) -> elements_type { return 0; };
    }
    RowsMultiplication_(
        matrices_ref, 
        extra_muliplier
    );
}

void WinogradUsual::RowsMultiplication_(matrices_pair_reference matrices_ref,
                                    extra_multiplier_func extra_muliplier){
    
    matrix_rows_unique_ptr current_result_row;

    // For first row
    current_result_row = CalculateRow_(
        matrices_ref,
        0,
        extra_muliplier, 
        WhichMultiplicationCalculationSolution::FOR_FIRST_ELEM);
    result_matrix_.matrix_array.push_back(*current_result_row);
    
    // For next rows
    for(row_size_type of_first_row_i = 1;
        of_first_row_i < matrices_ref.first.RowsSize();
        of_first_row_i++
    ){
        current_result_row = CalculateRow_(
            matrices_ref,
            of_first_row_i,
            extra_muliplier,
            WhichMultiplicationCalculationSolution::FOR_NEXT_ELEMS);
        result_matrix_.matrix_array.push_back(*current_result_row);
    }
}

WinogradUsual::matrix_rows_unique_ptr 
    WinogradUsual::CalculateRow_(matrices_pair_reference matrices_ref,
                        row_size_type of_first_row_i,
                        extra_multiplier_func extra_muliplier,
                        WhichMultiplicationCalculationSolution type_row_code){
    matrix_rows_unique_ptr result_row(new result_matrix_rows_type());
    elements_type current_element_result;
    multiplications_calculate_pair execute_codes;
    multiplicators_func multiplicators_calculation;

    execute_codes = DefineMultiplicationCalculationSolution_(type_row_code);

    multiplicators_calculation = DefineMultiplicatorsFunc_(
        execute_codes.first,
        matrices_ref
    );

    // if (of_first_row_i == 1){
    //     for (multiplicators_arrray::iterator it = second_matrix_multiplicators_.begin();
    //             it != second_matrix_multiplicators_.end();
    //             ++it){
    //         std::cout << it->first << ": " << it->second << std::endl;
    //     }
    //     exit(0);
    // }


    //For first element
    current_element_result = CalculateElement_(
        matrices_ref,
        of_first_row_i, 
        0,
        extra_muliplier,
        multiplicators_calculation
    );
    result_row->push_back(current_element_result);
    multiplicators_calculation = DefineMultiplicatorsFunc_(
        execute_codes.second,
        matrices_ref
    );

    //For next elements
    for(column_size_type of_second_column_i = 1;
        of_second_column_i < matrices_ref.second.ColumnsSize();
        of_second_column_i++
    ){
        current_element_result = CalculateElement_(
            matrices_ref,
            of_first_row_i,
            of_second_column_i,
            extra_muliplier,
            multiplicators_calculation
        );
        result_row->push_back(current_element_result);
        
    }
    first_matrix_multiplicator_ = 0;
    return result_row;
}

WinogradUsual::elements_type 
    WinogradUsual::CalculateElement_(matrices_pair_reference matrices_ref,
                    row_size_type of_first_row_i,
                    column_size_type of_second_column_i,
                    extra_multiplier_func extra_muliplier,
                    multiplicators_func multiplicators_calculation){
    elements_type element_result;

    element_result = 0;
    for(column_size_type of_first_column_i = 0;
            of_first_column_i < matrices_ref.first.ColumnsSize() - 1;
            of_first_column_i += 2
    ){
            element_result += 
                (matrices_ref.first[of_first_row_i][of_first_column_i] + 
                matrices_ref.second[of_first_column_i + 1][of_second_column_i])*
                (matrices_ref.first[of_first_row_i][of_first_column_i + 1] + 
                matrices_ref.second[of_first_column_i][of_second_column_i]);

            // if (of_second_column_i == 1){
            //     std::cout << matrices_ref.first[of_first_row_i][of_first_column_i] << "  "
            //         << matrices_ref.second[of_first_column_i + 1][of_second_column_i] << std::endl;
                // std::cout << first_matrix_multiplicator_ << " ";
            // }
            multiplicators_calculation(
                first_matrix_multiplicator_,
                second_matrix_multiplicators_,  
                of_first_row_i,
                of_first_column_i,
                of_second_column_i
            );
    }
    // std::cout << std::endl;
    //         std::cout << element_result << std::endl;
    //         std::cout << first_matrix_multiplicator_ << std::endl;
    //         std::cout << second_matrix_multiplicators_[of_second_column_i] << std::endl;
    //         exit(0);
    // if (of_second_column_i == 1){
    //     std::cout << std::endl;
    //     std::cout << element_result << std::endl;
    //     std::cout << first_matrix_multiplicator_ << std::endl;
    //     std::cout << second_matrix_multiplicators_[of_second_column_i] << std::endl;
    //     exit(0);
    // }
    element_result += extra_muliplier(of_first_row_i, of_second_column_i);
    element_result -= 
        first_matrix_multiplicator_ + 
        second_matrix_multiplicators_[of_second_column_i];
    return element_result;
}


WinogradUsual::multiplicators_func WinogradUsual::DefineMultiplicatorsFunc_(
                                        WhitchMultiplicatorsCalculate code,
                                        matrices_pair_reference matrices_ref){
    multiplicators_func return_func;
    
    switch (code){
        // For first element in row & all rows exclude first: 
        // - first_matrix_multiplicator wasn't calculated
        // - all second_matrix multiplications were calculated
        case WhitchMultiplicatorsCalculate::FIRST:
            return_func = 
                [&matrices_ref](
                    elements_type& first_matrix_multiplicator,
                    multiplicators_arrray_reference, 
                    row_size_type row_i, 
                    column_size_type column_i,
                    column_size_type
                ) -> void {
                    first_matrix_multiplicator += 
                        matrices_ref.first[row_i][column_i] *
                        matrices_ref.first[row_i][column_i + 1];
                };
            break;

        // For first element in row & first row:
        // - first_matrix_multiplicator wasn't calculated
        // - second_matrix multiplications weren't calculated
        case WhitchMultiplicatorsCalculate::FIRST_SECOND:
            return_func = 
                [&matrices_ref](
                    elements_type& first_matrix_multiplicator,
                    multiplicators_arrray_reference of_second_multiplicators, 
                    row_size_type row_i, 
                    column_size_type column_i,
                    column_size_type of_second_column_i
                ) -> void {
                    first_matrix_multiplicator += 
                        matrices_ref.first[row_i][column_i] *
                        matrices_ref.first[row_i][column_i + 1];

                    of_second_multiplicators[of_second_column_i] += 
                        matrices_ref.second[column_i][of_second_column_i] *
                        matrices_ref.second[column_i + 1][of_second_column_i];
                };
            break;
            
        // For all elements exclude first & first row:
        // - first_matrix_multiplicator was calculated
        // - second_matrix multiplications weren't calculated
        case WhitchMultiplicatorsCalculate::SECOND:
            return_func = 
                [&matrices_ref](
                    elements_type&,
                    multiplicators_arrray_reference of_second_multiplicators, 
                    row_size_type, 
                    column_size_type column_i,
                    column_size_type of_second_column_i
                ) -> void {
                    of_second_multiplicators[of_second_column_i] += 
                        matrices_ref.second[column_i][of_second_column_i] *
                        matrices_ref.second[column_i + 1][of_second_column_i];
                };
            break;

        // For all elements exclude first & all rows exclude first:
        // - first_matrix_multiplicator was calculated
        // - second_matrix multiplications were calculated
        case WhitchMultiplicatorsCalculate::NO_ONE:
            return_func = 
                [&matrices_ref](
                    elements_type&,
                    multiplicators_arrray_reference, 
                    row_size_type, 
                    column_size_type,
                    column_size_type
                ) -> void { };
            break;
    }
    return return_func;
}

WinogradUsual::multiplications_calculate_pair 
    WinogradUsual::DefineMultiplicationCalculationSolution_(
                                WhichMultiplicationCalculationSolution code){
    multiplications_calculate_pair return_pair;

    switch(code){
        case WhichMultiplicationCalculationSolution::FOR_FIRST_ELEM:
            if (second_matrix_multiplicators_.empty()){
                return_pair.first = WhitchMultiplicatorsCalculate::FIRST_SECOND;
                return_pair.second = WhitchMultiplicatorsCalculate::SECOND;
            } else {
                return_pair.first = WhitchMultiplicatorsCalculate::FIRST;
                return_pair.second = WhitchMultiplicatorsCalculate::NO_ONE;
            }
            break;
        case WhichMultiplicationCalculationSolution::FOR_NEXT_ELEMS:
            return_pair.first = WhitchMultiplicatorsCalculate::FIRST;
            return_pair.second = WhitchMultiplicatorsCalculate::NO_ONE;
            break;
    }
    return return_pair;
}


}