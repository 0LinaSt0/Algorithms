#ifndef TEST_ASSERT_H
#define TEST_ASSERT_H

#include <string>
#include <iostream>

namespace s21::test{

void Assert(
    const std::string& file,
    const int line,
    bool condition
);

}

#endif
