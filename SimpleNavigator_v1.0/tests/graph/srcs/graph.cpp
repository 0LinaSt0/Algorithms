#include "../includes/graph.hpp"

namespace s21::tests::graph{

TEST(TEST_SUITE_NAME, LOAD_VALID_FILE_1){
    using size_type = s21::Graph::size_type;
    const std::string file_name = "./tests/materials/graph/valid/1";

    s21::Graph graph;
    std::ifstream file_stream;
    file_stream.open(file_name);

    ASSERT_TRUE(file_stream.is_open());
    ASSERT_TRUE(graph.LoadGraphFromFile(file_name));

    size_type size;
    file_stream >> size;
    ASSERT_EQ(size, graph.Size());
    for (size_type i = 0; i < size; i++){
    for (size_type j = 0; j < size; j++){
        int value;
        file_stream >> value;
        ASSERT_EQ(value, graph.at(i, j));
    }
    }
}

TEST(TEST_SUITE_NAME, LOAD_INVALID_FILES){
    s21::Graph graph;

    ASSERT_FALSE(graph.LoadGraphFromFile("bad-file-name"));
    ASSERT_FALSE(graph.LoadGraphFromFile("./tests/materials/graph/invalid/1"));
    ASSERT_FALSE(graph.LoadGraphFromFile("./tests/materials/graph/invalid/2"));
    ASSERT_FALSE(graph.LoadGraphFromFile("./tests/materials/graph/invalid/3"));
    ASSERT_FALSE(graph.LoadGraphFromFile("./tests/materials/graph/invalid/4"));
    ASSERT_FALSE(graph.LoadGraphFromFile("./tests/materials/graph/invalid/5"));
    ASSERT_FALSE(graph.LoadGraphFromFile("./tests/materials/graph/invalid/6"));
}

}
