#pragma once

#include <iostream>
#include <string>

#define ERROR(file, func, line, msg)( \
    (s21::printError((file), (func), (line), (msg))), \
    (void)0 \
)

namespace s21{

void printError(const std::string& filename, 
        const std::string& funcname, int line, const std::string& msg);

}