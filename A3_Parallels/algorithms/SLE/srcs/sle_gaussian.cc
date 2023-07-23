#include "../includes/sle_gaussian.h"

namespace s21{

SleGaussianParent::SleGaussianParent(matrix_type_reference matrix)
                    : matrix_(new matrix_type(matrix)){
    equations_count_ = matrix_->RowsSize();
    roots_count_ = matrix_->ColumnsSize() - 1;
}

SleGaussianParent::result_roots_type SleGaussianParent::GaussianElimination(){
    if(!matrix_->RowsSize()){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,  "Matrix is empty");
        return roots_;
    }

    for(matrix_size_type current_i = 0;
        current_i < equations_count_ - 1; // => Not sure about -1 but (as i understood) we don't need to check the last equation
        current_i++
    ){
        if((*matrix_)[current_i][current_i] == 0 && SwapRow_(current_i)){
            continue ;
        }
        ReduceRows_(current_i);
    }
    DetermineResult_();
    return roots_;
}

bool SleGaussianParent::CheckCalculatedFactors(matrix_type_reference matrix){
    if(!roots_.equation_roots.size()){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, "Roots array is empty");
        return false;
    }
    double current_left_side;
    
    current_left_side = 0;
    for(const_iterator_type row_it = matrix.Begin();
        row_it != matrix.End();
        ++row_it, current_left_side = 0
    ){
        for(matrix_size_type elem_i = 0;
            elem_i < (row_it->size() - 1);
            elem_i++
        ){
            current_left_side += 
                            row_it->at(elem_i) * roots_.equation_roots[elem_i];
        }
        if(current_left_side != (*row_it->rbegin())){
            return false;
        }
    }
    return true;
}

bool SleGaussianParent::SwapRow_(matrix_size_type swapped_i){
    for(matrix_size_type row_i = (swapped_i + 1);
        row_i < equations_count_;
        row_i++
    ){
        if((*matrix_)[row_i][swapped_i] != 0){
            std::iter_swap(
                matrix_->Begin() + row_i,
                matrix_->Begin() + swapped_i
            );
            return false;
        }
    }
    return true;
}

void SleGaussianParent::DetermineResult_(){
    if(!DetermineSingular_()){
        DetermineRoots_();
    }
}

bool SleGaussianParent::DetermineSingular_(){
    reverse_iterator_type last_equation_it = matrix_->Rbegin();
    auto is_all_roots_zero = [&last_equation_it](void) -> bool {
        if(last_equation_it->at(0) == 0){
            return std::equal(
                last_equation_it->begin(),
                last_equation_it->end() - 1,
                last_equation_it->begin() + 1
            );
        }
        return false;
    };

    if(is_all_roots_zero()){
        // If the right hand side equal zero value the SLE has many solutions
        if(*(last_equation_it->rbegin()) == 0){
            PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                UNSOLVABLE_MATRIX_MSG + ": SLE has infinitely many solutions");
        } else {
            PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                UNSOLVABLE_MATRIX_MSG + ": SLE is inconsistent");
        }
        return true;
    }
    return false;
}

void SleGaussianParent::DetermineRoots_(){
    double current_root_value;

    for(reverse_const_iterator_type row_rev_it = matrix_->Rbegin();
        row_rev_it != matrix_->Rend();
        ++row_rev_it
    ){
        current_root_value = DetermineRoot_(row_rev_it);
        roots_.equation_roots.insert(
            roots_.equation_roots.begin(), current_root_value
        );
    }
}

double SleGaussianParent::DetermineRoot_(
                            reverse_const_iterator_type& row_rev_it){
    using column_rev_it = matrix_type::row_matrix_type::const_reverse_iterator;
    using root_rev_it   = result_roots_type::sle_type::const_reverse_iterator;

    double right_side;
    double root_value;
    column_rev_it root_factor_rev_it;

    right_side = *row_rev_it->rbegin();
    root_factor_rev_it = row_rev_it->rbegin() + 1;
    for(root_rev_it root_rev_it = roots_.equation_roots.rbegin();
        root_rev_it != roots_.equation_roots.rend();
        ++root_rev_it, ++root_factor_rev_it
    ){
        right_side -= (*root_rev_it) * (*root_factor_rev_it);
    }
    root_value = right_side / (*root_factor_rev_it);
    return root_value;
}


SleGaussianUsual::SleGaussianUsual(matrix_type_reference matrix)
    : SleGaussianParent(matrix){}

void SleGaussianUsual::ReduceRows_(matrix_size_type current_i){
    double current_multiplier;

    current_multiplier = 0;
    for(matrix_size_type row_i = current_i + 1;
        row_i < equations_count_;
        row_i++
    ){
        current_multiplier = (*matrix_)[row_i][current_i] /
                                (*matrix_)[current_i][current_i];
        for(matrix_size_type column_i = current_i;
            column_i <= roots_count_; // <= because we need to reduse and the right hand side of equation
            column_i++
        ){
            (*matrix_)[row_i][column_i] -=
                        (*matrix_)[current_i][column_i] * current_multiplier;
        }
    }
}


SleGaussianParellel::SleGaussianParellel(matrix_type_reference matrix)
    : SleGaussianParent(matrix){}

void SleGaussianParellel::ReduceRows_(matrix_size_type current_i){

    try{
        threads_array_type threads_array;

        for(matrix_size_type row_i = current_i + 1;
                row_i < equations_count_;
                row_i++
            ){
                threads_array.push_back(std::thread(
                    &SleGaussianParellel::ParallelReducing_,
                    this,
                    row_i, 
                    current_i
                ));
            }

        JoinThreads(threads_array);
    } catch(const std::exception &e) {
        std::string error = "Threads problems: ";
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, error + e.what());
    }

}

void SleGaussianParellel::ParallelReducing_(matrix_size_type row_i, 
                                        matrix_size_type current_i){
    threads_array_type threads_array;
    double current_multiplier;

    current_multiplier = (*matrix_)[row_i][current_i] /
                                            (*matrix_)[current_i][current_i];

    for(matrix_size_type column_i = current_i;
            column_i <= roots_count_; // <= because we need to reduse and the right hand side of equation
            column_i++
    ){
        threads_array.push_back(std::thread(
            &SleGaussianParellel::ParallelReduceRow_,
            this,
            row_i,
            column_i, 
            current_i,
            current_multiplier
        ));
    }
    JoinThreads(threads_array);
}

void SleGaussianParellel::ParallelReduceRow_(matrix_size_type row_i, 
                    matrix_size_type column_i, matrix_size_type current_i, 
                    double multiplier){
    std::lock_guard<mutex_type> locker(lock_);
    (*matrix_)[row_i][column_i] -=
                (*matrix_)[current_i][column_i] * multiplier;
}



}
