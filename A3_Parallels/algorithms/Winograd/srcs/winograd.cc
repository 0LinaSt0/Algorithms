#include "../includes/winograd.h"

namespace s21{

WinogradParent::WinogradParent() { }

WinogradParent::result_matrix_type WinogradParent::WinogradMultiplication(
                                    matrix_type_const_ref matrix_first,
                                    matrix_type_const_ref matrix_second){
    if(!IsMatricesInvalid_(
        matrix_first.ColumnsSize(), matrix_second.RowsSize()
    )){
        matrices_pair matrices{matrix_first, matrix_second};

        StartMultiplication_(&matrices);
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

void WinogradParent::StartMultiplication_(matrices_pair_ptr matrices_ptr){
    extra_multiplier_func extra_muliplier;

    extra_muliplier = MatrixMultiplication_(matrices_ptr);
    RowsMultiplication_(
        matrices_ptr,
        extra_muliplier
    );
}

WinogradParent::extra_multiplier_func WinogradParent::MatrixMultiplication_(
                                                matrices_pair_ptr matrices_ptr){
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
    return extra_muliplier;
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
                    elements_type first_matrix_multiplicator,
                    multiplicators_arrray_reference,
                    row_size_type row_i,
                    column_size_type column_i,
                    column_size_type
                ) -> elements_type {
                    first_matrix_multiplicator +=
                        matrices_ptr->first[row_i][column_i] *
                        matrices_ptr->first[row_i][column_i + 1];
                    return first_matrix_multiplicator;
                };
            break;

        // For first element in row & first row:
        // - first_matrix_multiplicator wasn't calculated
        // - second_matrix multiplications weren't calculated
        case WhitchMultiplicatorsCalculate::FIRST_SECOND:
            return_func =
                [matrices_ptr](
                    elements_type first_matrix_multiplicator,
                    multiplicators_arrray_reference of_second_multiplicators,
                    row_size_type row_i,
                    column_size_type column_i,
                    column_size_type of_second_column_i
                ) -> elements_type {
                    first_matrix_multiplicator +=
                        matrices_ptr->first[row_i][column_i] *
                        matrices_ptr->first[row_i][column_i + 1];

                    of_second_multiplicators[of_second_column_i] +=
                        matrices_ptr->second[column_i][of_second_column_i] *
                        matrices_ptr->second[column_i + 1][of_second_column_i];
                    return first_matrix_multiplicator;
                };
            break;

        // For all elements exclude first & first row:
        // - first_matrix_multiplicator was calculated
        // - second_matrix multiplications weren't calculated
        case WhitchMultiplicatorsCalculate::SECOND:
            return_func =
                [matrices_ptr](
                    elements_type first_matrix_multiplicator,
                    multiplicators_arrray_reference of_second_multiplicators,
                    row_size_type,
                    column_size_type column_i,
                    column_size_type of_second_column_i
                ) -> elements_type {
                    of_second_multiplicators[of_second_column_i] +=
                        matrices_ptr->second[column_i][of_second_column_i] *
                        matrices_ptr->second[column_i + 1][of_second_column_i];
                return first_matrix_multiplicator;
                };
            break;

        // For all elements exclude first & all rows exclude first:
        // - first_matrix_multiplicator was calculated
        // - second_matrix multiplications were calculated
        case WhitchMultiplicatorsCalculate::NO_ONE:
            return_func =
                [matrices_ptr](
                    elements_type first_matrix_multiplicator,
                    multiplicators_arrray_reference,
                    row_size_type,
                    column_size_type,
                    column_size_type
                ) -> elements_type {
                    (void) matrices_ptr;
                    return first_matrix_multiplicator;
                };
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
    elements_type first_matrix_multiplicator;

    execute_codes = DefineMultiplicationCalculationSolution_(type_row_code);
    first_matrix_multiplicator = 0;

    //For first element
    multiplicators_calculation = DefineMultiplicatorsFunc_(
        execute_codes.first,
        matrices_ptr
    );

    current_element_result = CalculateElement_(
        matrices_ptr,
        of_first_row_i,
        0,
        extra_muliplier,
        multiplicators_calculation,
        first_matrix_multiplicator
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
            multiplicators_calculation,
            first_matrix_multiplicator
        );
        result_row->push_back(current_element_result);

    }
    first_matrix_multiplicator = 0;
    return result_row;
}

WinogradParent::elements_type
    WinogradParent::CalculateElement_(matrices_pair_ptr matrices_ptr,
                    row_size_type of_first_row_i,
                    column_size_type of_second_column_i,
                    extra_multiplier_func extra_muliplier,
                    multiplicators_func multiplicators_calculation,
                    elements_type& first_matrix_multiplicator){
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

        first_matrix_multiplicator = multiplicators_calculation(
            first_matrix_multiplicator,
            second_matrix_multiplicators_,
            of_first_row_i,
            of_first_column_i,
            of_second_column_i
        );
    }
    element_result += extra_muliplier(of_first_row_i, of_second_column_i);
    element_result -=
        first_matrix_multiplicator +
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
        WhichMultiplicationCalculationSolution::FOR_FIRST_ELEM
    );
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


WinogradParallel::WinogradParallel(size_t threads_count)
                            : WinogradParent(), threads_count_(threads_count){ }

void WinogradParallel::ResultMatrixDefaultInitialization_(
                                            row_size_type of_first_rows_count){
    for(row_size_type i = 0; i < of_first_rows_count; i++){
        result_matrix_.matrix_array.push_back(result_matrix_rows_type());
    }
}

void WinogradParallel::RowsMultiplication_(matrices_pair_ptr matrices_ptr,
                                    extra_multiplier_func extra_muliplier){

    matrix_rows_unique_ptr current_result_row;
    row_size_type of_first_rows_count;

    of_first_rows_count = matrices_ptr->first.RowsSize();
    ResultMatrixDefaultInitialization_(matrices_ptr->first.RowsSize());

    // For first row
    current_result_row = CalculateRow_(
        matrices_ptr,
        0,
        extra_muliplier,
        WhichMultiplicationCalculationSolution::FOR_FIRST_ELEM);
    result_matrix_.matrix_array[0] = std::move(*current_result_row);

    // For next rows
    try{
        threads_array_type threads_array;

        for(size_t thread_i = 0;
            of_first_rows_count > 1 &&
            thread_i < threads_count_;
            thread_i++
        ){
            threads_array.push_back(std::thread(
                &WinogradParallel::RowsParallelism_,
                this,
                matrices_ptr,
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
                                    extra_multiplier_func extra_muliplier){
    matrix_rows_unique_ptr current_result_row;

    for(row_size_type of_first_row_i = 1;
            of_first_row_i < matrices_ptr->first.RowsSize();
            of_first_row_i++
        ){
            std::lock_guard<mutex_type> locker(lock_);
            if (result_matrix_.matrix_array[of_first_row_i].empty()){
                current_result_row = CalculateRow_(
                    matrices_ptr,
                    of_first_row_i,
                    extra_muliplier,
                    WhichMultiplicationCalculationSolution::FOR_NEXT_ELEMS
                );
                result_matrix_.matrix_array[of_first_row_i] =
                                            std::move(*current_result_row);
            }
        }
}


WinograPipelineParallel::WinograPipelineParallel() : WinogradParent() { }

void WinograPipelineParallel::RowsMultiplication_(
                                        matrices_pair_ptr matrices_ptr,
                                        extra_multiplier_func){
    InitResultMtrx_(matrices_ptr);
    InitMultiplicators_(matrices_ptr);

    row_size_type rows_count = matrices_ptr->first.RowsSize();
    row_size_type stages_count = std::min(rows_count, MAX_STAGES);

    rows_done_ = 0;
    stages_.reserve(stages_count);
    
    std::vector<std::mutex> m1(stages_count);
    std::vector<std::mutex> m2(stages_count);
    start_mutexes_ = std::move(m1);
    stages_mutexes_ = std::move(m2);
   
    int next_id = 0;
    for (row_size_type row = 0; row < stages_count; row++){
        Stage s;
        stages_.push_back(std::move(s));
        
        Stage& stage = stages_.back();
        stage.id = next_id++;

        std::thread th = std::thread(
            GetThreadBody_(stages_.back(), stages_count, matrices_ptr)
        );
        stage.thread = std::move(th);
    }

    stages_[0].rows.push(0);
    for (Stage& stage : stages_){
        stage.thread.join();
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

    std::vector<double> mb(
        columns_count, 
        std::numeric_limits<double>::quiet_NaN()
    );
    multiplicators_b_ = std::move(mb);
}

std::function<void ()> WinograPipelineParallel::GetThreadBody_(
    Stage& stage,
    row_size_type max_stage,
    matrices_pair_ptr matrices_ptr
){
    return [this, &stage, max_stage, matrices_ptr](){
        matrix_type_const_ref A = matrices_ptr->first;
        matrix_type_const_ref B = matrices_ptr->second;
        row_size_type max_rows = A.RowsSize();

        while (true){
            while (true) {
                if (this->rows_done_ == max_rows || !stage.rows.empty()) {
                    break;
                }
                usleep(500);
            }

            // Get next row number
            if (this->rows_done_ == max_rows) break;
            this->stages_mutexes_[stage.id].lock();
            row_size_type row = stage.rows.front();
            stage.rows.pop();
            this->stages_mutexes_[stage.id].unlock();
        
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
                    row_size_type next_row = row + 1;
                    int next_stage_id = 
                        (stage.id + 1 == static_cast<int>(max_stage)) ?
                        0 :
                        stage.id + 1;

                    // Update row next stage to work with
                    this->stages_mutexes_[next_stage_id].lock();
                    this->stages_[next_stage_id].rows.push(next_row);
                    this->stages_mutexes_[next_stage_id].unlock();
                }
            }
            
            this->rows_done_++;
        }
    };
}

}
