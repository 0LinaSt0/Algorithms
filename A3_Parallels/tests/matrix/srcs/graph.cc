#include "../includes/graph.h"

namespace s21::test::graph{

void TEST_GRAPH_LOAD_FROM_FILE(){
    std::cout << __FUNCTION__ << std::endl;

    {
        try {
            ::s21::Graph<int> graph = ::s21::Matrix<int>::LoadFromFile(
                MATERIALS_ROOT + "00_empty_matrix"
            );
            s21::test::Assert(__FILE__, __LINE__, false);
        } catch (::s21::Exception&){
            
        }
    }

    {
        try {
            ::s21::Graph<int> graph = ::s21::Matrix<int>::LoadFromFile(
                MATERIALS_ROOT + "01_with_solution"
            );
            std::cout << graph << std::endl;
        } catch (::s21::Exception&){
            s21::test::Assert(__FILE__, __LINE__, false);
        }
    }
}

void RUN_ALL_TESTS(){
    TEST_GRAPH_LOAD_FROM_FILE();
}

} // namespace s21::test::graph
