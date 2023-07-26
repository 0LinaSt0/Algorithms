#ifndef __SLE_H__
#error 'sle_impl.h' is not supposed to be included directly. \
        Include 'sle.h' instead.
#endif

namespace s21{

template< class T >
Sle<T>::Sle(const Matrix<T>& inp_mtrx) : parent_type(inp_mtrx) {
    ThrowOnInvalidInputMatrix_();
}

template< class T >
Sle<T>::Sle(Matrix<T>&& inp_mtrx) : parent_type(std::move(inp_mtrx)) {
    ThrowOnInvalidInputMatrix_();
}

template< class T >
Sle<T>::Sle(const matrix_type& inp_mtrx) : parent_type(inp_mtrx) {
    ThrowOnInvalidInputMatrix_();
}

template< class T >
Sle<T>::Sle(matrix_type&& inp_mtrx) : parent_type(std::move(inp_mtrx)) {
    ThrowOnInvalidInputMatrix_();
}

template< class T >
Sle<T>& Sle<T>::operator=(const Sle& other){
    if (this == &other) return *this;
    this->matrix_ = other.matrix_;
    return *this;
}

template< class T >
Sle<T>& Sle<T>::operator=(Sle&& other){
    if (this == &other) return *this;
    this->matrix_ = other.matrix_;
    return *this;
}

template< class T >
Sle<T>::SleException::SleException(const std::string& msg)
    : ::s21::Exception(msg) {

}

template< class T >
std::string Sle<T>::SleException::GetMessage() const{
    return ::s21::Exception::msg_;
}

template< class T >
Sle<T> Sle<T>::LoadFromFile(const std::string& filename){
    std::ifstream file_stream;
    int rows_count, columns_count;

    // Open file
    std::ifstream input_file_stream;
    input_file_stream.open(filename);
    if (!input_file_stream.is_open()){
        throw SleException("Cannot open file: " + filename);
    }

    // Read rows and columns count
    input_file_stream >> rows_count;
    input_file_stream >> columns_count;
    if (rows_count < 1 || columns_count < 1 ||
            (rows_count == 1 && columns_count == 1) ||
            rows_count + 1 != columns_count){
        throw SleException("Invalid SLE");
    }

    return Sle<T>(Matrix<T>::LoadMatrixFromFile_(
                        input_file_stream,
                        rows_count,
                        columns_count
                    ));
}

template< class T >
void Sle<T>::ThrowOnInvalidInputMatrix_() const{
    if (Matrix<T>::RowsSize() == 1 && Matrix<T>::ColumnsSize() == 1){
        throw SleException("Invalid matrix size");
    }
}

}
