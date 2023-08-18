#ifndef CLI_SLE_H
#define CLI_SLE_H

#include "cli.h"
#include "../../algorithms/SLE/includes/sle_gaussian.h"

namespace s21{

class CliSle : public CLI{
public:
    CliSle() = default;
    CliSle(const CliSle&) = delete;
    CliSle(CliSle&&) = delete;
    ~CliSle() = default;

    void run();

protected:
    void PrintMenu_() const;

};

}

#endif