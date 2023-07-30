#include "../includes/edge.h"

namespace s21{

int Edge::next_id_ = 0;

Edge::Edge(){
    value = 0;
    pheromone = PHEROMONE_INIT_VALUE;
}

Edge::Edge(double value, double pheromone){
    this->value = value;
    this->pheromone = pheromone;
}

}

bool operator==(const s21::Edge& lhs, const s21::Edge& rhs){
    return lhs.id == rhs.id;
}

bool operator!=(const s21::Edge& lhs, const s21::Edge& rhs){
    return !(lhs == rhs);
}

bool operator==(const s21::Edge& edge, double value){
    return s21::DoubleCompare(edge.value, value);
}

bool operator!=(const s21::Edge& edge, double value){
    return !(edge == value);
}

bool operator==(const s21::Edge& edge, int value){
    return edge == (double) value;
}

bool operator!=(const s21::Edge& edge, int value){
    return !(edge == value);
}

bool operator<(const s21::Edge& lhs, const s21::Edge& rhs){
    return lhs.id < rhs.id;
}

std::istream& operator>>(std::istream& input, s21::Edge& edge){
    edge.pheromone = s21::PHEROMONE_INIT_VALUE;
    return input >> edge.value;
}

std::ostream& operator<<(std::ostream& output, const s21::Edge& edge){
    return output
        << "{ value: " 
        << edge.value 
        << ", pheromone: " 
        << edge.pheromone
        << " }";
}
