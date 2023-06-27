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

    /**
     * @return a value of the cell with [row][col] coordinates
     */
    elem_of_graph_type::value_type at(size_type row, size_type col);

    /**
     * @return a value of the cell with [row][col] coordinates
     */
    elem_of_graph_type::value_type at(size_type row, size_type col) const;

    /**
     * @return the number of nodes in graph
     */
    std::size_t Size() const;


    size_type MinSpanningTreeSize() const;

    /**
     * @return an iterator to the first row of Graph
     */
    iterator_type Begin();

    /**
     * @return a const iterator to the first row of Graph
     */
    const_iterator_type Begin() const;

    /**
     * @return iterator to the element following the last Graph's row
     */
    iterator_type End();

    /**
     * @return a const iterator to the element following the last Graph's row
     */
    const_iterator_type End() const;

    /**
     * @return true if Graph is directed
     * @return false if Graph is not directed
     */
    bool IsDirected() const;

    /**
     * @return true if Graph is connected
     * @return false if Graph is not connected
     */
    bool IsConnected() const;

    /**
     * Loading a graph from a file [filename] in the adjacency matrix format
     * @return true if successful loading
     * @return false if not successful loading
     */
    bool LoadGraphFromFile(std::string filename);

    /**
     * Exporting a graph to a dot file [filename]
     */
    void ExportGraphToDot(std::string filename);

private:
    graph_type graph_;
    bool is_directed_;
    bool is_connected_;
    size_type min_spanning_tree_size_;

    bool IsDirected_() const;
    bool IsConnected_() const;

    /**
     * Check [filename] on validity and generate the file name
     * @return std::string with dot filename
     */
    std::string DotFilename_(std::string& filename);

    /**
     * Represent Graph to one srting in dot format
     * @return std::string with Graph's content for dot file
     */
    std::string GraphDotRepresentation_();

};

}

/**
 * Overload of operator for printing all Graph's content
 */
std::ostream& operator<<(std::ostream& out, const s21::Graph& graph);

#endif
