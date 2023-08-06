#ifndef TEST_GRAPH_H
#define TEST_GRAPH_H

#include "../../test_utils/includes/assert.h"
#include "../../../matrix/includes/s21_graph.h"

namespace s21::test::graph{

const std::string MATERIALS_ROOT = "./materials/matrix/valid/";

void TEST_GRAPH_LOAD_FROM_FILE();

void RUN_ALL_TESTS();

}

#endif
