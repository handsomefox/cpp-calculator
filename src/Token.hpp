#pragma once

#include <string>
#include <utility>

enum class TokenType {
    Number,
    Plus,
    Minus,
    Multiply,
    Divide,
    Power,
    LParen,
    RParen,
    Eof,
    Illegal
};

class Token {
public:
    Token(TokenType type, std::string literal);

    [[nodiscard]] TokenType type() const;

    [[nodiscard]] std::string literal() const;

    Token() = default;

private:
    TokenType _type{};
    std::string _literal{};
};
