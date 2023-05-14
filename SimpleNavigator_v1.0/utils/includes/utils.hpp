#pragma once

#include <filesystem>
#include <iostream>
#include <string>

#define PRINT_ERROR(file, func, line, msg)( \
    (s21::PrintError((file), (func), (line), (msg))), \
    (void)0 \
)

#define READ_ONLY(file)( \
    (s21::ReadOnlyPermissions((file))) \
    (void)0 \
)


namespace fs = std::filesystem;

namespace s21{

// Print error like "filename: funcname: line: msg" to std::cerr
void PrintError(const std::string& filename, 
        const std::string& funcname, int line, const std::string& msg);

// Set permissions READ-ONLY for "filepath"
void ReadOnlyPermissions(std::string& filepath);

}