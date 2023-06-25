#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <regex>

#include "../../utils/includes/utils.hpp"

namespace fs = std::filesystem;

namespace s21{

class Graph{
public:
    using elem_of_graph_type        = row_matrix_type;
    using graph_type                = matrix_type;
    using size_type                 = typename graph_type::size_type;
    using reference                 = typename graph_type::reference;
    using const_reference           = typename graph_type::const_reference;
    using iterator_type             = typename graph_type::iterator;
    using const_iterator_type       = typename graph_type::const_iterator;

    Graph();
    Graph(const Graph& other) = default;
    Graph(Graph&& other) = default;
    Graph(const graph_type& inp_graph);
    Graph(graph_type&& inp_graph);
    Graph(const graph_type& inp_graph, size_type min_spanning_tree_size);
    Graph(graph_type&& inp_graph, size_type min_spanning_tree_size);
    ~Graph() = default;

    Graph& operator=(const Graph& other);
    Graph& operator=(Graph&& other);
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;

    elem_of_graph_type::value_type at(size_type row, size_type col);
    elem_of_graph_type::value_type at(size_type row, size_type col) const;

    std::size_t Size() const;
    size_type MinSpanningTreeSize() const;
    iterator_type Begin();
    iterator_type End();
    const_iterator_type Begin() const;
    const_iterator_type End() const;

    bool IsDirected() const;
    bool IsConnected() const;

    bool LoadGraphFromFile(std::string filename);

    void ExportGraphToDot(std::string filename);

    void tmp_print_graph_DELETEME(void);

private:
    graph_type graph_;
    bool is_directed_;
    bool is_connected_;
    size_type min_spanning_tree_size_;

    bool IsDirected_() const;
    bool IsConnected_() const;

    std::string DotFilename_(std::string& filename);

    std::string GraphDotRepresentation_();

};

}

std::ostream& operator<<(std::ostream& out, const s21::Graph& graph);

#endif
