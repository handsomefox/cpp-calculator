#include "Parser.hpp"

#include <utility>
#include <vector>
#include <iostream>

Parser::Parser(std::string expression) : _expr(std::move(expression)) {
    _expr.erase(std::remove_if(_expr.begin(), _expr.end(), std::isspace), _expr.end());
}

void Parser::advance() {
    _curr_token = _curr_pos == _tokens.size() ? nullptr : &_tokens[_curr_pos++];
}

std::unique_ptr<Node> Parser::Parse() {
    auto lexer = Lexer(_expr);

    _tokens.reserve(_expr.length());
    for (auto token = lexer.next_token(); token.type() != tt::Eof; token = lexer.next_token()) {
        if (token.type() == tt::Illegal) {
            return nullptr;
        }
        _tokens.emplace_back(token);
    }

    // Checks for the implicit *
    // In case the input is 2(2+2), this will interpret the input as 2*(2+2)
    for (auto i = 1; i < _tokens.size(); ++i) {
        auto previous = _tokens[i - 1];
        auto current = _tokens[i];
        if (current.type() == tt::LParen && previous.type() == tt::Number) {
            _tokens.insert(_tokens.begin() + i, Token(tt::Multiply, "*"));
        }
    }

    std::cout << "Evaluated expression: ";
    for (const auto &token: _tokens) {
        std::cout << token.literal() << ' ';
    }
    std::cout << '\n';

    advance();
    if (!_curr_token) {
        return nullptr;
    }

    return expr();
}

std::unique_ptr<Node> Parser::expr() {
    auto lhs = term();

    while (_curr_token &&
           (_curr_token->type() == tt::Plus ||
            _curr_token->type() == tt::Minus)) {
        if (_curr_token->type() == tt::Plus) {
            advance();
            auto rhs = term();

            if (lhs && rhs) {
                lhs = std::make_unique<OperationNode>(OperationNode(op::Plus, std::move(lhs), std::move(rhs)));
            } else return nullptr; // invalid expr

        } else if (_curr_token->type() == tt::Minus) {
            advance();
            auto rhs = term();

            if (lhs && rhs) {
                lhs = std::make_unique<OperationNode>(OperationNode(op::Minus, std::move(lhs), std::move(rhs)));
            } else return nullptr; // invalid expr
        }
    }
    return lhs;
}

std::unique_ptr<Node> Parser::term() {
    auto lhs = factor();

    while (_curr_token &&
           (_curr_token->type() == tt::Multiply ||
            _curr_token->type() == tt::Divide ||
            _curr_token->type() == tt::Power)) {

        if (_curr_token->type() == tt::Multiply) {
            advance();
            auto rhs = factor();

            if (lhs && rhs) {
                lhs = std::make_unique<OperationNode>(op::Multiply, std::move(lhs), std::move(rhs));
            } else return nullptr; // invalid expr
        } else if (_curr_token->type() == tt::Divide) {
            advance();
            auto rhs = factor();

            if (lhs && rhs) {
                lhs = std::make_unique<OperationNode>(op::Divide, std::move(lhs), std::move(rhs));
            } else return nullptr; // invalid expr
        } else if (_curr_token->type() == tt::Power) {
            advance();
            auto rhs = factor();

            if (lhs && rhs) {
                lhs = std::make_unique<OperationNode>(op::Power, std::move(lhs), std::move(rhs));
            } else return nullptr; // invalid expr
        }
    }
    return lhs;
}

std::unique_ptr<Node> Parser::factor() {
    if (!_curr_token) {
        return nullptr;
    }

    auto t = _curr_token;
    if (t->type() == tt::LParen) {
        advance();
        auto result = expr();

        if (_curr_token && _curr_token->type() != tt::RParen || !_curr_token) {
            return nullptr;
        }

        advance();
        return result;
    }

    if (t->type() == tt::Number) {
        advance();
        return std::make_unique<NumericNode>(NumericNode(t->literal()));
    }
    return nullptr;
}
