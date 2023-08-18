#include "../includes/cli_aco.h"

namespace s21{

void CliAco::run(){    
    try {
        // Load graph from file
        PrintMsg_("Enter graph filepath");
        const std::string filepath = ReadLine_();
        Graph<double> graph = Graph<double>::LoadFromFile(filepath);
        
        int iters_count;
        PrintMsg_("Enter algorithm iters count");
        iters_count = ReadNum_();
        if (iters_count < 1) {
            throw CliException("Iterations count cannot be non-positive");
        }
        
        AcoSingle aco_single(graph);
        AcoMulti aco_multi(graph);

        Timer timer;
        long long single_duration, multi_duration;
        
        timer.Start();
        TsmResult single_result = aco_single.run(iters_count);
        timer.End();
        single_duration = timer.GetDuration();

        timer.Start();
        TsmResult multi_result = aco_multi.run(iters_count);
        timer.End();
        multi_duration = timer.GetDuration();

        auto print_res = [](
            const std::string& title,
            const TsmResult& tsm_result,
            double time
        ){
            std::cout
                << '\t' << title << std::endl
                << "Vertices: " << std::endl
                << tsm_result.vertices << std::endl
                << "Distance: " << tsm_result.distance << std::endl
                << "Execution time: " << (time / 1000) << " ms" << std::endl;
        };

        print_res("Single thread", single_result, single_duration);
        print_res("Multiple threads", multi_result, multi_duration);

    } catch (Exception& e) {
        PrintMsg_(e.GetMessage());
    }
}

}

int main(){
    ::s21::CliAco cli;
    cli.run();
}
