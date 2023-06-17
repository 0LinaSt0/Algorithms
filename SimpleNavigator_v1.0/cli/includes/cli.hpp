#pragma once

#include <iostream>
#include <stdexcept>

#include "../../graph/includes/graph.hpp"
#include "../../graph/includes/graphAlgorithms.hpp"


namespace s21{

constexpr int MENU_OPTIONS_COUNT = 8;
constexpr int BAD_INPUT_VALUE = -1;

class CLI{
public:
    CLI() = default;
    CLI(const CLI&) = delete;
    CLI(CLI&&) = delete;
    ~CLI() = default;

    CLI& operator=(const CLI&) = delete;
    CLI& operator=(CLI&&) = delete;

    /**
     * Main method to start CLI.
    */
    void run();

private:
    typedef void (CLI::*FuncPtr)(void);

    std::unique_ptr<Graph> graph_;
    GraphAlgorithms graph_algorithms_;
    const std::string menu_msg_[MENU_OPTIONS_COUNT] = {
        "1. graph traversal in breadth",
        "2. graph traversal in depth",
        "3. searching for the shortest path between any two vertices",
        "4. searching for the shortest paths between all pairs of vertices",
        "5. searching for the minimal spanning tree",
        "6. solving the salesman problem (ant algorithm)",
        "7. solving the salesman problem (branch and bound method)",
        "8. solving the salesman problem (exhaustive search)"
    };
    const FuncPtr methods_[MENU_OPTIONS_COUNT] = {
        &CLI::BreadthFirstSearch_,
        &CLI::DepthFirstSearch_,
        &CLI::GetShortestPathBetweenVertices_,
        &CLI::GetShortestPathsBetweenAllVertices_,
        &CLI::GetLeastSpanningTree_,
        &CLI::SolveTravelingSalesmanProblem_,
        &CLI::STSPBranchBoundMethodAlgorithm_,
        &CLI::ExhaustiveSearch_
    };

    void PrintMenu_() const;
    void PrintMsg_(const std::string& msg) const;
    int ReadInt_() const;

    /**
     * Load graph from given file.
     * Return true on success, false otherwise.
    */
    bool LoadGraphFromFile_(const std::string& filepath);

    void BreadthFirstSearch_();
    void DepthFirstSearch_();
    void GetShortestPathBetweenVertices_();
    void GetShortestPathsBetweenAllVertices_();
    void GetLeastSpanningTree_();
    void SolveTravelingSalesmanProblem_();

    void STSPBranchBoundMethodAlgorithm_();
    void ExhaustiveSearch_();

};

}
