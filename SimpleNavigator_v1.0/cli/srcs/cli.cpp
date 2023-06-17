#include "../includes/cli.hpp"

namespace s21{

void CLI::run(){
    // Load graph file
    PrintMsg_("Enter graph filepath");
    std::string input_line;
    std::getline(std::cin, input_line);
    if (!LoadGraphFromFile_(input_line)) return;

    while (true){
        PrintMsg_("Available options. Please, select one");
        PrintMenu_();
        
        int option = ReadInt_();
        if (option < 1 || option > MENU_OPTIONS_COUNT){
            PrintMsg_("Bad input. Please, enther a number");
        } else {
            (this->*(methods_[--option]))();
        }
    }
}

void CLI::PrintMenu_() const{
    for (const std::string& str : menu_msg_){
        std::cout << str << std::endl;
    }
}

void CLI::PrintMsg_(const std::string& msg) const{
    std::cout << std::endl << "SN: " << msg << std::endl;
}

int CLI::ReadInt_() const{
    std::string line;
    std::getline(std::cin, line);
    try {
        return std::stoi(line);
    } catch (std::exception&){
        return BAD_INPUT_VALUE;
    }
}

bool CLI::LoadGraphFromFile_(const std::string& filepath){
    graph_ = std::unique_ptr<Graph>(new Graph());
    return graph_->LoadGraphFromFile(filepath);
}

void CLI::BreadthFirstSearch_(){
    PrintMsg_("Enter number of start vertex");
    int start = ReadInt_();
    if (start == BAD_INPUT_VALUE){
        PrintMsg_("Invalid start vertex value");
        return;
    }

    std::vector<int> res = graph_algorithms_.BreadthFirstSearch(
        *graph_.get(),
        start
    );

    std::cout << "Graph traversal in breadth:" << std::endl;
    for (size_t i = 0; i < res.size(); i++){
        std::cout << res[i];
        if (i + 1 != res.size()) std::cout << "->";
    }
    std::cout << std::endl;
}

void CLI::DepthFirstSearch_(){
    PrintMsg_("Enter number of start vertex");
    int start = ReadInt_();
    if (start == BAD_INPUT_VALUE){
        PrintMsg_("Invalid start vertex value");
        return;
    }

    std::vector<int> res = graph_algorithms_.DepthFirstSearch(
        *graph_.get(),
        start
    );

    std::cout << "Graph traversal in depth:" << std::endl;
    for (size_t i = 0; i < res.size(); i++){
        std::cout << res[i];
        if (i + 1 != res.size()) std::cout << "->";
    }
    std::cout << std::endl;
}

void CLI::GetShortestPathBetweenVertices_(){
    PrintMsg_("Enter numbers of first and second verteces");
    int first = ReadInt_();
    int second = ReadInt_();
    if (first == BAD_INPUT_VALUE || second == BAD_INPUT_VALUE){
        PrintMsg_("Invalid input");
        return;
    }

    std::cout
        << "Searching for the shortest path between any two vertices: "
        << graph_algorithms_.GetShortestPathBetweenVertices(
                                *graph_.get(),
                                first,
                                second
                            )
        << std::endl;
}

void CLI::GetShortestPathsBetweenAllVertices_(){
    std::cout
        << "Searching for the shortest paths between all pairs of vertices: "
        << std::endl
        << graph_algorithms_.GetShortestPathsBetweenAllVertices(
                                *graph_.get()
                            )
        << std::endl;
}

void CLI::GetLeastSpanningTree_(){
    std::cout
        << "Searching for the minimal spanning tree: "
        << std::endl
        << graph_algorithms_.GetLeastSpanningTree(*graph_.get())
        << std::endl;
}

void CLI::SolveTravelingSalesmanProblem_(){
    std::cout
        << "Solving the salesman problem (ant algorithm): "
        << std::endl
        << graph_algorithms_.SolveTravelingSalesmanProblem(*graph_.get())
        << std::endl;
}

void CLI::STSPBranchBoundMethodAlgorithm_(){
    std::cout
        << "Solving the salesman problem (branch and bound method): "
        << std::endl
        << graph_algorithms_.STSPBranchBoundMethodAlgorithm(*graph_.get())
        << std::endl;
}

void CLI::ExhaustiveSearch_(){
    std::cout
        << "Solving the salesman problem (exhaustive search): "
        << std::endl
        << graph_algorithms_.ExhaustiveSearch(*graph_.get())
        << std::endl;
}

}
