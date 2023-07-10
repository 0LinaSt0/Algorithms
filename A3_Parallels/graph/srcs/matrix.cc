namespace s21{

template< class T >
Matrix<T>::Matrix(){ }

template< class T >
Matrix<T>::Matrix(const matrix_type& inp_matrix) : matrix_(inp_matrix){ }

template< class T >
Matrix<T>::Matrix(const matrix_type& inp_matrix)
    : matrix_(std::move(inp_matrix)){ }

template< class T >
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other){
    if (matrix_.size()) {
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, "Matrix is not empty");
    } else {
        matrix_ = other.matrix_;
    }
    return *this;
}

template< class T >
Matrix<T>& Matrix<T>::operator=(const Matrix<T>&& other){
    if (matrix_.size()) {
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, "Matrix is not empty");
    } else {
        matrix_ = std::move(other.matrix_);
    }
    return *this;
}

template< class T >
Matrix<T>::reference Matrix<T>:operator[](Matrix<T>::size_type pos){
    return matrix_.operator[](pos);
}

template< class T >
Matrix<T>::const_reference Matrix<T>:operator[](Matrix<T>::size_type pos) const{
    return matrix_.operator[](pos);
}

template< class T >
Matrix<T>::value_type Matrix<T>::at(size_type row, size_type col){
    return matrix_[row][col];
}

template< class T >
Matrix<T>::value_type Matrix<T>::at(size_type row, size_type col) const{
    return matrix_[row][col];
}

template< class T >
Matrix<T>::size_type Matrix<T>::RowsSize() const{
    return matrix_.size()
}

template< class T >
Matrix<T>::size_type Matrix<T>::ColumnsSize() const{
    return matrix_.begin().size();
}

template< class T >
Matrix<T>::iterator_type Matrix<T>::Begin(){
    return matrix_.begin();
}

template< class T >
Matrix<T>::const_iterator_type Matrix<T>::Begin() const{
    return matrix_.begin();
}

template< class T >
Matrix<T>::iterator_type Matrix<T>::End(){
    return matrix_.end();
}

template< class T >
Matrix<T>::const_iterator_type Matrix<T>::End() const{
    return matrix_.end();
}

template< class T >
Matrix<T>::iterator_type Matrix<T>::Rbegin(){
    return matrix_.rbegin();
}

template< class T >
Matrix<T>::const_iterator_type Matrix<T>::Rbegin() const{
    return matrix_.rbegin();
}

template< class T >
Matrix<T>::iterator_type Matrix<T>::Rend(){
    return matrix_.rend();
}

template< class T >
Matrix<T>::const_iterator_type Matrix<T>::Rend() const{
    return matrix_.rend();
}

template< class T >
bool Matrix<T>::LoadMatrixFromFile(std::string filename){
    if (matrix_.size()){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                    "Current 1 is not emtpy");
        return false;
    }

    std::ifstream file_stream;
    file_stream.open(filename, std::ios_base::in);
    if (!file_stream.is_open()){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                        "Cannot open file " + filename);
        return false;
    }

    int size;
    file_stream >> size;
    if (size <= 0){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                        "Graph size must be positive");
        return false;
    }

    graph_.reserve(size);
    for (int i = 0; i < size; i++){
        elem_of_graph_type row;
        row.reserve(size);
        for (int j = 0; j < size; j++){
            int val;
            if (!(file_stream >> val)){
                PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                                "Invalid file line");
                graph_.clear();
                return false;
            }
            if (val < 0){
                PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                                "Vertex value must be non-negative");
                graph_.clear();
                return false;
            }
            row.push_back(val);
        }
        graph_.push_back(std::move(row));
    }
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();

    return true;
}

}
