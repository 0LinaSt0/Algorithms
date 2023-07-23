#pragma once

#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <thread>

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

using threads_array_type    = std::vector<std::thread>;


const std::string INAPPROPRIATE_GRAPH_MSG = "It is impossible to solve "
                            "travelling salesman problem with current graph";
const std::string UNSOLVABLE_MATRIX_MSG = "It is impossible to solve "
                            "systems of linear equations with current matrix";
const std::string DEFAULT_DOT_NAME = "graph_default.dot";
const fs::path ROOT_DIR = fs::current_path();
const fs::path GRAPHS_PATH = "materials/graphs";
const fs::path DOTS_PATH = "materials/dot_representations";

struct TsmResult {
    std::vector<int> vertices; // an array with the route
    double distance;  // the length of this route
};

struct SleResult {
    using sle_type  = std::vector<double>;

    sle_type equation_roots;
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

/**
 * Join threads from [threads_array]
 */
void JoinThreads(threads_array_type& threads_array);

/**
 * Compare two doubles [a] and [b] with allowable error(precision) 1e-10
 * @return true if [a] and [b] are equal
 * @return false otherwise
 */
bool DoubleCompare(double a, double b);

}

std::ostream& operator<<(std::ostream& out, const s21::TsmResult& tsm_result);
std::ostream& operator<<(std::ostream& out, const s21::SleResult& sle_result);

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v){
    for (size_t i = 0; i < v.size(); i++){
        out << v[i] << " ";
    }

    return out;
}

template <typename T>
std::ostream& operator<<(
    std::ostream& out, 
    const std::vector<std::vector<T>>& v
){
    for (size_t i = 0; i < v.size(); i++){
        out << v[i];
        if (i + 1 != v.size()) out << std::endl;
    }

    return out;
}
