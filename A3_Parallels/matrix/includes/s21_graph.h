#ifndef S21_GRAPH_H
#define S21_GRAPH_H

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <utility>
#include <regex>

#include "matrix.h"
#include "../../utils/includes/utils.h"

namespace fs = std::filesystem;

namespace s21{

template< class T >
class Graph : public Matrix<T>{
public:
    using parent_type       = Matrix<T>;
    using graph_type        = typename parent_type::matrix_type;
    // using size_type         = typename parent_type::size_type; DELETEME
    // using row_matrix_type   = typename parent_type::row_matrix_type; DELETEME

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

    /**
     * @return the number of nodes in graph
     */
    size_type NodesSize() const;

    /**
     * @return return sum of weights of all edges in least spanning tree.
    */
    size_type MinSpanningTreeSize() const;

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
    bool LoadFromFile(std::string filename);

    /**
     * Exporting a graph to a dot file [filename]
     */
    void ExportGraphToDot(std::string filename);

private:
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
template <class type>
std::ostream& operator<<(std::ostream& out, const s21::Graph<type>& graph);

#include "../srcs/s21_graph_impl.h"

#endif
