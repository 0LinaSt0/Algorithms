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

    //For first element
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

    current_element_result = CalculateElement_(
        matrices_ptr,
        of_first_row_i,
        0,
        extra_muliplier,
        multiplicators_calculation
    );
    result_row->push_back(current_element_result);


    //For next elements
    multiplicators_calculation = DefineMultiplicatorsFunc_(
        execute_codes.second,
        matrices_ptr
    );

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
            matrices_ptr->second[of_first_column_i + 1][of_second_column_i]) *
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


WinograPipelineParallel::WinograPipelineParallel() : WinogradParent() { }

void WinograPipelineParallel::RowsMultiplication_(
                                        matrices_pair_ptr matrices_ptr,
                                        extra_multiplier_func){
    InitThreadMutexes_(matrices_ptr);
    InitResultMtrx_(matrices_ptr);
    InitMultiplicators_(matrices_ptr);

    row_size_type rows_count = matrices_ptr->first.RowsSize();
    threads_.clear();
    threads_.reserve(MAX_STAGES);
    int next_id = 0;
    for (row_size_type row = 0; row < std::min(rows_count, MAX_STAGES); row++){
        Thread thread;
        thread.row = row;
        thread.id = next_id++;
        thread.thread = std::move(
            std::thread(
                GetThreadBody_(thread, matrices_ptr)
            )
        );
        threads_.push_back(std::move(thread));
    }
    start_thread_mutexes_[0].unlock();
    for (size_t row = 0; row < threads_.size(); row++){
        threads_[row].thread.join();
    }
}

void WinograPipelineParallel::InitThreadMutexes_(matrices_pair_ptr matrices_ptr){
    row_size_type rows_count = matrices_ptr->first.RowsSize();
    
    start_thread_mutexes_ = std::move(std::vector<std::mutex>(rows_count));
    for (row_size_type i = 0; i < rows_count; i++){
        start_thread_mutexes_[i].lock();
    }
}

void WinograPipelineParallel::InitResultMtrx_(matrices_pair_ptr matrices_ptr){
    row_size_type rows_count = matrices_ptr->first.RowsSize();
    column_size_type columns_count = matrices_ptr->second.ColumnsSize();

    result_matrix_.matrix_array.reserve(rows_count);
    for (row_size_type i = 0; i < rows_count; i++){
        result_matrix_type::rows_type new_row(columns_count);
        result_matrix_.matrix_array.push_back(std::move(new_row));
    }
}

void WinograPipelineParallel::InitMultiplicators_(
    matrices_pair_ptr matrices_ptr
){
    column_size_type columns_count = matrices_ptr->second.ColumnsSize();

    multiplicators_b_ = std::move(std::vector<double>(
        columns_count, 
        std::numeric_limits<double>::quiet_NaN()
    ));
}

std::function<void ()> WinograPipelineParallel::GetThreadBody_(
    Thread& thread,
    matrices_pair_ptr matrices_ptr
){
    return [this, &thread, matrices_ptr](){
        matrix_type_reference A = matrices_ptr->first;
        matrix_type_reference B = matrices_ptr->second;

        while (true){
            row_size_type row = thread.row;

            // Wait for the thrad's start
            this->start_thread_mutexes_[row].lock();
            this->start_thread_mutexes_[row].unlock();

            // Create row's multiplicator
            double multi_a = 0;
            for (column_size_type col = 0; col + 1 < A.ColumnsSize(); col += 2){
                multi_a += A[row][col] * A[row][col + 1];
            }

            // Calculate row of result mtrx
            for (column_size_type col = 0; col < B.ColumnsSize(); col++){
                double multi_b = multiplicators_b_[col];
                // Create column's multiplicator
                if (std::isnan(multi_b)){
                    multi_b = 0;
                    for (row_size_type i = 0; i + 1 < B.RowsSize(); i += 2){
                        multi_b += B[i][col] * B[i + 1][col];
                    }
                    std::lock_guard guard(this->multiplicators_b_mutex_);
                    this->multiplicators_b_[col] = multi_b;
                }
                        
                // Continue row calculation
                double res = 0;
                column_size_type columns_count = A.ColumnsSize();
                for (column_size_type i = 0; i < columns_count; i++){
                    if (i + 1 < columns_count) {
                        res += (A[row][i] + B[i + 1][col]) *
                                (A[row][i + 1] + B[i][col]);
                        i++;
                    } else {
                        res += A[row][i] * B[i][col];
                    }
                }
                res -= multi_a + multi_b;
                this->result_matrix_.matrix_array[row][col] = res;
            
                // Let next thread start
                if (col == 0 && row + 1 != A.RowsSize()){
                    // FIND OUT NEXT THREAD ID
                    // CHANGE ITS ROW
                    // UNLCOCK MUTEX
                }
            }
        }
    };
}

}
