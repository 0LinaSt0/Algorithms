#include "../includes/cli.hpp"

namespace s21{

const std::string CLI::GREEN_COLOR_ = "\033[0;32m";
const std::string CLI::CYAN_COLOR_ = "\033[1;36m";
const std::string CLI::BLUE_COLOR_ = "\033[0;34m";
const std::string CLI::DEFAULT_COLOR_ = "\033[0m";
const std::string CLI::SN_PROMT_COLOR_ = CLI::GREEN_COLOR_;
const std::string CLI::USER_PROMT_COLOR_ = CLI::GREEN_COLOR_;
const std::string CLI::MSG_COLOR_ = CLI::CYAN_COLOR_;
const std::string CLI::IDX_COLOR_ = CLI::CYAN_COLOR_;
const std::string CLI::SN_PROMT_ = CLI::SN_PROMT_COLOR_ +
                                        "SN: " +
                                        CLI::DEFAULT_COLOR_;
const std::string CLI::USER_PROMT_ = CLI::USER_PROMT_COLOR_ +
                                        "> " +
                                        CLI::DEFAULT_COLOR_;
const std::string CLI::SEPARATOR_ = CLI::SN_PROMT_COLOR_ +
                                    "><><><><><><><><><><><><><><><><><><><><" +
                                    CLI::DEFAULT_COLOR_;

void CLI::run(){
    if (!LoadGraphFromFile_()) return;
    while (true){
        PrintMsg_("Available options. Please, select one");
        PrintMenu_();
        
        int option = ReadInput_();
        if (option == EXIT_INPUT_VALUE_ || std::cin.eof()){
            PrintMsg_("Exit");
            break;
        } else if (option == CLS_INPUT_VALUE_){
            system("clear");
        } else if (option < 1 || option > MENU_OPTIONS_COUNT_){
            PrintMsg_("Bad input. Please, enther a number");
        } else {
            (this->*(methods_[--option]))();
        }
    }
}

void CLI::PrintMenu_() const{
    for (int i = 0; i < MENU_OPTIONS_COUNT_; i++){
        const std::string& str = menu_msg_[i];
        std::cout
            << IDX_COLOR_
            << i + 1
            << ": "
            << DEFAULT_COLOR_
            << str
            << std::endl;
    }
}

void CLI::PrintMsg_(const std::string& msg) const{
    std::cout 
        << std::endl 
        << SEPARATOR_
        << std::endl
        << std::endl
        << SN_PROMT_ 
        << MSG_COLOR_
        << msg 
        << DEFAULT_COLOR_
        << std::endl;
}

int CLI::ReadInput_() const{
    std::string line;
    std::cout << USER_PROMT_;
    std::getline(std::cin, line);
    TrimLine_(line);
    std::transform(line.begin(), line.end(), line.begin(),
        [](unsigned char c){
            return std::tolower(c);
        }
    );

    if (line == "clear") return CLS_INPUT_VALUE_;
    else if (line == "exit") return EXIT_INPUT_VALUE_;
    try { return std::stoi(line); }
    catch (std::exception&){ return BAD_INPUT_VALUE_; }
}

bool CLI::LoadGraphFromFile_(){
    PrintMsg_("Enter graph filepath");
    std::string input_line;
    std::cout << USER_PROMT_;
    std::getline(std::cin, input_line);
    TrimLine_(input_line);

    graph_ = std::unique_ptr<Graph>(new Graph());
    return graph_->LoadGraphFromFile(input_line);
}

void CLI::BreadthFirstSearch_(){
    PrintMsg_("Enter number of start vertex");
    int start = ReadInput_();
    if (start == BAD_INPUT_VALUE_){
        PrintMsg_("Invalid start vertex value");
        return;
    }

    std::vector<int> res = graph_algorithms_.BreadthFirstSearch(
        *graph_.get(),
        start
    );
    if (!res.size()) return;

    std::cout << "Graph traversal in breadth:" << std::endl;
    for (size_t i = 0; i < res.size(); i++){
        std::cout << res[i];
        if (i + 1 != res.size()) std::cout << "->";
    }
    std::cout << std::endl;
}

void CLI::DepthFirstSearch_(){
    PrintMsg_("Enter number of start vertex");
    int start = ReadInput_();
    if (start == BAD_INPUT_VALUE_){
        PrintMsg_("Invalid start vertex value");
        return;
    }

    std::vector<int> res = graph_algorithms_.DepthFirstSearch(
        *graph_.get(),
        start
    );
    if (!res.size()) return;

    std::cout << "Graph traversal in depth:" << std::endl;
    for (size_t i = 0; i < res.size(); i++){
        std::cout << res[i];
        if (i + 1 != res.size()) std::cout << "->";
    }
    std::cout << std::endl;
}

void CLI::GetShortestPathBetweenVertices_(){
    PrintMsg_("Enter numbers of first and second verteces");
    int first = ReadInput_();
    int second = ReadInput_();
    if (first == BAD_INPUT_VALUE_ || second == BAD_INPUT_VALUE_){
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
    Timer timer;
    timer.Start();
    TsmResult tsmResult = graph_algorithms_.SolveTravelingSalesmanProblem(
                                                                *graph_.get()
                                                                );
    timer.End();

    std::cout
        << "Solving the salesman problem (ant algorithm): "
        << std::endl
        << tsmResult
        << std::endl
        << "Duration: "
        << timer.GetDuration()
        << " ms"
        << std::endl;
}

void CLI::STSPBranchBoundMethodAlgorithm_(){
    Timer timer;
    timer.Start();
    TsmResult tsmResult = graph_algorithms_.STSPBranchBoundMethodAlgorithm(
                                                                *graph_.get()
                                                                );
    timer.End();

    std::cout
        << "Solving the salesman problem (branch and bound method): "
        << std::endl
        << tsmResult
        << std::endl
        << "Duration: "
        << timer.GetDuration()
        << " ms"
        << std::endl;
}

void CLI::ExhaustiveSearch_(){
    Timer timer;
    timer.Start();
    TsmResult tsmResult = graph_algorithms_.ExhaustiveSearch(*graph_.get());
    timer.End();

    std::cout
        << "Solving the salesman problem (exhaustive search): "
        << std::endl
        << tsmResult
        << std::endl
        << "Duration: "
        << timer.GetDuration()
        << " ms"
        << std::endl;
}

void CLI::SolveTravelingSalesmanProblemWithTimeComparasion_(){
    Timer timer;

    PrintMsg_("Enter count of iterations: ");
    int N = ReadInput_();
    if (N == BAD_INPUT_VALUE_) {
        PRINT_ERROR(
            __FILE__,
            __FUNCTION__,
            __LINE__,
            "Invalid input value"
        );
        return;
    }

    for (int i = 0; i < 3; i++){
        long time_sum = 0;

        for (int iter = 0; iter < N; iter++){
            timer.Start();
            (graph_algorithms_.*tsp_methods_[i])(*graph_);
            timer.End();
            time_sum += timer.GetDuration();
        }

        std::cout
            << menu_msg_[i + 5]
            << ": "
            << std::to_string(time_sum)
            << " ms"
            << std::endl;
    }
}

void CLI::TrimLine_(std::string& line) const{
    auto lambda = [](char c){ return !std::isspace(c); };
    std::string::const_iterator iter = std::find_if(
        line.begin(),
        line.end(),
        lambda
    );
    if (iter != line.end()) line.erase(line.begin(), iter);

    std::string::const_reverse_iterator riter = std::find_if(
        line.rbegin(),
        line.rend(),
        lambda
    );
    if (riter != line.rend()) {
        std::string::const_iterator rriter(riter.base());
        line.erase(rriter, line.end());
    }
}

}
