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
        MatrixMultiplication_(&matrices);
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

void WinogradParent::MatrixMultiplication_(matrices_pair_ptr matrices_ptr){
    extra_multiplier_func extra_muliplier;
    
    if (matrices_ptr->first.ColumnsSize() % 2){
        extra_muliplier = 
            [matrices_ptr]
            (row_size_type of_first_row_i, column_size_type of_second_column_i)
            -> elements_type {
                elements_type returned_multiplicator;

                returned_multiplicator = 
                    matrices_ptr->first[of_first_row_i].back() * 
                    matrices_ptr->second.Back()[of_second_column_i];
                return returned_multiplicator;
            };
    } else {
        extra_muliplier = 
            [](row_size_type, column_size_type) -> elements_type { return 0; };
    }
    RowsMultiplication_(
        matrices_ptr, 
        extra_muliplier
    );
}

WinogradParent::multiplicators_func WinogradParent::DefineMultiplicatorsFunc_(
                                        WhitchMultiplicatorsCalculate code,
                                        matrices_pair_ptr matrices_ptr){
    multiplicators_func return_func;
    
    switch (code){
        // For first element in row & all rows exclude first: 
        // - first_matrix_multiplicator wasn't calculated
        // - all second_matrix multiplications were calculated
        case WhitchMultiplicatorsCalculate::FIRST:
            return_func = 
                [matrices_ptr](
                    elements_type& first_matrix_multiplicator,
                    multiplicators_arrray_reference, 
                    row_size_type row_i, 
                    column_size_type column_i,
                    column_size_type
                ) -> void {
                    first_matrix_multiplicator += 
                        matrices_ptr->first[row_i][column_i] *
                        matrices_ptr->first[row_i][column_i + 1];
                };
            break;

        // For first element in row & first row:
        // - first_matrix_multiplicator wasn't calculated
        // - second_matrix multiplications weren't calculated
        case WhitchMultiplicatorsCalculate::FIRST_SECOND:
            return_func = 
                [matrices_ptr](
                    elements_type& first_matrix_multiplicator,
                    multiplicators_arrray_reference of_second_multiplicators, 
                    row_size_type row_i, 
                    column_size_type column_i,
                    column_size_type of_second_column_i
                ) -> void {
                    first_matrix_multiplicator += 
                        matrices_ptr->first[row_i][column_i] *
                        matrices_ptr->first[row_i][column_i + 1];

                    of_second_multiplicators[of_second_column_i] += 
                        matrices_ptr->second[column_i][of_second_column_i] *
                        matrices_ptr->second[column_i + 1][of_second_column_i];
                };
            break;
            
        // For all elements exclude first & first row:
        // - first_matrix_multiplicator was calculated
        // - second_matrix multiplications weren't calculated
        case WhitchMultiplicatorsCalculate::SECOND:
            return_func = 
                [matrices_ptr](
                    elements_type&,
                    multiplicators_arrray_reference of_second_multiplicators, 
                    row_size_type, 
                    column_size_type column_i,
                    column_size_type of_second_column_i
                ) -> void {
                    of_second_multiplicators[of_second_column_i] += 
                        matrices_ptr->second[column_i][of_second_column_i] *
                        matrices_ptr->second[column_i + 1][of_second_column_i];
                };
            break;

        // For all elements exclude first & all rows exclude first:
        // - first_matrix_multiplicator was calculated
        // - second_matrix multiplications were calculated
        case WhitchMultiplicatorsCalculate::NO_ONE:
            return_func = 
                [matrices_ptr](
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

WinogradParent::multiplications_calculate_pair 
    WinogradParent::DefineMultiplicationCalculationSolution_(
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


WinogradUsual::WinogradUsual() : WinogradParent() { }

void WinogradUsual::RowsMultiplication_(matrices_pair_ptr matrices_ptr,
                                    extra_multiplier_func extra_muliplier){
    
    matrix_rows_unique_ptr current_result_row;

    // For first row
    current_result_row = CalculateRow_(
        matrices_ptr,
        0,
        extra_muliplier, 
        WhichMultiplicationCalculationSolution::FOR_FIRST_ELEM);
    result_matrix_.matrix_array.push_back(*current_result_row);
    
    // For next rows
    for(row_size_type of_first_row_i = 1;
        of_first_row_i < matrices_ptr->first.RowsSize();
        of_first_row_i++
    ){
        current_result_row = CalculateRow_(
            matrices_ptr,
            of_first_row_i,
            extra_muliplier,
            WhichMultiplicationCalculationSolution::FOR_NEXT_ELEMS);
        result_matrix_.matrix_array.push_back(*current_result_row);
    }
}

WinogradParent::matrix_rows_unique_ptr 
    WinogradParent::CalculateRow_(matrices_pair_ptr matrices_ptr,
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
        matrices_ptr
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
        matrices_ptr,
        of_first_row_i, 
        0,
        extra_muliplier,
        multiplicators_calculation
    );
    result_row->push_back(current_element_result);
    multiplicators_calculation = DefineMultiplicatorsFunc_(
        execute_codes.second,
        matrices_ptr
    );

    //For next elements
    for(column_size_type of_second_column_i = 1;
        of_second_column_i < matrices_ptr->second.ColumnsSize();
        of_second_column_i++
    ){
        current_element_result = CalculateElement_(
            matrices_ptr,
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

WinogradParent::elements_type 
    WinogradParent::CalculateElement_(matrices_pair_ptr matrices_ptr,
                    row_size_type of_first_row_i,
                    column_size_type of_second_column_i,
                    extra_multiplier_func extra_muliplier,
                    multiplicators_func multiplicators_calculation){
    elements_type element_result;

    element_result = 0;
    for(column_size_type of_first_column_i = 0;
            of_first_column_i < matrices_ptr->first.ColumnsSize() - 1;
            of_first_column_i += 2
    ){
            element_result += 
                (matrices_ptr->first[of_first_row_i][of_first_column_i] + 
                matrices_ptr->second[of_first_column_i + 1][of_second_column_i])*
                (matrices_ptr->first[of_first_row_i][of_first_column_i + 1] + 
                matrices_ptr->second[of_first_column_i][of_second_column_i]);

            // if (of_second_column_i == 1){
            //     std::cout << matrices_ptr.first[of_first_row_i][of_first_column_i] << "  "
            //         << matrices_ptr.second[of_first_column_i + 1][of_second_column_i] << std::endl;
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


WinogradParallel::WinogradParallel() : WinogradParent() { }

void WinogradParallel::RowsMultiplication_(matrices_pair_ptr matrices_ptr,
                                    extra_multiplier_func extra_muliplier){
    
    matrix_rows_unique_ptr current_result_row;

    // For first row
    current_result_row = CalculateRow_(
        matrices_ptr,
        0,
        extra_muliplier, 
        WhichMultiplicationCalculationSolution::FOR_FIRST_ELEM);
    result_matrix_.matrix_array.push_back(*current_result_row);
    
    // For next rows
    try{
        threads_array_type threads_array;

        for(row_size_type of_first_row_i = 1;
            of_first_row_i < matrices_ptr->first.RowsSize();
            of_first_row_i++
        ){
            threads_array.push_back(std::thread(
                &WinogradParallel::RowsParallelism_,
                this, 
                matrices_ptr,
                of_first_row_i,
                extra_muliplier
            ));
        }
        JoinThreads(threads_array);
    } catch(const std::exception &e){
        std::string error = "Threads problems: ";
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, error + e.what());
    }
}

void WinogradParallel::RowsParallelism_(matrices_pair_ptr matrices_ptr,
                                    row_size_type of_first_row_i,
                                    extra_multiplier_func extra_muliplier){
    matrix_rows_unique_ptr current_result_row;

    current_result_row = CalculateRow_(
        matrices_ptr,
        of_first_row_i,
        extra_muliplier,
        WhichMultiplicationCalculationSolution::FOR_NEXT_ELEMS
    );
    std::lock_guard<mutex_type> locker(lock_);
    result_matrix_.matrix_array.push_back(*current_result_row);
}

}