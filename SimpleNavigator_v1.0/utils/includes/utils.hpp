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

using coordinate            = std::array<int, 2>;
using coordinates           = std::vector<coordinates>;
using matrix_type           = std::vector<std::vector<int>>;
using matrix_unique_ptr     = std::unique_ptr<matrix_type>;


const std::string DEFAULT_DOT_NAME = "graph_default.dot";
const fs::path ROOT_DIR = fs::current_path();
const fs::path GRAPHS_PATH = "materials/graphs";
const fs::path DOTS_PATH = "materials/dot_representations";

const int TSM_ALPHA = 1; // parameter depending on the number of pheromones [0;2]
const int TSM_BETA = 2; // parameter depending on the length [0;2]
const double TSM_PYRA = 0.1; // evaporation rate constant of pheromones [0;1]

const int TSM_SAME_ROAD_LIMIT = 10;

struct TsmResult {
    std::vector<int> vertices; // an array with the route
    double distance;  // the length of this route
};

// Print error like "filename: funcname: line: msg" to std::cerr
void PrintError(const std::string& filename,
        const std::string& funcname, int line, const std::string& msg);

// Set permissions READ-ONLY for "filepath"
void ReadOnlyPermissions(std::string& filepath);

}
