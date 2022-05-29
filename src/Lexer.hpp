#pragma once

#include <string>
#include <utility>
#include "Token.hpp"

class Lexer {
public:
    explicit Lexer(std::string input);

    Token next_token();

private:
    using tt = TokenType;

    std::string _input;
    int32_t _curr_pos{0};
};
