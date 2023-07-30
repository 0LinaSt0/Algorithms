#pragma once

#include <vector>
#include <ostream>
#include <algorithm>

#include "edge.h"

namespace s21{

class Ant{
public:
    Ant();
    Ant(const Ant& other) = default;
    Ant(Ant&& other) = default;
    ~Ant() = default;

    Ant& operator=(const Ant& other) = default;
    Ant& operator=(Ant&& other) = default;

    const std::vector<int>& GetPath() const;

    bool IsInPath(int vertex) const;

    void AddVertex(int vertex);

    bool IsEnd() const;
    void SetEnd(bool end);

    bool IsSuccess() const;
    void SetSuccess(bool success);

private:
    // List of verteces
    std::vector<int> path_;
    // Is ant in the end of it's way
    bool end_;
    // Is ant's way full
    bool success_;

};

}

std::ostream& operator<<(std::ostream& output, const s21::Ant& ant);
