#ifndef S21_GRAPH_H
#error 's21_graph_impl.h' is not supposed to be included directly. \
        Include 's21_graph.h' instead.
#endif

namespace s21{

template< class T >
Graph<T>::Graph()
    : is_directed_(0), is_connected_(0), min_spanning_tree_size_(0){ }

template< class T >
Graph<T>::Graph(const graph_type& inp_graph) : parent_type(inp_graph){
    min_spanning_tree_size_ = 0;
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();
}

template< class T >
Graph<T>::Graph(graph_type&& inp_graph) : parent_type(std::move(inp_graph)){
    min_spanning_tree_size_ = 0;
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();
}

template< class T >
Graph<T>::Graph(const graph_type& inp_graph, size_type min_spanning_tree_size)
    : parent_type(inp_graph), min_spanning_tree_size_(min_spanning_tree_size) {
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();
}

template< class T >
Graph<T>::Graph(graph_type&& inp_graph, size_type min_spanning_tree_size)
    : parent_type(std::move(inp_graph)),
        min_spanning_tree_size_(min_spanning_tree_size) {
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();
}

template< class T >
Graph<T>& Graph<T>::operator=(const Graph<T>& other){
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
    parent_type::operator=(other);
    if (!parent_type::matrix_.size()){
        min_spanning_tree_size_ = other.min_spanning_tree_size_;
        is_directed_ = other.is_directed_;
        is_connected_ = other.is_connected_;
    }
    return *this;
}

template< class T >
typename Graph<T>::parent_type::size_type Graph<T>::NodesSize() const{
    return parent_type::RowsSize();
}

template< class T >
typename Graph<T>::parent_type::ize_type Graph<T>::MinSpanningTreeSize() const{
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
bool Graph<T>::LoadFromFile(std::string filename){
    std::ifstream file_stream;
    int size;

    size = parent_type::GeneralFromFileValidation_(filename, file_stream);
    if (size){
        for (int i = 0; i < size; i++){
            row_matrix_type row;
            row.reserve(size);
            for (int j = 0; j < size; j++){
                int val;
                if (!(file_stream >> val)){
                    PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                                    "Invalid file line");
                    parent_type::matrix_.clear();
                    return false;
                }
                if (val < 0){
                    PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__,
                                    "Vertex value must be non-negative");
                    parent_type::matrix_.clear();
                    return false;
                }
                row.push_back(val);
            }
            parent_type::matrix_.push_back(std::move(row));
        }
        is_directed_ = IsDirected_();
        is_connected_ = IsConnected_();
        return true;
    }
    return false;
}

template< class T >
void Graph<T>::ExportGraphToDot(std::string filename){
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
std::string Graph<T>::DotFilename_(std::string& filename){
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
std::string Graph<T>::GraphDotRepresentation_(){
    std::string graph_dot = (is_directed_ ? "digraph" : "graph") +
                            std::string(" graphname {\n");
    std::string dash = (is_directed_ ? " -> " : " -- ");
    std::string startline = "\t";
    std::string endline = ";\n";

    for(size_type i = 0; i < graph_.size(); i++){
        graph_dot += startline + std::to_string(i) + endline;
    }

    for(size_type row = 0; row < graph_.size(); row++){
        for(size_type col = 0; col < graph_.size(); col++){
            if (graph_[row][col] > 0){
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

}

template< class type >
std::ostream& operator<<(std::ostream& out, const s21::Graph<type>& graph){
    return out
            << dynamic_cast<s21::Matrix<type>>(graph)
            << std::endl
            << "IsDirected: " << graph.IsDirected() << std::endl
            << "IsConnected: " << graph.IsConnected() << std::endl
            << "Min spanning tree size: " << graph.MinSpanningTreeSize();
}
