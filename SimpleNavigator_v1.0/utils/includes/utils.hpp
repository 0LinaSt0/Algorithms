#pragma once

#include <filesystem>
#include <iostream>
#include <vector>
#include <string>

#define PRINT_ERROR(file, func, line, msg)( \
    (s21::PrintError((file), (func), (line), (msg))), \
    (void)0 \
)

#define READ_ONLY(file)( \
    (s21::ReadOnlyPermissions((file))) \
    (void)0 \
)


namespace fs = std::filesystem;

namespace s21{

using coordinate                    = std::array<int, 2>;
using coordinates                   = std::vector<coordinate>;
using row_matrix_type               = std::vector<int>;
using matrix_type                   = std::vector<row_matrix_type>;
using matrix_unique_ptr             = std::unique_ptr<matrix_type>;
using matrix_reference              = typename matrix_type::reference;
using matrix_const_reference        = typename matrix_type::const_reference;
using matrix_iterator_type          = typename matrix_type::iterator;
using matrix_const_iterator_type    = typename matrix_type::const_iterator;

// typedefs for BranchBoundMethodAlgorithm implementation
using coordinates_iter              = typename coordinates::iterator;
using coorsinate_cell               = std::pair<coordinate, int>;
using row_matrix_pair_type          = std::vector<coorsinate_cell>;
using matrix_pair_type              = std::vector<row_matrix_pair_type>;
using matrix_pair_unique_ptr        = std::unique_ptr<matrix_pair_type>;


const std::string INAPPROPRIATE_GRAPH_MSG = "It is impossible to solve "
                            "travelling salesman problem with current graph";
const std::string DEFAULT_DOT_NAME = "graph_default.dot";
const fs::path ROOT_DIR = fs::current_path();
const fs::path GRAPHS_PATH = "materials/graphs";
const fs::path DOTS_PATH = "materials/dot_representations";

const int TSM_ALPHA = 2; // parameter depending on the number of pheromones [0;2]
const int TSM_BETA = 1; // parameter depending on the length [0;2]
const double TSM_PYRA = 0.1; // evaporation rate constant of pheromones [0;1]

const int TSM_SAME_ROAD_LIMIT = 10;
const int TSM_PASSES_NUMBER_LIMIT = 100;

struct TsmResult {
    std::vector<int> vertices; // an array with the route
    double distance;  // the length of this route

    void tmp_print_DELETEME(void){
        std::cout << "TsmResult::vertices" << std::endl;
        for (auto& elem : vertices){
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
};

// Print error like "filename: funcname: line: msg" to std::cerr
void PrintError(const std::string& filename,
        const std::string& funcname, int line, const std::string& msg);

// Set permissions READ-ONLY for "filepath"
void ReadOnlyPermissions(std::string& filepath);

}

std::ostream& operator<<(std::ostream& out, const s21::TsmResult& tsm_result);
