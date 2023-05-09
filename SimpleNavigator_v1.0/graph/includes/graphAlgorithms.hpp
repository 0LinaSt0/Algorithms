#pragma once

namespace s21{

class GraphAlgorithms{
public:
    GraphAlgorithms();
    GraphAlgorithms(const GraphAlgorithms& other);
    GraphAlgorithms(GraphAlgorithms&& other);
    ~GraphAlgorithms();

    GraphAlgorithms& operator=(const GraphAlgorithms& other);
    GraphAlgorithms& operator=(GraphAlgorithms&& other);

private:

};

}
