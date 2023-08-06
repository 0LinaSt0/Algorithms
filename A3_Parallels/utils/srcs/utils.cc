#include "../includes/utils.h"

namespace s21{

void PrintError(const std::string& filename,
        const std::string& funcname, int line, const std::string& msg){
    std::cerr << filename << ": "
            << funcname << ": "
            << line << ": "
            << msg << std::endl;
}

void ReadOnlyPermissions(std::string& filepath){
    fs::path path = filepath;

    fs::permissions(
        path,
        fs::perms::none |
            fs::perms::owner_read |
            fs::perms::group_read |
            fs::perms::others_read,
        fs::perm_options::replace
    );
}

void JoinThreads(threads_array_type& threads_array){
    for(auto &thread : threads_array){
        thread.join();
    }
}

bool DoubleCompare(double a, double b){
    const double val = 1e-10;
    return std::abs(a - b) < val;
}

}

std::ostream& operator<<(std::ostream& out, const ::s21::TsmResult& tsm_result){
    return out
        << "distance: " << tsm_result.distance << std::endl
        << "vertices: " << std::endl
        << tsm_result.vertices;
}

std::ostream& operator<<(std::ostream& out, const ::s21::SleResult& sle_result){
    return out
        << "vertices: " << std::endl
        << sle_result.equation_roots;
}
