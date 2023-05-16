#pragma once

// #include <filesystem>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <regex>

#include <random> // DELETE MEEEEEE

// #include "../../utils/includes/utils.hpp"


// namespace fs = std::filesystem;

namespace s21{

// const std::string DEFAULT_DOT_NAME = "graph_default.dot";
// const fs::path ROOT_DIR = fs::current_path();
// const fs::path GRAPHS_PATH = "materials/graphs";
// const fs::path DOTS_PATH = "materials/dot_representations";

class Graph{
public:
    using elem_of_graph_type        = std::vector<int>;
    using graph_type                = std::vector<elem_of_graph_type>;
    using size_type                 = typename graph_type::size_type;
    using reference                 = typename graph_type::reference;
    using const_reference           = typename graph_type::const_reference;

    Graph();
    Graph(const Graph& other) = default;
    Graph(Graph&& other) = default;
    Graph(const graph_type& inp_graph);
    Graph(graph_type&& inp);
    ~Graph() = default;

    Graph& operator=(const Graph& other) = default;
    Graph& operator=(Graph&& other) = default;
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;

    std::size_t Size();

    void ExportGraphToDot(std::string filename);

    void tmp_write_to_graph_DELETEME(int elem_number);
    void tmp_print_graph_DELETEME(void);

private:
    graph_type graph_;
    bool is_directed_;

    std::string DotFilename_(std::string& filename);

    std::string GraphDotRepresentation_();
};



}
