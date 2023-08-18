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
                
        int iters_count;
        PrintMsg_("Enter algorithm iters count");
        iters_count = ReadNum_();
        if (iters_count < 1) {
            throw CliException("Iterations count cannot be non-positive");
        }

        std::cout
            << "\tMatrix A"
            << std::endl
            << mtrx.first 
            << std::endl
            << std::endl
            << "\tMatrix B"
            << std::endl
            << mtrx.second
            << std::endl
            << std::endl;
        
        WinogradUsual win_usual;
        WinogradParallel win_parallel;
        WinograPipelineParallel win_pipeline;

        Timer timer;
        long long single_duration, multi_duration, pipeline_duration;
        
        timer.Start();
        MatrixResult<double> single_result = win_usual.WinogradMultiplication(
            mtrx.first,
            mtrx.second
        );
        timer.End();
        single_duration = timer.GetDuration();

        timer.Start();
        MatrixResult<double> multi_result = win_parallel.WinogradMultiplication(
            mtrx.first,
            mtrx.second
        );
        timer.End();
        multi_duration = timer.GetDuration();

        timer.Start();
        MatrixResult<double> pipe_result = win_pipeline.WinogradMultiplication(
            mtrx.first,
            mtrx.second
        );
        timer.End();
        pipeline_duration = timer.GetDuration();

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

        print_res("Single thread", single_result, single_duration);
        print_res("Multiple threads", multi_result, multi_duration);
        print_res("Pipeline parallels", pipe_result, pipeline_duration);

    } catch (Exception& e) {
        PrintMsg_(e.GetMessage());
    }
}

void CliWinograd::PrintMenu_() const{

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
