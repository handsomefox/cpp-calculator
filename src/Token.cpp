#include "Token.hpp"

Token::Token(TokenType type, std::string literal)
        : _type(type), _literal(std::move(literal)) {
}

TokenType Token::type() const {
    return _type;
}

std::string Token::literal() const {
    return _literal;
}
