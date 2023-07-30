#include <exception>

#include "algorithms/ACO/includes/aco.h"

int main(){
    const std::string filename = "materials/matrix/valid/graphs/10_with_several_soltuions";



    try {
        s21::Aco aco(filename);
        std::cout
            << aco.GetGraph()
            << std::endl
            << aco.run()
            << std::endl;
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
    }

}
