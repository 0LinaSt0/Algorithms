#include "../includes/graphAlgorithms.hpp"

namespace s21::tests::graph{

TEST(TEST_SUITE_NAME, BreadthFirstSearch1){
    const int size = 11;
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;
    const std::string answ[size] = {
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
    
    for (int i = 0; i < size; i++){
        ASSERT_EQ(vectorToString(graphAlgorithms.BreadthFirstSearch(graph, i)),
                   answ[i]);
    }
}

TEST(TEST_SUITE_NAME, BreadthFirstSearch2){
    const int size = 6;
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;
    const std::string answ[size] = {
        "1 2 3 6 4 5",
        "2 1 3 4 6 5",
        "3 1 2 4 6 5",
        "4 2 3 5 1 6",
        "5 4 6 2 3 1",
        "6 1 3 5 2 4"
    };

    auto vectorToString = [](const std::vector<int>& v){
        std::string str;
        
        for (size_t i = 0; i < v.size(); i++){
            str += std::to_string(v[i] + 1);
            if (i + 1 != v.size()) str += ' ';
        }

        return str;
    };
    
    graph.LoadGraphFromFile("./tests/materials/graph/valid/2");
    
    for (int i = 0; i < size; i++){
        ASSERT_EQ(vectorToString(graphAlgorithms.BreadthFirstSearch(graph, i)),
                   answ[i]);
    }
}

TEST(TEST_SUITE_NAME, BreadthFirstSearch3){
    const int size = 6;
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;
    const std::string answ[size] = {
        "1 2 4 3 5 6",
        "2 3 1 6 4 5",
        "3 1 6 2 4 5",
        "4 5 3 1 6 2",
        "5 3 4 1 6 2",
        "6 5 3 4 1 2"
    };

    auto vectorToString = [](const std::vector<int>& v){
        std::string str;
        
        for (size_t i = 0; i < v.size(); i++){
            str += std::to_string(v[i] + 1);
            if (i + 1 != v.size()) str += ' ';
        }

        return str;
    };
    
    graph.LoadGraphFromFile("./tests/materials/graph/valid/3");
    
    for (int i = 0; i < size; i++){
        ASSERT_EQ(vectorToString(graphAlgorithms.BreadthFirstSearch(graph, i)),
                   answ[i]);
    }
}

TEST(TEST_SUITE_NAME, BreadthFirstSearch4){
    const int size = 8;
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;
    const std::string answ[size] = {
        "1 2 5 3 6 4 7 8",
        "2 3 4 5 6 7 8",
        "3 2 4 5 6 7 8",
        "4 5 6 3 7 2 8",
        "5 6 3 7 2 4 8",
        "6 3 7 2 4 8 5",
        "7 6 8 3 2 4 5",
        "8 6 3 7 2 4 5"
    };

    auto vectorToString = [](const std::vector<int>& v){
        std::string str;
        
        for (size_t i = 0; i < v.size(); i++){
            str += std::to_string(v[i] + 1);
            if (i + 1 != v.size()) str += ' ';
        }

        return str;
    };
    
    graph.LoadGraphFromFile("./tests/materials/graph/valid/4");
    
    for (int i = 0; i < size; i++){
        ASSERT_EQ(vectorToString(graphAlgorithms.BreadthFirstSearch(graph, i)),
                   answ[i]);
    }
}

TEST(TEST_SUITE_NAME, BreadthFirstSearch5){
    const int size = 8;
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;
    const std::string answ[size] = {
        "1 2 5 7 3 4",
        "2 3 4",
        "3 2 4",
        "4",
        "5 1 2 7 3 4",
        "6 4",
        "7 5 1 2 3 4",
        "8"
    };

    auto vectorToString = [](const std::vector<int>& v){
        std::string str;
        
        for (size_t i = 0; i < v.size(); i++){
            str += std::to_string(v[i] + 1);
            if (i + 1 != v.size()) str += ' ';
        }

        return str;
    };
    
    graph.LoadGraphFromFile("./tests/materials/graph/valid/5");
    
    for (int i = 0; i < size; i++){
        ASSERT_EQ(vectorToString(graphAlgorithms.BreadthFirstSearch(graph, i)),
                   answ[i]);
    }
}

TEST(TEST_SUITE_NAME, BreadthFirstSearch6){
    const int size = 8;
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;
    const std::string answ[size] = {
        "1 2 8 3 4 7 6 5",
        "2 3 4 6 5 8 7",
        "3 4 6 5 8 7",
        "4 5 3 7 6 8",
        "5 3 7 4 6 8",
        "6 8 7",
        "7 6 8",
        "8 7 6"
    };

    auto vectorToString = [](const std::vector<int>& v){
        std::string str;
        
        for (size_t i = 0; i < v.size(); i++){
            str += std::to_string(v[i] + 1);
            if (i + 1 != v.size()) str += ' ';
        }

        return str;
    };
    
    graph.LoadGraphFromFile("./tests/materials/graph/valid/6");
    
    for (int i = 0; i < size; i++){
        ASSERT_EQ(vectorToString(graphAlgorithms.BreadthFirstSearch(graph, i)),
                   answ[i]);
    }
}

TEST(TEST_SUITE_NAME, MinimumSpanningTree1){
    s21::GraphAlgorithms graphAlgorithms;
    s21::Graph graph;
    ASSERT_TRUE(graph.LoadGraphFromFile("./tests/materials/graph/valid/1"));
    s21::Graph minSpanningTree = graphAlgorithms.GetLeastSpanningTree(graph);
    ASSERT_EQ(minSpanningTree.MinSpanningTreeSize(), 150);
}

TEST(TEST_SUITE_NAME, MinimumSpanningTree2){
    s21::GraphAlgorithms graphAlgorithms;
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

TEST(TEST_SUITE_NAME, MinimumSpanningTree3){
    s21::GraphAlgorithms graphAlgorithms;
    s21::Graph graph;
    ASSERT_TRUE(graph.LoadGraphFromFile("./tests/materials/graph/valid/3"));
    s21::Graph minSpanningTree = graphAlgorithms.GetLeastSpanningTree(graph);
    ASSERT_EQ(minSpanningTree.MinSpanningTreeSize(), 66);
}

TEST(TEST_SUITE_NAME, MinimumSpanningTree4){
    s21::GraphAlgorithms graphAlgorithms;
    s21::Graph graph;
    ASSERT_TRUE(graph.LoadGraphFromFile("./tests/materials/graph/valid/4"));
    s21::Graph minSpanningTree = graphAlgorithms.GetLeastSpanningTree(graph);
    ASSERT_EQ(minSpanningTree.MinSpanningTreeSize(), 87);
}

TEST(TEST_SUITE_NAME, MinimumSpanningTree5){
    s21::GraphAlgorithms graphAlgorithms;
    s21::Graph graph;
    ASSERT_TRUE(graph.LoadGraphFromFile("./tests/materials/graph/valid/5"));
    try {
        graphAlgorithms.GetLeastSpanningTree(graph);
        ASSERT_TRUE(false);
    } catch (std::exception&) {

    }
}

TEST(TEST_SUITE_NAME, MinimumSpanningTree6){
    s21::GraphAlgorithms graphAlgorithms;
    s21::Graph graph;
    ASSERT_TRUE(graph.LoadGraphFromFile("./tests/materials/graph/valid/6"));
    s21::Graph minSpanningTree = graphAlgorithms.GetLeastSpanningTree(graph);
    ASSERT_EQ(minSpanningTree.MinSpanningTreeSize(), 70);
}

TEST(TEST_SUITE_NAME, GetShortestPathBetweenVertices1){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile("./tests/materials/graph/valid/1");
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 0, 3), 20);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 6, 1), 72);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 3, 6), 92);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 4, 7), 9);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 1, 5), 40);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 3, 7), 12);
}

TEST(TEST_SUITE_NAME, GetShortestPathBetweenVertices2){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile("./tests/materials/graph/valid/2");
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 0, 5), 11);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 0, 3), 20);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 0, 4), 20);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 4, 1), 21);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 4, 1), 21);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 2, 4), 11);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 3, 5), 13);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 4, 0), 20);
}

TEST(TEST_SUITE_NAME, GetShortestPathBetweenVertices3){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile("./tests/materials/graph/valid/3");
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 4, 1), 74);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 2, 4), 47);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 1, 5), 38);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 5, 3), 38);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 5, 0), 79);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 5, 4), 30);
}

TEST(TEST_SUITE_NAME, GetShortestPathBetweenVertices4){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile("./tests/materials/graph/valid/4");
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 5, 0), 0);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 0, 3), 59);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 1, 5), 105);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 1, 4), 87);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 5, 0), 0);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 7, 4), 98);
}

TEST(TEST_SUITE_NAME, GetShortestPathBetweenVertices5){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile("./tests/materials/graph/valid/5");
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 5, 4), 0);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 0, 2), 30);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 0, 3), 72);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 1, 4), 0);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 0, 6), 25);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 6, 0), 57);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 6, 3), 129);
}

TEST(TEST_SUITE_NAME, GetShortestPathBetweenVertices6){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile("./tests/materials/graph/valid/6");
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 4, 0), 0);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 5, 3), 0);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 7, 5), 26);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 0, 4), 32);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 2, 6), 20);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 2, 1), 0);
}

TEST(TEST_SUITE_NAME, ExhaustiveSearch){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile("./tests/materials/graph/valid/2");
    s21::TsmResult tsmResult = graphAlgorithms.ExhaustiveSearch(graph);
    ASSERT_EQ(tsmResult.distance, 48);
    std::cout << std::endl;
}

}
