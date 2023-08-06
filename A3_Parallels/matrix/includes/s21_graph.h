#ifndef S21_GRAPH_H
#define S21_GRAPH_H

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <utility>
#include <regex>

#include "matrix.h"
#include "../../utils/includes/utils.h"
#include "../../utils/includes/exception.h"

namespace fs = std::filesystem;

namespace s21{

template< class T >
class Graph : public Matrix<T>{
public:
    template <typename Type>
    friend std::ostream& ::operator<<(
        std::ostream& out,
        const Graph<Type>& graph
    );

    using parent_type       = Matrix<T>;
    using matrix_type       = typename parent_type::matrix_type;
    using size_type         = typename parent_type::size_type;
    using row_matrix_type   = typename parent_type::row_matrix_type;

    Graph() = delete;
    Graph(const Matrix<T>& inp_mtrx);
    Graph(Matrix<T>&& inp_mtrx);
    Graph(const Graph& other) = default;
    Graph(Graph&& other) = default;
    Graph(const matrix_type& inp_graph);
    Graph(matrix_type&& inp_graph);
    Graph(const matrix_type& inp_graph, size_type min_spanning_tree_size);
    Graph(matrix_type&& inp_graph, size_type min_spanning_tree_size);
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

    template <typename Type>
    static Graph<T> ConvertFromGraph(const Graph<Type>& graph){
        std::vector<std::vector<T>> mtrx;
        
        size_type nodes_count = graph.NodesSize();
        mtrx.reserve(nodes_count);
        for (size_type i = 0; i < nodes_count; i++){
            std::vector<T> row;
            row.reserve(nodes_count);
            for (size_type j = 0; j < nodes_count; j++){
                row.push_back(graph[i][j]);
            }
            mtrx.push_back(std::move(row));
        }

        return Graph<T>(std::move(mtrx));
    }
    
    /**
     * Load graph from a file [filename] in the adjacency matrix format
     * @return new Graph<T> object
     * @throw GraphException on invalid file
     */
    static Graph<T> LoadFromFile(const std::string& filename);

    /**
     * Exporting a graph to a dot file [filename]
     */
    static void ExportGraphToDot(
                    const Graph<T> graph,
                    const std::string& filename
    );

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
    static std::string DotFilename_(const std::string& filename);

    /**
     * Represent Graph to one srting in dot format
     * @return std::string with Graph's content for dot file
     */
    static std::string GraphDotRepresentation_(const Graph<T> graph);

    class GraphException : public ::s21::Exception{
    public:
        GraphException() = delete;
        GraphException(const std::string& msg);
        GraphException(GraphException&&) = delete;
        ~GraphException() = default;

        GraphException& operator=(const GraphException&) = delete;
        GraphException& operator=(GraphException&&) = delete;

        std::string GetMessage() const;
    };

};

}

template <typename Type>
std::ostream& operator<<(std::ostream& out,const ::s21::Graph<Type>& graph){
    return out 
        << dynamic_cast<const ::s21::Matrix<Type>&>(graph) << std::endl
        << "is directed:\t" << graph.is_directed_ << std::endl
        << "is connected:\t" << graph.is_connected_;
}

#include "../srcs/s21_graph_impl.h"

#endif
