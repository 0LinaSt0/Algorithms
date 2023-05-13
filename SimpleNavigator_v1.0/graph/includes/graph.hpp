#pragma once

#include <filesystem>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <regex>

#include "../../utils/includes/utils.hpp"


namespace fs = std::filesystem;

namespace s21{

const std::string DEFAULT_DOT_NAME = "tmp_graph.dot";
const fs::path ROOT_DIR = fs::current_path();
const fs::path GRAPHS_PATH = "materials/graphs";
const fs::path DOTS_PATH = "materials/dots_representation";

class Graph{
public:
    using graph_type    = std::vector<std::vector<int>>;

    Graph();
    Graph(const Graph& other) = default;
    Graph(Graph&& other) = default;
    ~Graph() = default;

    Graph& operator=(const Graph& other) = default;
    Graph& operator=(Graph&& other) = default;

    void ExportGraphToDot(std::string filename);

private:
    graph_type graph_;
    bool is_directed_;

    std::string dotFilename_(std::string& filename);

    std::string graphDotRepresentation_();
};

}
