#include "../includes/ant.h"

namespace s21{

Ant::Ant(){
    end_ = false;
    success_ = false;
}

const std::vector<int>& Ant::GetPath() const{
    return path_;
}

bool Ant::IsInPath(int vertex) const{
    return std::find(path_.begin(), path_.end(), vertex) != path_.end();
}

void Ant::AddVertex(int vertex){
    path_.push_back(vertex);
}

bool Ant::IsEnd() const{
    return end_;
}

void Ant::SetEnd(bool end){
    end_ = end;
}

bool Ant::IsSuccess() const{
    return success_;
}

void Ant::SetSuccess(bool success){
    success_ = success;
}

}

std::ostream& operator<<(std::ostream& output, const s21::Ant& ant){
    return output << ant.GetPath();
}
