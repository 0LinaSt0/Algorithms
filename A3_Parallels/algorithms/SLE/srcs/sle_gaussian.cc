#include "../includes/sle_gaussian.h"

namespace s21{

SleGaussianParent::SleGaussianParent(matrix_type_reference graph) 
                    : matrix_(new matrix_type(graph)){
    equations_count_ = matrix_->Size();
    roots_count_ = matrix_->Size() ? (matrix_->Begin()->size() - 1) : 0;
}

SleGaussianParent::result_roots_type SleGaussianParent::GaussianElimination(){
    if(!matrix_->Size()){ 
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,  "Matrix is empty");
    }

    for(matrix_size_type current_i = 0; 
        current_i < equations_count_; 
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

bool SleGaussianParent::DetermineSingular_(){
    matrix_iterator_type last_equation_it = 
                                        matrix_->Begin() + matrix_->Size() - 1;
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

void SleGaussianParent::DetermineResult_(){
    if(!DetermineSingular_()){
        DetermineRoots_();
    }
}


SleGaussianUsual::SleGaussianUsual(matrix_type_reference graph) 
    : SleGaussianParent(graph){}

void SleGaussianUsual::ReduceRows_(matrix_size_type current_i){
    double current_multiplier;

    current_multiplier = 0;
    for(matrix_size_type row_i = current_i + 1; 
        row_i < equations_count_; 
        row_i++
    ){
        // HERE MATRIX ELEMENTS SHOUD BE DOUBLE TYPE
        current_multiplier = (*matrix_)[row_i][current_i] / 
                                (*matrix_)[current_i][current_i];
        for(matrix_size_type column_i = current_i; 
            column_i <= roots_count_; // <= because we need to reduse and the right hand side of equation
            column_i++
        ){
            // HERE ALL IT SHOUD BE SAVED TO DOUBLE ARRAY
            (*matrix_)[row_i][column_i] -= 
                        (*matrix_)[current_i][current_i] * current_multiplier;
        }
    }
}

void SleGaussianUsual::DetermineRoots_(){
    double current_root_value;

    // HERE SHOULD BE RECURITON
    current_root_value = 0;
    for(reverse_iterator_type rev_row_it = matrix_->Rbegin(); 
        rev_row_it != matrix_->Rend();
        ++rev_row_it
    ){
        for(auto rev_column_it = rev_row_it->rbegin() + 1;
            rev_column_it != rev_row_it->rend() && (*rev_column_it) != 0;
            ++rev_column_it
        ){
            current_root_value = rev_row_it->rbegin() / 
            roots_.equation_roots.insert(
                roots_.equation_roots.begin(), )
        }
    }
}

}