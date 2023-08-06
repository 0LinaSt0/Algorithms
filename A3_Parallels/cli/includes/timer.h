#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace s21{

class Timer{
public:
    Timer() = default;
    Timer(const Timer& other) = delete;
    Timer(Timer&& other) = delete;
    ~Timer() = default;

    Timer& operator=(const Timer& other) = delete;
    Timer& operator=(Timer&& other) = delete;

    void Start();
    void End();
    long long GetDuration();

private:
    std::chrono::steady_clock::time_point start_;
    std::chrono::steady_clock::time_point end_;

};

}

#endif
