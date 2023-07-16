#include "../includes/cli.h"

namespace s21{

const std::string CLI::GREEN_COLOR_ = "\033[0;32m";
const std::string CLI::CYAN_COLOR_ = "\033[1;36m";
const std::string CLI::BLUE_COLOR_ = "\033[0;34m";
const std::string CLI::DEFAULT_COLOR_ = "\033[0m";

const std::string CLI::PROGRAM_PROMT_COLOR_ = CLI::GREEN_COLOR_;
const std::string CLI::USER_PROMT_COLOR_ = CLI::GREEN_COLOR_;
const std::string CLI::MSG_COLOR_ = CLI::CYAN_COLOR_;
const std::string CLI::IDX_COLOR_ = CLI::CYAN_COLOR_;

const std::string CLI::PROGRAM_PROMT_ = CLI::PROGRAM_PROMT_COLOR_ +
                                        "SN: " +
                                        CLI::DEFAULT_COLOR_;
const std::string CLI::USER_PROMT_ = CLI::USER_PROMT_COLOR_ +
                                        "> " +
                                        CLI::DEFAULT_COLOR_;
const std::string CLI::SEPARATOR_ = CLI::PROGRAM_PROMT_COLOR_ +
                                    "><><><><><><><><><><><><><><><><><><><><" +
                                    CLI::DEFAULT_COLOR_;

CLI::CliException::CliException(const std::string& msg)
    : ::s21::Exception(msg) {

}

std::string CLI::CliException::GetMessage() const{
    return ::s21::Exception::msg_;
}

void CLI::PrintMsg_(const std::string& msg) const{
    std::cout 
        << std::endl 
        << SEPARATOR_
        << std::endl
        << std::endl
        << PROGRAM_PROMT_ 
        << MSG_COLOR_
        << msg 
        << DEFAULT_COLOR_
        << std::endl;
}

std::string CLI::ReadLine_() const{
    std::string line;

    std::cout << USER_PROMT_;
    std::getline(std::cin, line);

    return line;
}

int CLI::ReadNum() const{
    try {
        return std::stoi(ReadLine_());
    } catch (std::invalid_argument& e){
        throw CliException(std::string(e.what()));
    }
}

void CLI::TrimLine_(std::string& line) const{
    auto lambda = [](char c){ return !std::isspace(c); };
    std::string::const_iterator iter = std::find_if(
        line.begin(),
        line.end(),
        lambda
    );
    if (iter != line.end()) line.erase(line.begin(), iter);

    std::string::const_reverse_iterator riter = std::find_if(
        line.rbegin(),
        line.rend(),
        lambda
    );
    if (riter != line.rend()) {
        std::string::const_iterator rriter(riter.base());
        line.erase(rriter, line.end());
    }
}

}
