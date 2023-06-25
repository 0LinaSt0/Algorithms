#include <iostream>
#include <array>

#include "graph/includes/graph.hpp"
#include "graph/includes/graphAlgorithms.hpp"

std::string directory_path = "materials/graphs/";
std::array<std::string, 14> filenames{
    directory_path + "00_empty_matrix",
    directory_path + "01_with_solution",
    directory_path + "02_without_solution",
    directory_path + "03_without_solution",
    directory_path + "04_with_several_solutions_loop",
    directory_path + "05_with_solutiom_loop",
    directory_path + "06_with_solutiom_loop",
    directory_path + "07_connected_without_solution",
    directory_path + "08_connected_loop",
    directory_path + "14_with_some_solutions",
    directory_path + "15_ex",
    directory_path + "16_ex_20",
    directory_path + "17_ex_default",
    directory_path + "18_eight_vertices"
};

void print_result(const std::string& method, const s21::TsmResult& result){
    std::cout << std::endl << "~~~> " << method << ": " << std::endl;
    std::cout << "\t- result way:\t";
    for (auto& elem : result.vertices){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\t- result length:\t" << result.distance << std::endl;
    std::cout << "\t\t ~~~~~~~~~~~~~~~~ " << std::endl;
}

void print_graph(s21::Graph& graph){
    std::cout << "~~~> GRAPH_MATRIX:" << std::endl;
    graph.tmp_print_graph_DELETEME();
    std::cout << "- Is directed: " << graph.IsDirected() << std::endl;
    std::cout << "- Is connected: " << graph.IsConnected() << std::endl;
}

void test_STSP_ants(s21::Graph& graph, s21::GraphAlgorithms& algs){
    s21::TsmResult result = algs.SolveTravelingSalesmanProblem(graph);

    print_result("ANT RESULT", result);
}

void test_STSP_BBM(s21::Graph& graph, s21::GraphAlgorithms& algs){
    s21::TsmResult result = algs.STSPBranchBoundMethodAlgorithm(graph);

    print_result("BBM RESULT", result);
}

void test_STSP_Exhaustive(s21::Graph& graph, s21::GraphAlgorithms& algs){
    s21::TsmResult result = algs.ExhaustiveSearch(graph);

    print_result("Exhaustive RESULT", result);
}

void graph_convert(s21::Graph& graph, std::string& filename){
    std::string tmp_string;
    std::string dot_filename;

    tmp_string = filename.substr(filename.find("/") + 1);
    tmp_string = tmp_string.substr(tmp_string.find("/") + 1);
    tmp_string = tmp_string.substr(0, tmp_string.find("_") + 1);
    dot_filename = tmp_string + "schema.dot";

    graph.LoadGraphFromFile(filename);
    graph.ExportGraphToDot(dot_filename);
    print_graph(graph);
}

void test(std::string& filename){
    s21::Graph graph;
    s21::GraphAlgorithms algs;

    graph_convert(graph, filename);

    std::cout << std::endl;
    test_STSP_ants(graph, algs);
    std::cout << std::endl;
    test_STSP_BBM(graph, algs);
    std::cout << std::endl;
    test_STSP_Exhaustive(graph, algs);
}

void dfs_test(){
    std::string way = "tests/materials/graph/valid/5";
    std::vector<int> tmp;

    s21::Graph graph;
    s21::GraphAlgorithms algs;

    graph_convert(graph, way);

    std::cout << std::endl;
    tmp = algs.DepthFirstSearch(graph, 1);
    for (auto& elem : tmp){
        std::cout << elem << "  ";
    }
    std::cout << std::endl;
}

int main(void){
    // dfs_test();
    // std::cout << "\033[0;32m" << "~~~~~~~~~~~" << "\033[0m" << std::endl;
    // test(filenames[0]);
    // std::cout << "\033[0;32m" << "~~~~~~~~~~~" << "\033[0m" << std::endl;
    // test(filenames[1]);
    // std::cout << "\033[0;32m" << "~~~~~~~~~~~" << "\033[0m" << std::endl;
    // test(filenames[2]);
    // std::cout << "\033[0;32m" << "~~~~~~~~~~~" << "\033[0m" << std::endl;
    // test(filenames[3]);
    // std::cout << "\033[0;32m" << "~~~~~~~~~~~" << "\033[0m" << std::endl;
    // test(filenames[4]);
    // std::cout << "\033[0;32m" << "~~~~~~~~~~~" << "\033[0m" << std::endl;
    // test(filenames[5]);
    // std::cout << "\033[0;32m" << "~~~~~~~~~~~" << "\033[0m" << std::endl;
    // test(filenames[6]);
    // std::cout << "\033[0;32m" << "~~~~~~~~~~~" << "\033[0m" << std::endl;
    // test(filenames[7]);
    // std::cout << "\033[0;32m" << "~~~~~~~~~~~" << "\033[0m" << std::endl;
    // test(filenames[8]);
    // std::cout << "\033[0;32m" << "~~~~~~~~~~~" << "\033[0m" << std::endl;
    // test(filenames[9]);
    // std::cout << "\033[0;32m" << "~~~~~~~~~~~" << "\033[0m" << std::endl;
    // test(filenames[10]);
    // std::cout << "\033[0;32m" << "~~~~~~~~~~~" << "\033[0m" << std::endl;
    // test(filenames[11]); // long one
    // std::cout << "\033[0;32m" << "~~~~~~~~~~~" << "\033[0m" << std::endl;
    // test(filenames[12]);
    std::cout << "\033[0;32m" << "~~~~~~~~~~~" << "\033[0m" << std::endl;
    test(filenames[13]);
}