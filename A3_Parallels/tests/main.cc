#include <iostream>

#include "matrix/includes/graph.h"
#include "matrix/includes/matrix.h"

int main(int argc, char** argv){
    (void)argc; (void)argv;
    
    std::cout << " <<< TESTS >>> " << std::endl;
    ::s21::test::mtrx::RUN_ALL_TESTS();
    ::s21::test::graph::RUN_ALL_TESTS();
}
