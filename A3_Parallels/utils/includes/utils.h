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

using row_matrix_type               = std::vector<int>;
using matrix_type                   = std::vector<row_matrix_type>;
using matrix_unique_ptr             = std::unique_ptr<matrix_type>; // DELETEME IF I WILL NOT BE USED
using matrix_reference              = typename matrix_type::reference; // DELETEME IF I WILL NOT BE USED
using matrix_const_reference        = typename matrix_type::const_reference; // DELETEME IF I WILL NOT BE USED
using matrix_iterator_type          = typename matrix_type::iterator; // DELETEME IF I WILL NOT BE USED
using matrix_const_iterator_type    = typename matrix_type::const_iterator; // DELETEME IF I WILL NOT BE USED


const std::string INAPPROPRIATE_GRAPH_MSG = "It is impossible to solve "
                            "travelling salesman problem with current graph";
const std::string DEFAULT_DOT_NAME = "graph_default.dot";
const fs::path ROOT_DIR = fs::current_path();
const fs::path GRAPHS_PATH = "materials/graphs";
const fs::path DOTS_PATH = "materials/dot_representations";

struct TsmResult {
    std::vector<int> vertices; // an array with the route
    double distance;  // the length of this route
};

struct SleResult {
    std::vector<double> equation_roots;
};

/**
 * Print error to std::cerr like: [filename]: [funcname]: [line]: [msg]
 */
void PrintError(const std::string& filename,
        const std::string& funcname, int line, const std::string& msg);

/**
 * Set permissions READ-ONLY for [filepath]
 */
void ReadOnlyPermissions(std::string& filepath);

}

std::ostream& operator<<(std::ostream& out, const s21::TsmResult& tsm_result);
