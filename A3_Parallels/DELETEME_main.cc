#include <iostream>
#include <vector>
#include <array>

#include "utils/includes/utils.h"
#include "matrix/includes/matrix.h"
#include "algorithms/SLE/includes/sle_gaussian.h"

void print_vector(const std::vector<double>& g){
    for(auto& elem : g){
        std::cout << elem << "  ";
    }
        std::cout << std::endl;
}

void print_vector_of_vector(const std::vector<std::vector<double>>& g){
    for(auto& row : g){
        print_vector(row);
    }
}

void print_result(s21::Matrix<double>& matrix, s21::SleGaussianParent& sle, s21::SleResult& rsl){
    print_vector(rsl.equation_roots);
    std::cout << "Is the factors are valid: "
            << sle.CheckCalculatedFactors(matrix)
            << std::endl;
}

std::vector<std::vector<double>> create_matrix(){
    {
        //// MANY SOLUTIONS
        // std::vector<std::vector<double>> returned{
        //     std::vector<double>{0, 0, 0, 0, 0},
        //     std::vector<double>{0, 0, 0, 0, 0},
        //     std::vector<double>{0, 0, 0, 0, 0},
        //     std::vector<double>{0, 0, 0, 0, 0}
        // };
        // return returned;
    }
    {
        //// MANY SOLUTIONS
        // std::vector<std::vector<double>> returned{
        //     std::vector<double>{2, 3, -1, 1, 1},
        //     std::vector<double>{8, 12, -9, 8, 3},
        //     std::vector<double>{4, 6, 3, -2, 3},
        //     std::vector<double>{2, 3, 9, -7, 3}
        // };
        // return returned;
    }
    {
        //// INCONSISTENT
        // std::vector<std::vector<double>> returned{
        //     std::vector<double>{4, -3, 2, -1, 8},
        //     std::vector<double>{3, -2, 1, -3, 7},
        //     std::vector<double>{5, -3, 1, -8, 1}
        // };
        // return returned;
    }
    {
        //// 1.4
        // std::vector<std::vector<double>> returned{
        //     std::vector<double>{5, 7}
        // };
        // return returned;
    }
    {
        //// 1.4
        // std::vector<std::vector<double>> returned{
        //     std::vector<double>{5, 0, 7}
        // };
        // return returned;
    }
    {
        //// INCONSISTENT
        // std::vector<std::vector<double>> returned{
        //     std::vector<double>{5, 1, 7}
        // };
        // return returned;
    }
    {
        //// -11 31
        // std::vector<std::vector<double>> returned{
        //     std::vector<double>{5, 2, 7},
        //     std::vector<double>{2, 1, 9}
        // };
        // return returned;
    }
    {
        //// -0.153846  -0.846154  1.80769
        // std::vector<std::vector<double>> returned{
        //     std::vector<double>{0, 5, 4, 3},
        //     std::vector<double>{5, 1, 2, 2},
        //     std::vector<double>{3, 4, 6, 7}
        // };
        // return returned;
    }
    {
        //// -1 1 3
        // std::vector<std::vector<double>> returned{
        //     std::vector<double>{2, 1, 1, 2},
        //     std::vector<double>{1, -1, 0, -2},
        //     std::vector<double>{3, -1, 2, 2}
        // };
        // return returned;
    }
    {
        //// 4.02347  0.237271  0.163783  -0.93755  -0.173827  0
        // std::vector<std::vector<double>> returned{
        //     std::vector<double>{0, 11, 2, 1, 0, 0, 2},
        //     std::vector<double>{0, 1, 10, 2, 0, 0, 0},
        //     std::vector<double>{2, 1, 2, 9, 1, 0, 0},
        //     std::vector<double>{1, 0, 0, 1, 12, 0, 1},
        //     std::vector<double>{0, 0, 0, 0, 0, 8, 0},
        //     std::vector<double>{2, 2, 0, 0, 3, 0, 8}
        // };
        // return returned;
    }
    {
        // INCONSISTENT
        // std::vector<std::vector<double>> returned{
        //     std::vector<double>{0, 11, 2, 1, 2},
        //     std::vector<double>{0, 1, 10, 2, 0},
        //     std::vector<double>{2, 1, 2, 9, 0},
        //     std::vector<double>{1, 0, 0, 10, 1},
        //     std::vector<double>{0, 5, 0, 4, 0},
        //     std::vector<double>{2, 2, 0, 0, 8}
        // };
        // return returned;
    }
    {
        //// INCONSISTENT
        // std::vector<std::vector<double>> returned{
        //     std::vector<double>{9, 0, 0, 3, 1, 0, 1},
        //     std::vector<double>{0, 11, 2, 1, 0, 0, 2},
        //     std::vector<double>{0, 1, 10, 2, 0, 0, 0},
        //     std::vector<double>{2, 1, 2, 9, 1, 0, 0},
        //     std::vector<double>{1, 0, 0, 1, 12, 0, 1},
        //     std::vector<double>{0, 0, 0, 0, 0, 8, 0},
        //     std::vector<double>{2, 2, 0, 0, 3, 0, 8}
        // };
        // return returned;
    }
    {
        //// -12.1939  -1.86645  -0.960441  9.84075  -6.2605  -0.0185866  -2.32726  -2.39437  2.97297  4.71629  -3.31108  13.9199
        std::vector<std::vector<double>> returned{
            std::vector<double>{0, 7.77, 7.30, 32.5, 8.45, 41.1, 3.89, 75.6, 0, 0, 5.46, 0, 36.5},
            std::vector<double>{0, 0, 4.53, 0, 61.2, 6.72, 6.02, 8.10, 8.03, 85.9, 0, 0, 7.98},
            std::vector<double>{0, 0, 0, 87.2, 49.2, 9.82, 275, 0, 31.5, 7.03, 8.4, 0, 8.91},
            std::vector<double>{1.73, 0, 80.3, 0, 0, 90.8, 0, 2.92, 7.69, 74.3, 72.6, 0, 26.0},
            std::vector<double>{0, 0, 66.6, 5.24, 0, 0, 0, 0, 0, 3.8, 11.9, 3, 7.88},
            std::vector<double>{0, 3.96, 4.47, 4.90, 0, 0, 0, 37.7, 0, 3.51, 7.10, 6.91, 35.5},
            std::vector<double>{5.26, 3.96, 9.08, 7.50, 26.7, 3.73, 0, 2.49, 2.06, 3.53, 92.2, 33.2, 0},
            std::vector<double>{0, 5.27, 0, 8.95, 0, 23.2, 82.0, 0, 6.90, 48.4, 41, 0, 0},
            std::vector<double>{24.5, 5.02, 3.87, 0, 51.8, 44.5, 0, 0, 0, 6.14, 5.25, 45.3, 5.19},
            std::vector<double>{20.7, 13, 0, 55.1, 1.17, 5.19, 4.23, 72.7, 0, 0, 2.48, 0, 66},
            std::vector<double>{3.88, 27.3, 21, 35, 91.3, 99.6, 0, 5.63, 84.6, 0, 0, 7.86, 0},
            std::vector<double>{5.10, 35.6, 0, 9.4, 0, 2.29, 0, 0, 0, 7.67, 0, 0, 0}
        };
        return returned;
    }
}

void usual(s21::Matrix<double>& matrix){
    s21::SleGaussianUsual alg(matrix);
    s21::SleResult sle = alg.GaussianElimination();

    print_result(matrix, alg, sle);
}

void parallel(s21::Matrix<double>& matrix){
    s21::SleGaussianParellel alg(matrix);
    s21::SleResult sle = alg.GaussianElimination();

    print_result(matrix, alg, sle);
}

int main(void)
{
    std::vector<std::vector<double>> g = create_matrix();
    s21::Matrix<double> matrix(g);

    std::cout << matrix << std::endl << std::endl;
    std::cout << "Usual_result: " << std::endl;
    usual(matrix);
    std::cout << std::endl << "Parallel_result: " << std::endl;
    parallel(matrix);
}
