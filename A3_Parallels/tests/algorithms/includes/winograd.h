#ifndef TEST_WINOGRAD_H
#define TEST_WINOGRAD_H

#include <string>
#include <vector>
#include <sstream>
#include <gtest/gtest.h>

#include "../../test_utils/includes/utils.h"
#include "../../../algorithms/Winograd/includes/winograd.h"

#define TEST_SUITE_NAME_WIN WINOGRAD_TEST

namespace s21::test::winograd{

const std::string WINOGRAD_MTRX_DIR = "./materials/matrix/valid/winograd/";

struct MultiplicatorInfo{
    std::string A;
    std::string B;
    std::string C;
    bool mtrx_valid;
};
}

#endif

