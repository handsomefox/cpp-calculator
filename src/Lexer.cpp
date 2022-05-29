#include <vector>
#include "Lexer.hpp"

Lexer::Lexer(std::string input) : _input(std::move(input)) {
}

Token Lexer::next_token() {
    if (_curr_pos >= _input.length()) {
        return {tt::Eof, "EOF"};
    }

    char character = _input[_curr_pos];

    auto token = Token();
    switch (character) {
        case '+':
            token = {tt::Plus, "+"};
            break;
        case '-':
            token = {tt::Minus, "-"};
            break;
        case '*':
            token = {tt::Multiply, "*"};
            break;
        case '/':
            token = {tt::Divide, "/"};
            break;
        case '(':
            token = {tt::LParen, "("};
            break;
        case ')':
            token = {tt::RParen, ")"};
            break;
        case '^':
            token = {tt::Power, "^"};
            break;
        case ' ':
            break;
        default:
            if (std::isdigit(character)) {
                std::string number_string{};
                while (std::isdigit(character) || character == '.' || character == '!' && _curr_pos < _input.length()) {
                    number_string += character;
                    character = _input[++_curr_pos];
                }
                return {tt::Number, number_string};
            } else token = {tt::Illegal, "Illegal token"};
            break;
    }
    ++_curr_pos;
    return token;
}
