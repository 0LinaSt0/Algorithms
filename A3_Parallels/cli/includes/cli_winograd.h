#ifndef CLI_WINOGRAD_H
#define CLI_WINOGRAD_H

#include <random>

#include "cli.h"
#include "../../algorithms/Winograd/includes/winograd.h"

namespace s21{

class CliWinograd : public CLI{
public:
    CliWinograd() = default;
    CliWinograd(const CliWinograd&) = delete;
    CliWinograd(CliWinograd&&) = delete;
    ~CliWinograd() = default;

    void run();

private:
    std::pair<Matrix<double>, Matrix<double>> random_mtrx_() const;
    std::pair<Matrix<double>, Matrix<double>> load_mtrx_() const;

};

}

#endif
