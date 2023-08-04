#pragma once

#include <iostream>

#include "../../../utils/includes/utils.h"

namespace s21{

const double PHEROMONE_INIT_VALUE = 0.5;

class Edge{
public:
    Edge();
    Edge(int value);
    Edge(double value);
    Edge(double value, double pheromone);
    Edge(const Edge& other) = default;
    Edge(Edge&& other) = default;
    ~Edge() = default;

    Edge& operator=(const Edge& other) = default;
    Edge& operator=(Edge&& other) = default;

    const int id = next_id_++;
    double value;
    double pheromone;

private:
    static int next_id_;

};

}

bool operator==(const s21::Edge& lhs, const s21::Edge& rhs);
bool operator!=(const s21::Edge& lhs, const s21::Edge& rhs);
bool operator==(const s21::Edge& edge, double value);
bool operator!=(const s21::Edge& edge, double value);
bool operator==(const s21::Edge& edge, int value);
bool operator!=(const s21::Edge& edge, int value);
bool operator<(const s21::Edge& lhs, const s21::Edge& rhs);

std::istream& operator>>(std::istream& input, s21::Edge& edge);
std::ostream& operator<<(std::ostream& output, const s21::Edge& edge);
