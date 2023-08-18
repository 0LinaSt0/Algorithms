#include "../includes/cli_sle.h"

namespace s21{

void CliSle::run(){    
    try {
        // Load graph from file
        PrintMsg_("Enter matrix filepath");
        const std::string filepath = ReadLine_();
        Sle<double> mtrx = Sle<double>::LoadFromFile(filepath);
        
        int iters_count;
        PrintMsg_("Enter algorithm iters count");
        iters_count = ReadNum_();
        if (iters_count < 1) {
            throw CliException("Iterations count cannot be non-positive");
        }
        
        SleGaussianUsual sle_usual(mtrx);
        SleGaussianParellel sle_parallel(mtrx);

        Timer timer;
        long long single_duration, multi_duration;
        
        timer.Start();
        SleResult single_result = sle_usual.GaussianElimination();
        timer.End();
        single_duration = timer.GetDuration();

        timer.Start();
        SleResult multi_result = sle_parallel.GaussianElimination();
        timer.End();
        multi_duration = timer.GetDuration();

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

        print_res("Single thread", single_result, single_duration);
        print_res("Multiple threads", multi_result, multi_duration);

    } catch (Exception& e) {
        PrintMsg_(e.GetMessage());
    }
}

void CliSle::PrintMenu_() const{

}

}

int main(){
    ::s21::CliSle cli;
    cli.run();
}
