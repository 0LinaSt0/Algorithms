#include <iostream>

#include "matrix/includes/sle.h"
#include "matrix/includes/graph.h"
#include "matrix/includes/matrix.h"
#include "algorithms/includes/winograd.h"

int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    std::cout << RUN_ALL_TESTS() << std::endl;
}
