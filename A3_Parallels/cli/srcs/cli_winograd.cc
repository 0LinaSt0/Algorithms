#include "../includes/cli_winograd.h"

namespace s21{

void CliWinograd::run(){
    try {
        // Get run type
        PrintMsg_("Select algo run type\n0: random\n1: with files");
        int run_type = ReadNum_();
        if (run_type != 0 && run_type != 1) {
            throw CliException("Invalid run type. Must be 0 or 1");
        }

        // Load matrices from file
        std::pair<Matrix<double>, Matrix<double>> mtrx = 
            (run_type == 0) ?
            random_mtrx_() :
            load_mtrx_();
        if (mtrx.first.ColumnsSize() != mtrx.second.RowsSize()){
            throw CliException(
                "Values of columns in A and rows in B must be equal"
            );
        }
                
        // Get algo iters count
        int iters_count;
        PrintMsg_("Enter algorithm iters count");
        iters_count = ReadNum_();
        if (iters_count < 1) {
            throw CliException("Iterations count cannot be non-positive");
        }

        // Print input matrices
        Matrix<double>& A = mtrx.first;
        Matrix<double>& B = mtrx.second;
        std::cout
            << "\tMatrix A"
            << std::endl
            << A 
            << std::endl
            << std::endl
            << "\tMatrix B"
            << std::endl
            << B
            << std::endl
            << std::endl;

        // Execute
        MatrixResult<double> result_usual, result_parallel, result_pipeline;
        long long duration_usual = 0, 
                    duration_parallel = 0, 
                    duration_pipeline = 0;
        
        auto run_algo = [&A, &B](
            WinogradParent& algo, 
            MatrixResult<double>& result,
            long long& duration
        ){
            Timer timer;

            timer.Start();
            result = algo.WinogradMultiplication(A, B);
            timer.End();
            duration = timer.GetDuration();
        };

        auto print_res = [](
            const std::string& title,
            const MatrixResult<double>& tsm_result,
            double time
        ){
            std::cout
                << '\t' << title << std::endl
                << "Vertices: " << std::endl
                << tsm_result.matrix_array << std::endl
                << "Execution time: " << (time / 1000) << " ms" << std::endl;
        };

        for (int i = 0; i < iters_count; i++){
            WinogradUsual win_usual;
            WinogradParallel win_parallel;
            WinograPipelineParallel win_pipeline;
            long long duration_usual_tmp,
                        duration_parallel_tmp,
                        duration_pipeline_tmp;

            run_algo(win_usual, result_usual, duration_usual_tmp);
            run_algo(win_parallel, result_parallel, duration_parallel_tmp);
            run_algo(win_pipeline, result_pipeline, duration_pipeline_tmp);

            duration_usual += duration_usual_tmp;
            duration_parallel += duration_parallel_tmp;
            duration_pipeline += duration_pipeline_tmp;
        }

        // Print results
        print_res("Single thread", result_usual, duration_usual);
        print_res("Multiple threads", result_parallel, duration_parallel);
        print_res("Pipeline parallels", result_pipeline, duration_pipeline);

    } catch (Exception& e) {
        PrintMsg_(e.GetMessage());
    }
}

std::pair<Matrix<double>, Matrix<double>> CliWinograd::random_mtrx_() const{
    int A_row, A_col, B_row, B_col;

    auto read_int_lambda = [this](const std::string& msg){
        this->PrintMsg_(msg);
        int val = this->ReadNum_();
        if (val < 1) throw CliException(
            "Matrix dimension cannot be non-positive"
        );
        return val;
    };

    auto gen_mtrx_lambda = [](int rows, int columns){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(-100, 100);
        
        std::vector<std::vector<double>> new_mtrx;
        new_mtrx.reserve(rows);
        for (int row = 0; row < rows; row++){
            std::vector<double> new_row;
            new_row.reserve(columns);
            for (int column = 0; column < columns; column++){
                new_row.push_back(distrib(gen));
            }
            new_mtrx.push_back(std::move(new_row));
        }

        return new_mtrx;
    };

    A_row = read_int_lambda("Rows count for matrix A");
    A_col = read_int_lambda("Columns count for matrix A");
    B_row = read_int_lambda("Rows count for matrix B");
    B_col = read_int_lambda("Columns count for matrix B");

    return std::pair<Matrix<double>, Matrix<double>>{
        gen_mtrx_lambda(A_row, A_col),
        gen_mtrx_lambda(B_row, B_col)
    };
}

std::pair<Matrix<double>, Matrix<double>> CliWinograd::load_mtrx_() const{
    PrintMsg_("Enter matrix `A` filepath");
    const std::string filepath_A = ReadLine_();

    PrintMsg_("Enter matrix `B` filepath");
    const std::string filepath_B = ReadLine_();

    return std::pair<Matrix<double>, Matrix<double>>{
        Matrix<double>::LoadFromFile(filepath_A),
        Matrix<double>::LoadFromFile(filepath_B)
    };
}

}

int main(){
    ::s21::CliWinograd cli;
    cli.run();
}
