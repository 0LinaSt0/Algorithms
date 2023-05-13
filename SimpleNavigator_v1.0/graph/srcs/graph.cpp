#include "../includes/graph.hpp"

namespace s21{

Graph::Graph() : is_directed_(0){ }

void Graph::ExportGraphToDot(std::string filename){
    try{
        fs::path result_path = ROOT_DIR / DOTS_PATH / dotFilename_(filename);
        std::ofstream dot_file(result_path.native());
        std::string dot_graph = graphDotRepresentation_();
        
        dot_file << dot_graph << std::endl;
    }
    catch(...){
        ERROR(__FILE__, __FUNCTION__, __LINE__, "Invalid file");
    }

}

std::string Graph::dotFilename_(std::string& filename){
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

std::string Graph::graphDotRepresentation_(){
    
}

}
