#ifndef MATRIX_H
#error 'matrix_iml.h' is not supposed to be included directly. \
        Include 'matrix.h' instead.
#endif

namespace s21{

template< class T >
Matrix<T>::Matrix(const matrix_type& inp_matrix) : matrix_(inp_matrix){
    
}

template< class T >
Matrix<T>::Matrix(matrix_type&& inp_matrix) : matrix_(std::move(inp_matrix)){ 
    
}

template< class T >
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other){
    if (this == &other) return *this;
    ThrowOnNonEmptyMatrix_();
    matrix_ = other.matrix_;
    return *this;
}

template< class T >
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other){
    if (this == &other) return *this;
    ThrowOnNonEmptyMatrix_();
    matrix_ = std::move(other.matrix_);
    return *this;
}

template< class T >
typename Matrix<T>::reference Matrix<T>::operator[](row_size_type pos){
    return matrix_.operator[](pos);
}

template< class T >
typename Matrix<T>::const_reference Matrix<T>::operator[](
                                                    row_size_type pos) const{
    return matrix_.operator[](pos);
}

template< class T >
typename Matrix<T>::value_type Matrix<T>::At(row_size_type row, 
                                            column_size_type col){
    return matrix_[row][col];
}

template< class T >
typename Matrix<T>::value_type Matrix<T>::At(row_size_type row, 
                                            column_size_type col) const{
    return matrix_[row][col];
}

template< class T >
typename Matrix<T>::row_size_type Matrix<T>::RowsSize() const{
    return matrix_.size();
}

template< class T >
typename Matrix<T>::column_size_type Matrix<T>::ColumnsSize() const{
    return matrix_.size() ? matrix_.begin()->size() : 0;
}

template< class T >
typename Matrix<T>::iterator_type Matrix<T>::Begin(){
    return matrix_.begin();
}

template< class T >
typename Matrix<T>::const_iterator_type Matrix<T>::Begin() const{
    return matrix_.begin();
}

template< class T >
typename Matrix<T>::iterator_type Matrix<T>::End(){
    return matrix_.end();
}

template< class T >
typename Matrix<T>::const_iterator_type Matrix<T>::End() const{
    return matrix_.end();
}

template< class T >
typename Matrix<T>::reverse_iterator_type Matrix<T>::Rbegin(){
    return matrix_.rbegin();
}

template< class T >
typename Matrix<T>::reverse_const_iterator_type Matrix<T>::Rbegin() const{
    return matrix_.rbegin();
}

template< class T >
typename Matrix<T>::reverse_iterator_type Matrix<T>::Rend(){
    return matrix_.rend();
}

template< class T >
typename Matrix<T>::reverse_const_iterator_type Matrix<T>::Rend() const{
    return matrix_.rend();
}

template< class T >
Matrix<T> Matrix<T>::LoadFromFile(const std::string& filename){
    std::ifstream file_stream;
    int rows_count, columns_count;

    // Open file
    std::ifstream input_file_stream;
    input_file_stream.open(filename);
    if (!input_file_stream.is_open()){
        throw MatrixException("Cannot open file: " + filename);
    }

    // Read rows and columns count
    input_file_stream >> rows_count;
    input_file_stream >> columns_count;
    if (rows_count < 1 || columns_count < 1){
        throw MatrixException("Columns or rows count cannot be non-positive");
    }

    return Matrix<T>(LoadMatrixFromFile_(
                        input_file_stream,
                        rows_count,
                        columns_count
                    ));
}

template< class T >
Matrix<T> Matrix<T>::LoadMatrixFromFile_(
    std::ifstream& input_file_stream,
    int rows_count,
    int columns_count
){
    matrix_type new_mtrx;
    new_mtrx.reserve(rows_count);
    for (int row = 0; row < rows_count; row++){
        row_matrix_type new_row;
        new_row.reserve(columns_count);
        for (int column = 0; column < columns_count; column++){
            T var;
            input_file_stream >> var;
            new_row.push_back(std::move(var));
        }
        new_mtrx.push_back(std::move(new_row));
    }

    return Matrix<T>(std::move(new_mtrx));
}

template< class T >
bool Matrix<T>::IsMatrixValid_(){
    if (!matrix_.size()){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                        "Invalid matrix: Matrix rows size must be positive");
        matrix_.clear();
        return false;
    }

    size_type columns_count;

    columns_count = matrix_.begin()->size();
    if (!columns_count){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                        "Invalid matrix: Matrix columns size must be positive");
        matrix_.clear();
        return false;
    }

    for (iterator_type row_it = matrix_.begin();
        row_it != matrix_.end();
        ++row_it
    ){
        if (row_it->size() != columns_count){
            PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, "Invalid matrix");
            matrix_.clear();
            return false;
        }
    }
    return true;
}

template< class T >
Matrix<T>::MatrixException::MatrixException(const std::string& msg)
    : ::s21::Exception(msg) {

}

template< class T >
std::string Matrix<T>::MatrixException::GetMessage() const{
    return ::s21::Exception::msg_;
}

template< class T >
void Matrix<T>::ThrowOnNonEmptyMatrix_() const{
    if (matrix_.size()) throw MatrixException("Matrix is not empty");
}

} // namespace s21
