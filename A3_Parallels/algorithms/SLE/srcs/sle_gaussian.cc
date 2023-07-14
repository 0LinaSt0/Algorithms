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
    reverse_iterator_type last_equation_it = matrix_->Rbegin() - 1;
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

    double left_side;
    double root_value;
    column_rev_it root_factor_rev_it;

    left_side = 0;
    root_value = 0;
    root_factor_rev_it = row_rev_it->rbegin() + 1;
    for(result_roots_type::sle_type::const_reverse_iterator root_rev_it
        = roots_.equation_roots.rbegin();
        root_rev_it != roots_.equation_roots.rend();
        ++root_rev_it, ++root_factor_rev_it
    ){
        left_side += (*root_rev_it) * (*root_factor_rev_it);
    }
    root_value = ((*row_rev_it->rbegin()) - root_value) / (*root_factor_rev_it);
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
        // HERE MATRIX ELEMENTS SHOULD BE DOUBLE TYPE
        current_multiplier = (*matrix_)[row_i][current_i] /
                                (*matrix_)[current_i][current_i];
        for(matrix_size_type column_i = current_i;
            column_i <= roots_count_; // <= because we need to reduse and the right hand side of equation
            column_i++
        ){
            // HERE ALL IT SHOULD BE SAVED TO DOUBLE ARRAY
            (*matrix_)[row_i][column_i] -=
                        (*matrix_)[current_i][column_i] * current_multiplier;
        }
    }
}

}
