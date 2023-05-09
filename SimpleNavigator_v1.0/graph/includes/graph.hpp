#pragma once

namespace s21{

class Graph{
public:
    Graph();
    Graph(const Graph& other);
    Graph(Graph&& other);
    ~Graph();

    Graph& operator=(const Graph& other);
    Graph& operator=(Graph&& other);

private:

};

}
