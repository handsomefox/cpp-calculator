#pragma once

#include <string>
#include <memory>
#include <cmath>

#include "Token.hpp"

enum class OperationType {
    Plus,
    Minus,
    Multiply,
    Divide,
    Power,
};

class Node {
public:
    [[nodiscard]] virtual double eval() const = 0;

    [[nodiscard]] virtual std::string to_string() const = 0;

    [[nodiscard]] virtual Node *left() const = 0;

    [[nodiscard]] virtual Node *right() const = 0;

    virtual ~Node() = default;

protected:
    Node() = default;
};

class NumericNode : public Node {
public:
    explicit NumericNode(std::string number_string);

    [[nodiscard]] double eval() const override;

    [[nodiscard]] std::string to_string() const override;

    [[nodiscard]] Node *left() const override { return nullptr; }

    [[nodiscard]] Node *right() const override { return nullptr; }

private:
    double _value;
};

class OperationNode : public Node {
public:
    OperationNode(OperationType op_type, std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs);

    [[nodiscard]] double eval() const override;

    [[nodiscard]] std::string to_string() const override;

    [[nodiscard]] Node *left() const override { return _lhs.get(); }

    [[nodiscard]] Node *right() const override { return _rhs.get(); }

private:
    using op = OperationType;

    OperationType _type;
    std::unique_ptr<Node> _lhs, _rhs;
};
