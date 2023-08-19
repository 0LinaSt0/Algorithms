#ifndef S21_GRAPH_H
#error 's21_graph_impl.h' is not supposed to be included directly. \
        Include 's21_graph.h' instead.
#endif

namespace s21{

template< class T >
Graph<T>::Graph(const Matrix<T>& inp_mtrx) : parent_type(inp_mtrx) {
    min_spanning_tree_size_ = 0;
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();
}

template< class T >
Graph<T>::Graph(Matrix<T>&& inp_mtrx) : parent_type(std::move(inp_mtrx)) {
    min_spanning_tree_size_ = 0;
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();
}

template< class T >
Graph<T>::Graph(const matrix_type& inp_graph) : parent_type(inp_graph){
    min_spanning_tree_size_ = 0;
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();
}

template< class T >
Graph<T>::Graph(matrix_type&& inp_graph) : parent_type(std::move(inp_graph)){
    min_spanning_tree_size_ = 0;
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();
}

template< class T >
Graph<T>::Graph(const matrix_type& inp_graph, size_type min_spanning_tree_size)
    : parent_type(inp_graph), min_spanning_tree_size_(min_spanning_tree_size) {
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();
}

template< class T >
Graph<T>::Graph(matrix_type&& inp_graph, size_type min_spanning_tree_size)
    : parent_type(std::move(inp_graph)),
        min_spanning_tree_size_(min_spanning_tree_size) {
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();
}

template< class T >
Graph<T>& Graph<T>::operator=(const Graph<T>& other){
    if (this == &other) return *this;
    parent_type::operator=(other);
    if (!parent_type::matrix_.size()){
        min_spanning_tree_size_ = other.min_spanning_tree_size_;
        is_directed_ = other.is_directed_;
        is_connected_ = other.is_connected_;
    }
    return *this;
}

template< class T >
Graph<T>& Graph<T>::operator=(Graph<T>&& other){
    if (this == &other) return *this;
    parent_type::operator=(other);
    if (!parent_type::matrix_.size()){
        min_spanning_tree_size_ = other.min_spanning_tree_size_;
        is_directed_ = other.is_directed_;
        is_connected_ = other.is_connected_;
    }
    return *this;
}

template< class T >
typename Graph<T>::size_type Graph<T>::NodesSize() const{
    return parent_type::RowsSize();
}

template< class T >
typename Graph<T>::size_type Graph<T>::MinSpanningTreeSize() const{
    return min_spanning_tree_size_;
}

template< class T >
bool Graph<T>::IsDirected() const{
    return is_directed_;
}

template< class T >
bool Graph<T>::IsConnected() const{
    return is_connected_;
}

template< class T >
Graph<T> Graph<T>::LoadFromFile(const std::string& filename){
    // std::ifstream file_stream;
    int rows_count, columns_count;

    // Open file
    std::ifstream input_file_stream;
    input_file_stream.open(filename);
    if (!input_file_stream.is_open()){
        throw GraphException("Cannot open file: " + filename);
    }
    // Read rows and columns count
    input_file_stream >> rows_count;
    input_file_stream >> columns_count;
    if (rows_count < 1 || columns_count < 1 || rows_count != columns_count){
        throw GraphException("Columns or rows count cannot be non-positive");
    }

    return Graph<T>(Matrix<T>::LoadMatrixFromFile_(
                        input_file_stream,
                        rows_count,
                        columns_count
                    ));
}

template< class T >
void Graph<T>::ExportGraphToDot(
    const Graph<T>,
    const std::string& filename
){
    try{
        std::string&& file = DotFilename_(filename);
        fs::path result_path = ROOT_DIR / DOTS_PATH / file;
        std::ofstream dot_file(result_path.native());

        if (!dot_file.is_open()){
            throw std::invalid_argument(result_path);
        }

        std::string dot_graph = GraphDotRepresentation_();

        dot_file << dot_graph << std::endl;
    } catch(const std::invalid_argument& e){
        std::string error = "Permission denied (filename is reserved): ";
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, error + e.what());
    } catch(...){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, "Invalid file");
    }
}

template< class T >
bool Graph<T>::IsDirected_() const{
    for (size_t x = 0; x < parent_type::matrix_.size(); x++){
    for (size_t y = 0; y < parent_type::matrix_.size(); y++){
        if (parent_type::matrix_[x][y] != parent_type::matrix_[y][x]){
            return true;
        }
    }
    }
    return false;
}

template< class T >
bool Graph<T>::IsConnected_() const{
    for (size_t x = 0; x < parent_type::matrix_.size(); x++){
        for (size_t y = 0; y < parent_type::matrix_.size(); y++){
            if (parent_type::matrix_[x][y] != 0) break;
            if (y + 1 == parent_type::matrix_.size()) return false;
        }
        for (size_t y = 0; y < parent_type::matrix_.size(); y++){
            if (parent_type::matrix_[y][x] != 0) break;
            if (y + 1 == parent_type::matrix_.size()) return false;
        }
    }

    return true;
}

template< class T >
std::string Graph<T>::DotFilename_(const std::string& filename){
    if (filename.empty()){
        return DEFAULT_DOT_NAME;
    }

    const std::regex rgx(".*(\\.dot|\\.gv)$");
    std::smatch result;

    if (std::regex_match(filename, result, rgx)){
        return filename;
    }
    return filename + ".dot";
}

template< class T >
std::string Graph<T>::GraphDotRepresentation_(const Graph<T> graph){
    std::string graph_dot = (graph.is_directed_ ? "digraph" : "graph") +
                            std::string(" graphname {\n");
    std::string dash = (graph.is_directed_ ? " -> " : " -- ");
    std::string startline = "\t";
    std::string endline = ";\n";

    for(size_type i = 0; i < ::s21::Matrix<T>::matrix_.size(); i++){
        graph_dot += startline + std::to_string(i) + endline;
    }

    for(size_type row = 0; row < ::s21::Matrix<T>::matrix_.size(); row++){
        for(size_type col = 0; col < ::s21::Matrix<T>::matrix_.size(); col++){
            if (::s21::Matrix<T>::matrix_[row][col] > 0){
                graph_dot += startline +
                            std::to_string(row) +
                            dash +
                            std::to_string(col) +
                            endline;
            }
        }
    }

    graph_dot += "}";
    return graph_dot;
}

template< class T >
Graph<T>::GraphException::GraphException(const std::string& msg)
    : ::s21::Exception(msg) {

}

template< class T >
std::string Graph<T>::GraphException::GetMessage() const{
    return ::s21::Exception::msg_;
}

} // namespace s21
