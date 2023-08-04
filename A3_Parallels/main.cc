#include <exception>

#include "algorithms/ACO/includes/aco.h"

int main(){
    const std::string filename = "materials/matrix/valid/graphs/10_with_several_soltuions";



    try {
        {
            s21::Aco aco(filename);
            std::cout
                << aco.run()
                << std::endl;
        }
        {
            ::s21::Aco aco(::s21::Graph<int>::LoadFromFile(filename));
            std::cout
                << aco.run()
                << std::endl;
        }
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
    }

}
