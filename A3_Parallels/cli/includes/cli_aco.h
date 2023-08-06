#ifndef CLI_ACO_H
#define CLI_ACO_H

#include "cli.h"
#include "../../algorithms/ACO/includes/aco_multi.h"
#include "../../algorithms/ACO/includes/aco_single.h"

namespace s21{

class CliAco : public CLI{
public:
    CliAco() = default;
    CliAco(const CliAco&) = delete;
    CliAco(CliAco&&) = delete;
    ~CliAco() = default;

    void run();

protected:
    void PrintMenu_() const;

};

}

#endif
