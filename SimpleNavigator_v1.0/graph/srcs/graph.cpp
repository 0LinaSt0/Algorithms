#include "../includes/graph.hpp"

namespace s21{

Graph::Graph() : is_directed_(0){ }

void Graph::ExportGraphToDot(std::string filename){
    fs::path result_path = std::move(createFileIfNotExist_(filename));
    std::ofstream dot_file(result_path.native());
    std::string dot_graph = graphDotRepresentation_();

    dot_file << dot_graph << std::endl;
}

fs::path Graph::createFileIfNotExist_(std::string& filename){
    fs::path result_path = ROOT_DIR / DOTS_PATH / dotFilename_(filename);

    if(!fs::exists(result_path)){
        fs::create_directories(result_path);
    }

    return result_path;
}

std::string Graph::dotFilename_(std::string& filename){

}

std::string Graph::graphDotRepresentation_(){

}

}
