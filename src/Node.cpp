#include "Node.hpp"

#include <utility>

OperationNode::OperationNode(OperationType op_type, std::unique_ptr<Node> lhs, std::unique_ptr<Node> rhs)
        : _type(op_type), _lhs(std::move(lhs)), _rhs(std::move(rhs)) {
}

double OperationNode::eval() const {
    // TODO: Maybe return an optional here, instead of having zeroes.
    double left_value = _lhs ? _lhs->eval() : 0;
    double right_value = _rhs ? _rhs->eval() : 0;

    switch (_type) {
        case op::Plus:
            return left_value + right_value;
        case op::Minus:
            return left_value - right_value;
        case op::Multiply:
            return left_value * right_value;
        case op::Divide:
            return left_value / right_value;
        case op::Power:
            return std::pow(left_value, right_value);
    }
}

std::string OperationNode::to_string() const {
    switch (_type) {
        case op::Plus:
            return "+";
        case op::Minus:
            return "-";
        case op::Multiply:
            return "*";
        case op::Divide:
            return "/";
        case op::Power:
            return "^";
    }
}

double NumericNode::eval() const {
    return _value;
}

static double factorial(double n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}

NumericNode::NumericNode(std::string number_string) {
    double number = std::stod(number_string);

    if (number_string.length() > 1) {
        if (number_string[number_string.length() - 1] == '!') {
            number_string.pop_back();
            number = factorial(std::stoi(number_string));
        }
    }
    _value = number;
}

std::string NumericNode::to_string() const {
    return std::to_string(_value);
}
