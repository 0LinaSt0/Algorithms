#include "../includes/graph.hpp"

namespace s21{

Graph::Graph() : is_directed_(0){ }

Graph::Graph(const graph_type& inp_graph) : graph_(inp_graph){ }

Graph::Graph(graph_type&& inp_graph) : graph_(inp_graph){ }

Graph::reference Graph::operator[](Graph::size_type pos){
    return graph_.operator[](pos);
}

Graph::const_reference Graph::operator[](Graph::size_type pos) const{
    return graph_.operator[](pos);
}

std::size_t Graph::Size(){
    return graph_.size();
}

// void Graph::ExportGraphToDot(std::string filename){
//     try{
//         std::string file = std::move(DotFilename_(filename));
//         fs::path result_path = ROOT_DIR / DOTS_PATH / file;
//         std::ofstream dot_file(result_path.native());

//         if (!dot_file.is_open()){
//             throw std::invalid_argument(result_path);
//         }

//         std::string dot_graph = std::move(GraphDotRepresentation_());

//         dot_file << dot_graph << std::endl;
//     }
//     catch(const std::invalid_argument& e){
//         std::string error = "Permission denied (filename is reserved): ";
//         PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, error + e.what());
//     }
//     catch(...){
//         PRINT_ERROR(__FILE__, __FUNCTION__, __LINE__, "Invalid file");
//     }
// }

// std::string Graph::DotFilename_(std::string& filename){
//     if (filename.empty()){
//         return DEFAULT_DOT_NAME;
//     }

//     const std::regex rgx(".*(\\.dot|\\.gv)$");
//     std::smatch result;

//     if (std::regex_match(filename, result, rgx)){
//         return filename;
//     }
//     return filename + ".dot";
// }

// std::string Graph::GraphDotRepresentation_(){
//     std::string graph_dot = "graph graphname {\n";
//     std::string dash = (is_directed_ ? " -> " : " -- ");
//     std::string startline = "\t";
//     std::string endline = ";\n";

//     for(graph_type::size_type i = 0; i < graph_.size(); i++){
//         graph_dot += startline + std::to_string(i) + endline;
//     }

//     for(graph_type::size_type row = 0; row < graph_.size(); row++){
//         for(graph_type::size_type col = 0; col < graph_.size(); col++){
//             if (graph_[row][col] > 0){
//                 graph_dot += startline +
//                             std::to_string(row) +
//                             dash +
//                             std::to_string(col) +
//                             endline;
//             }
//         }
//     }

//     graph_dot += "}";
//     return graph_dot;
// }

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
