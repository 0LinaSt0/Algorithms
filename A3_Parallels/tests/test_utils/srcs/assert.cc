#include "../includes/assert.h"

namespace s21::test{

void Assert(
    const std::string& file,
    const int line,
    bool condition
) {
    if (!condition){
        std::cerr 
            << "Error on "
            << file
            << ": "
            << line
            << std::endl;
        exit(1);
    }
}

}
