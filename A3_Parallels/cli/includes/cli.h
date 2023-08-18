#ifndef CLI_H
#define CLI_H

#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "timer.h"
#include "../../utils/includes/exception.h"

namespace s21{

class CLI{
public:
    CLI() = default;
    CLI(const CLI&) = delete;
    CLI(CLI&&) = delete;
    virtual ~CLI() = default;

    CLI& operator=(const CLI&) = delete;
    CLI& operator=(CLI&&) = delete;

    /**
     * Main method to start CLI.
    */
    virtual void run() = 0;

protected:
    class CliException : public ::s21::Exception{
    public:
        CliException() = delete;
        CliException(const std::string& msg);
        CliException(CliException&&) = delete;
        ~CliException() = default;

        CliException& operator=(const CliException&) = delete;
        CliException& operator=(CliException&&) = delete;

        std::string GetMessage() const;
    };

    // Available raw colors
    const static std::string GREEN_COLOR_;
    const static std::string CYAN_COLOR_;
    const static std::string BLUE_COLOR_;
    const static std::string DEFAULT_COLOR_;
    
    // Specified colors
    const static std::string PROGRAM_PROMT_COLOR_;
    const static std::string USER_PROMT_COLOR_;
    const static std::string MSG_COLOR_;
    const static std::string IDX_COLOR_;

    // Constant lines
    const static std::string PROGRAM_PROMT_;
    const static std::string USER_PROMT_;
    const static std::string SEPARATOR_;

    /**
     * Print message with awesome promt.
    */
    void PrintMsg_(const std::string& msg) const;
    /**
     * @return line entered by user.
    */
    std::string ReadLine_() const;
    /**
     * @return number entered by user.
     * @throw CliException on invalid input.
    */
    int ReadNum_() const;

    /**
     * Remove white spaces from the start and end
     * of input line.
    */
    void TrimLine_(std::string& line) const;

};

}

#endif
