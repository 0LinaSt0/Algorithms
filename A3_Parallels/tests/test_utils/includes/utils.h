#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <string>

namespace s21::test{

const std::string MTRX_ROOT_DIR = "./materials/matrix/";
const std::string MTRX_VALID_DIR = MTRX_ROOT_DIR + "valid/";
const std::string MTRX_INVALID_DIR = MTRX_ROOT_DIR + "invalid/";
const std::string GRAPH_VALID_DIR = MTRX_VALID_DIR + "graphs/";
const std::string SLE_VALID_DIR = MTRX_VALID_DIR + "sles/";

const std::string valid_graph_files[26] = {
    GRAPH_VALID_DIR + "01_with_solution",
    GRAPH_VALID_DIR + "02_without_solution",
    GRAPH_VALID_DIR + "03_without_solution",
    GRAPH_VALID_DIR + "04_with_several_solutions_loop",
    GRAPH_VALID_DIR + "05_with_solutiom_loop",
    GRAPH_VALID_DIR + "06_with_solutiom_loop",
    GRAPH_VALID_DIR + "07_connected_without_solution",
    GRAPH_VALID_DIR + "08_connected_loop",
    GRAPH_VALID_DIR + "09_with_several_soltuions",
    GRAPH_VALID_DIR + "10_with_several_soltuions",
    GRAPH_VALID_DIR + "11_with_several_soltuions",
    GRAPH_VALID_DIR + "12_disconnected",
    GRAPH_VALID_DIR + "13_connected",
    GRAPH_VALID_DIR + "14_default_matrix",
    GRAPH_VALID_DIR + "15_default_matrix",
    GRAPH_VALID_DIR + "16_directed",
    GRAPH_VALID_DIR + "17_directed",
    GRAPH_VALID_DIR + "18_directed",
    GRAPH_VALID_DIR + "19_directed",
    GRAPH_VALID_DIR + "20_eight_vertices",
    GRAPH_VALID_DIR + "21_seven_vertices",
    GRAPH_VALID_DIR + "22_ten_vertices",
    GRAPH_VALID_DIR + "23_thirteen_vertices",
    GRAPH_VALID_DIR + "24_twenty_vertices",
    GRAPH_VALID_DIR + "25_sixty_vertices",
    GRAPH_VALID_DIR + "26_hundred_vertices"
};

const std::string valid_sle_files[13] = {
    SLE_VALID_DIR + "00_zero_factors",
    SLE_VALID_DIR + "01_many_solutions",
    SLE_VALID_DIR + "02_inconsistent",
    SLE_VALID_DIR + "03_one_equation_1",
    SLE_VALID_DIR + "04_one_equation_2",
    SLE_VALID_DIR + "05_one_equation_inconsistent",
    SLE_VALID_DIR + "06_two_equations",
    SLE_VALID_DIR + "07_three_equations_1",
    SLE_VALID_DIR + "08_three_equations_2",
    SLE_VALID_DIR + "09_six_equations",
    SLE_VALID_DIR + "10_six_equations_inconsistent",
    SLE_VALID_DIR + "11_six_equations_and_four_roots",
    SLE_VALID_DIR + "12_twelve_equations"
};

const std::string invalid_graph_files[6] = {
    MTRX_INVALID_DIR + "00",
    MTRX_INVALID_DIR + "01",
    MTRX_INVALID_DIR + "02",
    MTRX_INVALID_DIR + "03",
    MTRX_INVALID_DIR + "04",
    MTRX_INVALID_DIR + "05"
};

}

#endif
