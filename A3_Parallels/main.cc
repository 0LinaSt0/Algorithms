#include "cli/includes/cli_aco.h"

#include "algorithms/Winograd/includes/winograd.h"

int main(){
    std::cout << ">> START" << std::endl;

    s21::WinograPipelineParallel p;
    s21::Matrix<double> A = s21::Matrix<double>::LoadFromFile("tmp_A");
    s21::Matrix<double> B = s21::Matrix<double>::LoadFromFile("tmp_B");
    
    s21::MatrixResult<double> res = p.WinogradMultiplication(A, B);

    std::cout
        << "** Matrix A **"
        << std::endl
        << A
        << std::endl
        << std::endl
        << "** Matrix B **"
        << std::endl
        << B
        << std::endl
        << std::endl
        << "** Result matrix **"
        << std::endl
        << res.matrix_array
        << std::endl;
}   
