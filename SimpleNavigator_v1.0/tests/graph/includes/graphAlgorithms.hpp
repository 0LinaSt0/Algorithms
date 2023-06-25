#pragma once

#include <string>
#include <fstream>
#include <gtest/gtest.h>

#include "../../../cli/includes/timer.hpp"
#include "../../../graph/includes/graph.hpp"
#include "../../../graph/includes/graphAlgorithms.hpp"

#define TEST_SUITE_NAME GRAPH_ALGORITHMS_TESTS

typedef s21::TsmResult (s21::GraphAlgorithms::*AlgoPtr)(s21::Graph&);
const std::string valid_graphs_dir = "./materials/graphs/valid/";
const std::string invalid_graphs_dir = "./materials/graphs/invalid/";
