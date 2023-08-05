#include <exception>

#include "algorithms/ACO/includes/aco_single.h"
#include "algorithms/ACO/includes/aco_multi.h"
#include "cli/includes/timer.h"

int main(){
    const std::string filename = "materials/matrix/valid/graphs/25_sixty_vertices";

    try {
        {
            ::s21::Timer timer;
            ::s21::AcoSingle aco(::s21::Graph<int>::LoadFromFile(filename));

            timer.Start();
            ::s21::TsmResult tsmResult = aco.run();
            timer.End();
            std::cout
                << "\tSinglethread"
                << std::endl
                << tsmResult
                << std::endl
                << "exec duration: "
                << (timer.GetDuration() / 1000)
                << std::endl;
        }

        {
            ::s21::Timer timer;
            ::s21::AcoMulti aco(::s21::Graph<int>::LoadFromFile(filename));

            timer.Start();
            ::s21::TsmResult tsmResult = aco.run();
            timer.End();
            std::cout
                << "\tMultithread"
                << std::endl
                << tsmResult
                << std::endl
                << "exec duration: "
                << (timer.GetDuration() / 1000)
                << std::endl;
        }
    } catch (std::exception& e){
        std::cout << e.what() << std::endl;
    }

}
