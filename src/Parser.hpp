#pragma once

#include <vector>
#include "Token.hpp"
#include "Lexer.hpp"
#include "Node.hpp"

class Parser {
public:
    explicit Parser(std::string expression);

    std::unique_ptr<Node> Parse();

private:
    Parser() = default;

    void advance();

    std::unique_ptr<Node> expr();

    std::unique_ptr<Node> term();

    std::unique_ptr<Node> factor();

private:
    using op = OperationType;
    using tt = TokenType;

    std::string _expr;
    std::vector<Token> _tokens;
    Token *_curr_token{};
    size_t _curr_pos{0};
};
