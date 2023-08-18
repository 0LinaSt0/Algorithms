#include "../includes/cli_aco.h"

namespace s21{

void CliAco::run(){    
    try {
        // Load graph from file
        PrintMsg_("Enter graph filepath");
        const std::string filepath = ReadLine_();
        Graph<double> graph = Graph<double>::LoadFromFile(filepath);
        
        // Get algo iters count
        int iters_count;
        PrintMsg_("Enter algorithm iters count");
        iters_count = ReadNum_();
        if (iters_count < 1) {
            throw CliException("Iterations count cannot be non-positive");
        }
    
        // Run algo and save results
        auto run_algo = [iters_count](
            AcoAbs& aco,
            TsmResult& result,
            long long& duration
        ){
            Timer timer;

            timer.Start();
            result = aco.run(iters_count);
            timer.End();
            duration = timer.GetDuration();
        };

        // Print info
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

        // Execute
        AcoSingle aco_single(graph);
        AcoMulti aco_multi(graph);
        TsmResult result_single, result_multi;
        long long duration_single, duration_multi;

        run_algo(aco_single, result_single, duration_single);
        run_algo(aco_multi, result_multi, duration_multi);

        // Print results
        print_res("Single thread", result_single, duration_single);
        print_res("Multiple threads", result_multi, duration_multi);

    } catch (Exception& e) {
        PrintMsg_(e.GetMessage());
    }
}

}

int main(){
    ::s21::CliAco cli;
    cli.run();
}
