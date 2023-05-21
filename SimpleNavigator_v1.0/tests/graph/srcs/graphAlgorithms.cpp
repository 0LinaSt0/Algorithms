#include "../includes/graphAlgorithms.hpp"

namespace s21::tests::graph{

TEST(TEST_SUITE_NAME, BreadthFirstSearch){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;
    const std::string answ[11] = {
        "1 2 3 4 5 6 7 8 9 10 11",
        "2 1 3 4 5 6 7 8 9 10 11",
        "3 1 2 4 5 6 7 8 9 10 11",
        "4 1 2 3 5 6 7 8 9 10 11",
        "5 1 2 3 4 6 7 8 9 10 11",
        "6 1 2 3 4 5 7 8 9 10 11",
        "7 1 2 3 4 5 6 8 9 10 11",
        "8 1 2 3 4 5 6 7 9 10 11",
        "9 1 2 3 4 5 6 7 8 10 11",
        "10 1 2 3 4 5 6 7 8 9 11",
        "11 1 2 3 4 5 6 7 8 9 10"
    };

    auto vectorToString = [](const std::vector<int>& v){
        std::string str;
        
        for (size_t i = 0; i < v.size(); i++){
            str += std::to_string(v[i] + 1);
            if (i + 1 != v.size()) str += ' ';
        }

        return str;
    };
    
    graph.LoadGraphFromFile("./tests/materials/graph/valid/1");
    
    for (int i = 0; i < 11; i++){
        ASSERT_EQ(vectorToString(graphAlgorithms.BreadthFirstSearch(graph, i)),
                   answ[i]);
    }
}

TEST(TEST_SUITE_NAME, MinimumSpanningTree){
    s21::GraphAlgorithms graphAlgorithms;
    
    {
        s21::Graph graph;
        ASSERT_TRUE(graph.LoadGraphFromFile("./tests/materials/graph/valid/1"));
        s21::Graph minSpanningTree = graphAlgorithms.GetLeastSpanningTree(graph);
        ASSERT_EQ(minSpanningTree.MinSpanningTreeSize(), 150);
    }

    {
        s21::Graph graph;
        ASSERT_TRUE(graph.LoadGraphFromFile("./tests/materials/graph/valid/2"));
        s21::Graph minSpanningTree = graphAlgorithms.GetLeastSpanningTree(graph);
        
        ASSERT_EQ(minSpanningTree.MinSpanningTreeSize(), 33);
        for (s21::Graph::size_type i = 0; i < minSpanningTree.Size(); i++){
        for (s21::Graph::size_type j = 0; j < minSpanningTree.Size(); j++){
            int val = minSpanningTree.at(i, j);
            if (i == 0 && j == 1 && val == 7) ASSERT_TRUE(true);
            else if (i == 1 && j == 0 && val == 7) ASSERT_TRUE(true);
            else if (i == 0 && j == 2 && val == 9) ASSERT_TRUE(true);
            else if (i == 2 && j == 0 && val == 9) ASSERT_TRUE(true);
            else if (i == 3 && j == 4 && val == 6) ASSERT_TRUE(true);
            else if (i == 4 && j == 3 && val == 6) ASSERT_TRUE(true);
            else if (i == 2 && j == 5 && val == 2) ASSERT_TRUE(true);
            else if (i == 5 && j == 2 && val == 2) ASSERT_TRUE(true);
            else if (i == 4 && j == 5 && val == 9) ASSERT_TRUE(true);
            else if (i == 5 && j == 4 && val == 9) ASSERT_TRUE(true);
            else if (val == 0) ASSERT_TRUE(true);
            else ASSERT_TRUE(false);
        }
        }
    }
}

}
