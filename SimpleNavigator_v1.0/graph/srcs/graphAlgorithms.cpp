#include "../includes/graphAlgorithms.hpp"

namespace s21{

GraphAlgorithms::GraphAlgorithms(){

}
GraphAlgorithms::GraphAlgorithms(const GraphAlgorithms& other){
    (void)other;
}
GraphAlgorithms::GraphAlgorithms(GraphAlgorithms&& other){
    (void)other;
}
GraphAlgorithms::~GraphAlgorithms(){

}

GraphAlgorithms& GraphAlgorithms::operator=(const GraphAlgorithms& other){
    (void)other;
    return *this;
}
GraphAlgorithms& GraphAlgorithms::operator=(GraphAlgorithms&& other){
    (void)other;
    return *this;
}

}
