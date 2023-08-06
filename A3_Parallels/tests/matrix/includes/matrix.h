#ifndef TEST_MATRIX_H
#define TEST_MATRIX_H

#include "../../test_utils/includes/assert.h"
#include "../../../matrix/includes/matrix.h"

namespace s21::test::mtrx{

const std::string MATERIALS_ROOT = "./materials/matrix/valid/";

void TEST_MTRX_LOAD_FROM_FILE();

void RUN_ALL_TESTS();

}

#endif
