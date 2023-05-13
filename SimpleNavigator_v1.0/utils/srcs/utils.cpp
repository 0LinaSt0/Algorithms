#include "../includes/utils.hpp"

namespace s21{

void printError(const std::string& filename, 
        const std::string& funcname, int line, const std::string& msg){
    std::cout << filename << ": "
            << funcname << ": "
            << line << ": "
            << msg << std::endl;
}

}
