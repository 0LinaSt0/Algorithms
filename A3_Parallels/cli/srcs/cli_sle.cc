#include "../includes/cli_sle.h"

namespace s21{

void CliSle::run(){    
    try {
        // Load graph from file
        PrintMsg_("Enter matrix filepath");
        const std::string filepath = ReadLine_();
        Sle<double> mtrx = Sle<double>::LoadFromFile(filepath);
        
        // Get algo iters count
        int iters_count;
        PrintMsg_("Enter algorithm iters count");
        iters_count = ReadNum_();
        if (iters_count < 1) {
            throw CliException("Iterations count cannot be non-positive");
        }

        // Execute
        SleGaussianUsual sle_usual(mtrx);
        SleGaussianParellel sle_parallel(mtrx);
        SleResult result_usual, result_parallel;
        long long duration_usual = 0, duration_parallel = 0;

        auto run_algo = [](
            SleGaussianParent& sle,
            SleResult& result,
            long long& duration
        ){
            Timer timer;

            timer.Start();
            result = sle.GaussianElimination();
            timer.End();
            duration = timer.GetDuration();
        };

        auto print_res = [](
            const std::string& title,
            const SleResult& sle_result,
            double time
        ){
            std::cout
                << '\t' << title << std::endl
                << "Vertices: " << std::endl
                << sle_result.equation_roots << std::endl
                << "Execution time: " << (time / 1000) << " ms" << std::endl;
        };

        // Execute
        for (int i = 0; i < iters_count; i++){
            SleGaussianUsual sle_usual(mtrx);
            SleGaussianParellel sle_parallel(mtrx);
            long long duration_usual_tmp, duration_parallel_tmp;

            run_algo(sle_usual, result_usual, duration_usual_tmp);
            run_algo(sle_parallel, result_parallel, duration_parallel_tmp);

            duration_usual += duration_usual_tmp;
            duration_parallel += duration_parallel_tmp;
        }

        // Print results
        print_res("Single thread", result_usual, duration_usual);
        print_res("Multiple threads", result_parallel, duration_parallel);

    } catch (Exception& e) {
        PrintMsg_(e.GetMessage());
    }
}

}

int main(){
    ::s21::CliSle cli;
    cli.run();
}
