#include "../includes/graphAlgorithms.hpp"

namespace s21::tests::graph{

TEST(TEST_SUITE_NAME, BreadthFirstSearch1){
    const int size = 10;
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;
    const std::string answ[size] = {
        "1 2 3 4 5 6 7 8 9 10",
        "2 1 3 4 5 6 7 8 9 10",
        "3 1 2 4 5 6 7 8 9 10",
        "4 1 2 3 5 6 7 8 9 10",
        "5 1 2 3 4 6 7 8 9 10",
        "6 1 2 3 4 5 7 8 9 10",
        "7 1 2 3 4 5 6 8 9 10",
        "8 1 2 3 4 5 6 7 9 10",
        "9 1 2 3 4 5 6 7 8 10",
        "10 2 3 4 5 6 7 8 9 1"
    };

    auto vectorToString = [](const std::vector<int>& v){
        std::string str;
        
        for (size_t i = 0; i < v.size(); i++){
            str += std::to_string(v[i] + 1);
            if (i + 1 != v.size()) str += ' ';
        }

        return str;
    };
    
    graph.LoadGraphFromFile(valid_graphs_dir + "14_default_matrix");
    
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
    
    graph.LoadGraphFromFile(valid_graphs_dir + "13_connected");
    
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
    
    graph.LoadGraphFromFile(valid_graphs_dir + "16_directed");
    
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
    
    graph.LoadGraphFromFile(valid_graphs_dir + "17_directed");
    
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
    
    graph.LoadGraphFromFile(valid_graphs_dir + "12_disconnected");
    
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
    
    graph.LoadGraphFromFile(valid_graphs_dir + "19_directed");
    
    for (int i = 0; i < size; i++){
        ASSERT_EQ(vectorToString(graphAlgorithms.BreadthFirstSearch(graph, i)),
                   answ[i]);
    }
}

TEST(TEST_SUITE_NAME, DepthFirstSearch1){
    const int size = 10;
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;
    const std::string answ[size] = {
        "1 2 10 3 4 5 6 7 8 9",
        "2 1 3 4 5 6 7 8 9 10",
        "3 1 2 4 5 6 7 8 9 10",
        "4 1 2 3 5 6 7 8 9 10",
        "5 1 2 3 4 6 7 8 9 10",
        "6 1 2 3 4 5 7 8 9 10",
        "7 1 2 3 4 5 6 8 9 10",
        "8 1 2 3 4 5 6 7 9 10",
        "9 1 2 3 4 5 6 7 8 10",
        "10 2 1 3 4 5 6 7 8 9"
    };

    auto vectorToString = [](const std::vector<int>& v){
        std::string str;
        
        for (size_t i = 0; i < v.size(); i++){
            str += std::to_string(v[i] + 1);
            if (i + 1 != v.size()) str += ' ';
        }

        return str;
    };

    graph.LoadGraphFromFile(valid_graphs_dir + "14_default_matrix");

    for (int i = 0; i < size; i++){
        ASSERT_EQ(vectorToString(graphAlgorithms.DepthFirstSearch(graph, i)),
                   answ[i]);
    }
}

TEST(TEST_SUITE_NAME, DepthFirstSearch2){
    const int size = 6;
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;
    const std::string answ[size] = {
        "1 2 4 5 3 6",
        "2 1 6 5 3 4",
        "3 1 2 4 5 6",
        "4 2 1 6 3 5",
        "5 4 2 1 3 6",
        "6 1 2 4 3 5"
    };

    auto vectorToString = [](const std::vector<int>& v){
        std::string str;
        
        for (size_t i = 0; i < v.size(); i++){
            str += std::to_string(v[i] + 1);
            if (i + 1 != v.size()) str += ' ';
        }

        return str;
    };

    graph.LoadGraphFromFile(valid_graphs_dir + "13_connected");

    for (int i = 0; i < size; i++){
        ASSERT_EQ(vectorToString(graphAlgorithms.DepthFirstSearch(graph, i)),
                   answ[i]);
    }
}

TEST(TEST_SUITE_NAME, DepthFirstSearch3){
    const int size = 6;
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;
    const std::string answ[size] = {
        "1 2 3 6 5 4",
        "2 3 1 4 5 6",
        "3 1 2 4 5 6",
        "4 5 3 1 2 6",
        "5 3 1 2 6 4",
        "6 5 3 1 2 4"
    };

    auto vectorToString = [](const std::vector<int>& v){
        std::string str;
        
        for (size_t i = 0; i < v.size(); i++){
            str += std::to_string(v[i] + 1);
            if (i + 1 != v.size()) str += ' ';
        }

        return str;
    };

    graph.LoadGraphFromFile(valid_graphs_dir + "16_directed");

    for (int i = 0; i < size; i++){
        ASSERT_EQ(vectorToString(graphAlgorithms.DepthFirstSearch(graph, i)),
                   answ[i]);
    }
}

TEST(TEST_SUITE_NAME, DepthFirstSearch4){
    const int size = 8;
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;
    const std::string answ[size] = {
        "1 2 3 4 5 6 7 8",
        "2 3 4 5 6 7 8",
        "3 2 4 5 6 7 8",
        "4 5 6 3 2 7 8",
        "5 6 3 2 4 7 8",
        "6 3 2 4 5 7 8",
        "7 6 3 2 4 5 8",
        "8 6 3 2 4 5 7"
    };

    auto vectorToString = [](const std::vector<int>& v){
        std::string str;
        
        for (size_t i = 0; i < v.size(); i++){
            str += std::to_string(v[i] + 1);
            if (i + 1 != v.size()) str += ' ';
        }

        return str;
    };

    graph.LoadGraphFromFile(valid_graphs_dir + "17_directed");

    for (int i = 0; i < size; i++){
        ASSERT_EQ(vectorToString(graphAlgorithms.DepthFirstSearch(graph, i)),
                   answ[i]);
    }
}

TEST(TEST_SUITE_NAME, DepthFirstSearch5){
    const int size = 8;
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;
    const std::string answ[size] = {
        "1 2 3 4 5 7",
        "2 3 4",
        "3 2 4",
        "4",
        "5 1 2 3 4 7",
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

    graph.LoadGraphFromFile(valid_graphs_dir + "12_disconnected");

    for (int i = 0; i < size; i++){
        ASSERT_EQ(vectorToString(graphAlgorithms.DepthFirstSearch(graph, i)),
                   answ[i]);
    }
}

TEST(TEST_SUITE_NAME, DepthFirstSearch6){
    const int size = 8;
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;
    const std::string answ[size] = {
        "1 2 3 6 4 5 7 8",
        "2 3 6 8 7 4 5",
        "3 4 5 7 6 8",
        "4 5 3 6 8 7",
        "5 3 4 6 8 7",
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

    graph.LoadGraphFromFile(valid_graphs_dir + "19_directed");

    for (int i = 0; i < size; i++){
        ASSERT_EQ(vectorToString(graphAlgorithms.DepthFirstSearch(graph, i)),
                   answ[i]);
    }
}

TEST(TEST_SUITE_NAME, MinimumSpanningTree1){
    s21::GraphAlgorithms graphAlgorithms;
    s21::Graph graph;
    ASSERT_TRUE(graph.LoadGraphFromFile(valid_graphs_dir + "14_default_matrix"));
    s21::Graph minSpanningTree = graphAlgorithms.GetLeastSpanningTree(graph);
    ASSERT_EQ(minSpanningTree.MinSpanningTreeSize(), 76);
}

TEST(TEST_SUITE_NAME, MinimumSpanningTree2){
    s21::GraphAlgorithms graphAlgorithms;
    s21::Graph graph;
    ASSERT_TRUE(graph.LoadGraphFromFile(valid_graphs_dir + "13_connected"));
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
    ASSERT_TRUE(graph.LoadGraphFromFile(valid_graphs_dir + "16_directed"));
    s21::Graph minSpanningTree = graphAlgorithms.GetLeastSpanningTree(graph);
    ASSERT_EQ(minSpanningTree.MinSpanningTreeSize(), 66);
}

TEST(TEST_SUITE_NAME, MinimumSpanningTree4){
    s21::GraphAlgorithms graphAlgorithms;
    s21::Graph graph;
    ASSERT_TRUE(graph.LoadGraphFromFile(valid_graphs_dir + "17_directed"));
    s21::Graph minSpanningTree = graphAlgorithms.GetLeastSpanningTree(graph);
    ASSERT_EQ(minSpanningTree.MinSpanningTreeSize(), 87);
}

TEST(TEST_SUITE_NAME, MinimumSpanningTree5){
    s21::GraphAlgorithms graphAlgorithms;
    s21::Graph graph;
    ASSERT_TRUE(graph.LoadGraphFromFile(valid_graphs_dir + "12_disconnected"));
    try {
        graphAlgorithms.GetLeastSpanningTree(graph);
        ASSERT_TRUE(false);
    } catch (std::exception&) {

    }
}

TEST(TEST_SUITE_NAME, MinimumSpanningTree6){
    s21::GraphAlgorithms graphAlgorithms;
    s21::Graph graph;
    ASSERT_TRUE(graph.LoadGraphFromFile(valid_graphs_dir + "19_directed"));
    s21::Graph minSpanningTree = graphAlgorithms.GetLeastSpanningTree(graph);
    ASSERT_EQ(minSpanningTree.MinSpanningTreeSize(), 70);
}

TEST(TEST_SUITE_NAME, GetShortestPathBetweenVertices1){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile(valid_graphs_dir + "14_default_matrix");
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 0, 3), 20);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 6, 1), 24);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 3, 6), 9);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 4, 7), 9);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 1, 5), 40);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 3, 7), 12);
}

TEST(TEST_SUITE_NAME, GetShortestPathBetweenVertices2){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile(valid_graphs_dir + "13_connected");
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

    graph.LoadGraphFromFile(valid_graphs_dir + "16_directed");
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

    graph.LoadGraphFromFile(valid_graphs_dir + "17_directed");
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

    graph.LoadGraphFromFile(valid_graphs_dir + "12_disconnected");
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

    graph.LoadGraphFromFile(valid_graphs_dir + "19_directed");
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 4, 0), 0);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 5, 3), 0);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 7, 5), 26);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 0, 4), 32);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 2, 6), 20);
    ASSERT_EQ(graphAlgorithms.GetShortestPathBetweenVertices(graph, 2, 1), 0);
}

TEST(TEST_SUITE_NAME, GetShortestPathBetweenAllVertices1){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile(valid_graphs_dir + "14_default_matrix");
    s21::Graph res_graph =
                    graphAlgorithms.GetShortestPathsBetweenAllVertices(graph);

    ASSERT_EQ(res_graph.at(0, 3), 20);
    ASSERT_EQ(res_graph.at(6, 1), 24);
    ASSERT_EQ(res_graph.at(3, 6), 9);
    ASSERT_EQ(res_graph.at(4, 7), 9);
    ASSERT_EQ(res_graph.at(1, 5), 40);
    ASSERT_EQ(res_graph.at(3, 7), 12);
}

TEST(TEST_SUITE_NAME, GetShortestPathBetweenAllVertices2){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile(valid_graphs_dir + "13_connected");
    s21::Graph res_graph =
                    graphAlgorithms.GetShortestPathsBetweenAllVertices(graph);

    ASSERT_EQ(res_graph.at(0, 5), 11);
    ASSERT_EQ(res_graph.at(0, 3), 20);
    ASSERT_EQ(res_graph.at(0, 4), 20);
    ASSERT_EQ(res_graph.at(4, 1), 21);
    ASSERT_EQ(res_graph.at(2, 4), 11);
    ASSERT_EQ(res_graph.at(3, 5), 13);
    ASSERT_EQ(res_graph.at(4, 0), 20);
}

TEST(TEST_SUITE_NAME, GetShortestPathBetweenAllVertices3){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile(valid_graphs_dir + "16_directed");
    s21::Graph res_graph =
                    graphAlgorithms.GetShortestPathsBetweenAllVertices(graph);

    ASSERT_EQ(res_graph.at(4, 1), 74);
    ASSERT_EQ(res_graph.at(2, 4), 47);
    ASSERT_EQ(res_graph.at(1, 5), 38);
    ASSERT_EQ(res_graph.at(5, 3), 38);
    ASSERT_EQ(res_graph.at(5, 0), 79);
    ASSERT_EQ(res_graph.at(5, 4), 30);
}

TEST(TEST_SUITE_NAME, GetShortestPathBetweenAllVertices4){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile(valid_graphs_dir + "17_directed");
    s21::Graph res_graph =
                    graphAlgorithms.GetShortestPathsBetweenAllVertices(graph);

    ASSERT_EQ(res_graph.at(5, 0), 0);
    ASSERT_EQ(res_graph.at(0, 3), 59);
    ASSERT_EQ(res_graph.at(1, 5), 105);
    ASSERT_EQ(res_graph.at(1, 4), 87);
    ASSERT_EQ(res_graph.at(7, 4), 98);
}

TEST(TEST_SUITE_NAME, GetShortestPathBetweenAllVertices5){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile(valid_graphs_dir + "12_disconnected");
    s21::Graph res_graph =
                    graphAlgorithms.GetShortestPathsBetweenAllVertices(graph);

    ASSERT_EQ(res_graph.at(5, 4), 0);
    ASSERT_EQ(res_graph.at(0, 2), 30);
    ASSERT_EQ(res_graph.at(0, 3), 72);
    ASSERT_EQ(res_graph.at(1, 4), 0);
    ASSERT_EQ(res_graph.at(0, 6), 25);
    ASSERT_EQ(res_graph.at(6, 0), 57);
    ASSERT_EQ(res_graph.at(6, 3), 129);
}

TEST(TEST_SUITE_NAME, GetShortestPathBetweenAllVertices6){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile(valid_graphs_dir + "19_directed");
    s21::Graph res_graph =
                    graphAlgorithms.GetShortestPathsBetweenAllVertices(graph);

    ASSERT_EQ(res_graph.at(4, 0), 0);
    ASSERT_EQ(res_graph.at(5, 3), 0);
    ASSERT_EQ(res_graph.at(7, 5), 26);
    ASSERT_EQ(res_graph.at(0, 4), 32);
    ASSERT_EQ(res_graph.at(2, 6), 20);
    ASSERT_EQ(res_graph.at(2, 1), 0);
}

TEST(TEST_SUITE_NAME, ExhaustiveSearch){
    s21::Graph graph;
    s21::GraphAlgorithms graphAlgorithms;

    graph.LoadGraphFromFile(valid_graphs_dir + "13_connected");
    s21::TsmResult tsmResult = graphAlgorithms.ExhaustiveSearch(graph);
    ASSERT_EQ(tsmResult.distance, 48);
    std::cout << std::endl;
}

TEST(TEST_SUITE_NAME, TravelingSalesman){
    const std::string BALD = "\033[1m";
    const std::string DEFAULT = "\033[0m";
    const int algos_count = 3;
    s21::Timer timer;
    s21::GraphAlgorithms graph_algs;
    std::vector<std::string> files = {
        valid_graphs_dir + "01_with_solution",
        valid_graphs_dir + "02_without_solution",
        valid_graphs_dir + "03_without_solution",
        valid_graphs_dir + "04_with_several_solutions_loop",
        valid_graphs_dir + "05_with_solutiom_loop",
        valid_graphs_dir + "06_with_solutiom_loop",
        valid_graphs_dir + "07_connected_without_solution",
        valid_graphs_dir + "08_connected_loop",
        valid_graphs_dir + "09_with_several_soltuions",
        valid_graphs_dir + "10_with_several_soltuions",
        valid_graphs_dir + "11_with_several_soltuions",
        valid_graphs_dir + "12_disconnected",
        valid_graphs_dir + "13_connected",
        valid_graphs_dir + "14_default_matrix",
        valid_graphs_dir + "15_default_matrix",
        valid_graphs_dir + "16_directed",
        valid_graphs_dir + "17_directed",
        valid_graphs_dir + "18_directed",
        valid_graphs_dir + "19_directed",
        valid_graphs_dir + "20_eight_vertices",
        valid_graphs_dir + "21_seven_vertices",
        valid_graphs_dir + "22_ten_vertices",
        valid_graphs_dir + "23_thirteen_vertices",
        valid_graphs_dir + "24_twenty_vertices",
        valid_graphs_dir + "25_sixty_vertices",
        valid_graphs_dir + "26_hundred_vertices"
    };
    
    AlgoPtr algos_methods[algos_count] = {
        &s21::GraphAlgorithms::SolveTravelingSalesmanProblem,
        &s21::GraphAlgorithms::STSPBranchBoundMethodAlgorithm,
        &s21::GraphAlgorithms::ExhaustiveSearch
    };
    std::string algos_names[algos_count] = {
        "Ant algorithm",
        "Branch bound method",
        "Exhaustive search"
    };
    

    for (size_t i = 0; i < files.size(); i++){
        const std::string& file = files.at(i);
        s21::Graph graph;
        ASSERT_TRUE(graph.LoadGraphFromFile(file));
        
        int max;
        if (i == 24 || i == 25) max = 1;
        else if (i == 13 || i == 14 || i == 22 || i == 23) max = 2;
        else max = 3;
        
        std::cout 
            << BALD
            << "Filename: "
            << file
            << DEFAULT
            << std::endl;

        for (int i = 0; i < max; i++){
            timer.Start();
            s21::TsmResult tsm_result = (graph_algs.*algos_methods[i])(graph);
            timer.End();

            std::cout
                << "> "
                << algos_names[i]
                << std::endl
                << tsm_result
                << std::endl
                << timer.GetDuration()
                << " ms"
                << std::endl;
            
            if (i + 1 != algos_count) std::cout << std::endl;
        }

        std::cout
            << BALD
            << "==========================================="
            << DEFAULT
            << std::endl;
    }

}

}
