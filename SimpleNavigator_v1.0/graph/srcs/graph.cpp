#include "../includes/graph.hpp"

namespace s21{

Graph::Graph() : is_directed_(0){ }

Graph::Graph(const graph_type& inp_graph) : graph_(inp_graph){ 
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();
}

Graph::Graph(graph_type&& inp_graph) : graph_(std::move(inp_graph)){
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();
}

Graph::Graph(const graph_type& inp_graph, size_type min_spanning_tree_size)
    : graph_(inp_graph), min_spanning_tree_size_(min_spanning_tree_size) {
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();
}

Graph::Graph(graph_type&& inp_graph, size_type min_spanning_tree_size)
    : graph_(std::move(inp_graph)),
        min_spanning_tree_size_(min_spanning_tree_size) {
    is_directed_ = IsDirected_();
    is_connected_ = IsConnected_();
}

Graph& Graph::operator=(const Graph& other){
    if (graph_.size()) PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, 
                                    "Graph is not empty");
    else {
        graph_ = other.graph_;
        min_spanning_tree_size_ = other.min_spanning_tree_size_;
        is_directed_ = other.is_directed_;
        is_connected_ = other.is_connected_;
    }
    return *this;
}

Graph& Graph::operator=(Graph&& other){
    if (graph_.size()) PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, 
                                    "Graph is not empty");
    else {
        graph_ = std::move(other.graph_);
        min_spanning_tree_size_ = other.min_spanning_tree_size_;
        is_directed_ = other.is_directed_;
        is_connected_ = other.is_connected_;
    }
    return *this;
}

Graph::reference Graph::operator[](Graph::size_type pos){
    return graph_.operator[](pos);
}

Graph::const_reference Graph::operator[](Graph::size_type pos) const{
    return graph_.operator[](pos);
}

Graph::elem_of_graph_type::value_type Graph::at(size_type row, size_type col){
    return graph_[row][col];
}

Graph::elem_of_graph_type::value_type Graph::at(size_type row, 
                                                size_type col) const{
    return graph_[row][col];
}

std::size_t Graph::Size() const{
    return graph_.size();
}

Graph::size_type Graph::MinSpanningTreeSize() const{
    return min_spanning_tree_size_;
}

Graph::iterator_type Graph::Begin(){
    return graph_.begin();
}

Graph::iterator_type Graph::End(){
    return graph_.end();
}

Graph::const_iterator_type Graph::Begin() const{
    return graph_.begin();
}

Graph::const_iterator_type Graph::End() const{
    return graph_.end();
}

bool Graph::IsDirected() const{
    return is_directed_;
}

bool Graph::IsConnected() const{
    return is_connected_;
}

bool Graph::LoadGraphFromFile(std::string filename){
    if (graph_.size()){
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
    is_connected_ = IsConnected_();

    return true;
}

bool Graph::IsDirected_() const{
    for (size_t x = 0; x < graph_.size(); x++){
    for (size_t y = 0; y < graph_.size(); y++){
        if (graph_[x][y] != graph_[y][x]) return true;
    }
    }

    return false;
}

bool Graph::IsConnected_() const{
    for (size_t x = 0; x < graph_.size(); x++){
        for (size_t y = 0; y < graph_.size(); y++){
            if (graph_[x][y] != 0) break;
            if (y + 1 == graph_.size()) return false;
        }
        for (size_t y = 0; y < graph_.size(); y++){
            if (graph_[y][x] != 0) break;
            if (y + 1 == graph_.size()) return false;
        }
    }

    return true;
}

void Graph::ExportGraphToDot(std::string filename){
    try{
        std::string&& file = DotFilename_(filename);
        fs::path result_path = ROOT_DIR / DOTS_PATH / file;
        std::ofstream dot_file(result_path.native());

        if (!dot_file.is_open()){
            throw std::invalid_argument(result_path);
        }

        std::string dot_graph = GraphDotRepresentation_();

        dot_file << dot_graph << std::endl;
    }
    catch(const std::invalid_argument& e){
        std::string error = "Permission denied (filename is reserved): ";
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, error + e.what());
    }
    catch(...){
        PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, "Invalid file");
    }
}

std::string Graph::DotFilename_(std::string& filename){
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

std::string Graph::GraphDotRepresentation_(){
    std::string graph_dot = "1 graphname {\n";
    std::string dash = (is_directed_ ? " -> " : " -- ");
    std::string startline = "\t";
    std::string endline = ";\n";

    for(graph_type::size_type i = 0; i < graph_.size(); i++){
        graph_dot += startline + std::to_string(i) + endline;
    }

    for(graph_type::size_type row = 0; row < graph_.size(); row++){
        for(graph_type::size_type col = 0; col < graph_.size(); col++){
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

void Graph::tmp_write_to_graph_DELETEME(int elem_number){
    auto gen = std::bind(
        std::uniform_int_distribution<>(0,1),
        std::default_random_engine()
    );

    for (auto i = 0; i < elem_number; i++){
        std::vector<int> inside;
        for (auto j = 0; j < elem_number; j++){
            inside.push_back(bool(gen()));
        }
        graph_.push_back(std::move(inside));
    }
}

void Graph::tmp_print_graph_DELETEME(void){
    for(graph_type::size_type i = 0; i < graph_.size(); i++){
        for(graph_type::size_type j = 0; j < graph_.size(); j++){
            std::cout << graph_[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

}
