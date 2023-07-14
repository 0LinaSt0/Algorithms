#ifndef MATRIX_H
#error 'matrix_iml.h' is not supposed to be included directly. \
        Include 'matrix.h' instead.
#endif

namespace s21{

template< class T >
Matrix<T>::Matrix(const matrix_type& inp_matrix) : matrix_(inp_matrix){
    IsMatrixValid_();
}

template< class T >
Matrix<T>::Matrix(matrix_type&& inp_matrix)
    : matrix_(std::move(inp_matrix)){ IsMatrixValid_(); }

template< class T >
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other){
    if (matrix_.size()) {
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, "Matrix is not empty");
    } else {
        matrix_ = other.matrix_;
        IsMatrixValid_();
    }
    return *this;
}

template< class T >
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other){
    if (matrix_.size()) {
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, "Matrix is not empty");
    } else {
        matrix_ = std::move(other.matrix_);
        IsMatrixValid_();
    }
    return *this;
}

template< class T >
typename Matrix<T>::reference Matrix<T>::operator[](size_type pos){
    return matrix_.operator[](pos);
}

template< class T >
typename Matrix<T>::const_reference Matrix<T>::operator[](size_type pos) const{
    return matrix_.operator[](pos);
}

template< class T >
typename Matrix<T>::value_type Matrix<T>::at(size_type row, size_type col){
    return matrix_[row][col];
}

template< class T >
typename Matrix<T>::value_type Matrix<T>::at(size_type row, size_type col) const{
    return matrix_[row][col];
}

template< class T >
typename Matrix<T>::size_type Matrix<T>::RowsSize() const{
    return matrix_.size();
}

template< class T >
typename Matrix<T>::size_type Matrix<T>::ColumnsSize() const{
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
bool Matrix<T>::LoadFromFile(std::string filename){
    std::ifstream file_stream;
    int size;

    size = GeneralFromFileValidation_(filename, file_stream);
    if (size){
        for (int i = 0; i < size; i++){
            row_matrix_type row;
            row.reserve(size);
            for (int j = 0; j < size; j++){
                int val;
                if (!(file_stream >> val)){
                    PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                                    "Invalid file line");
                    matrix_.clear();
                    return false;
                }
                row.push_back(val);
            }
            matrix_.push_back(std::move(row));
        }
        return true;
    }
    return false;
}

template< class T >
int Matrix<T>::GeneralFromFileValidation_(std::string filename,
                                        std::ifstream& file_stream){
    if (matrix_.size()){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                    "Current 1 is not emtpy");
        return 0;
    }

    file_stream.open(filename, std::ios_base::in);
    if (!file_stream.is_open()){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                        "Cannot open file " + filename);
        return 0;
    }

    int size;
    file_stream >> size;
    if (size <= 0){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                        "Matrix size must be positive");
        return 0;
    }

    matrix_.reserve(size);
    return size;
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

}

template <class type>
std::ostream& operator<<(std::ostream& out, const s21::Matrix<type>& matrix){
    for (size_t x = 0; x < matrix.RowsSize(); x++){
    for (size_t y = 0; y < matrix.ColumnsSize(); y++){
        out << matrix.at(x, y);
        if (y + 1 != matrix.ColumnsSize()) out << "\t";
        else out << std::endl;
    }
    }
    return out;
}
