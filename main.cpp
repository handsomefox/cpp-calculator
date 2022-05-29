#include <iostream>
#include "src/Token.hpp"
#include "src/Parser.hpp"

void print_tree(const std::string &prefix, const Node *node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix;
        std::cout << (isLeft ? "|---" : "'---");
        std::cout << node->to_string() << std::endl;
        
        print_tree(prefix + (isLeft ? "|   " : "    "), node->left(), true);
        print_tree(prefix + (isLeft ? "|   " : "    "), node->right(), false);
    }
}

void pretty_print_tree(const Node *node) {
    print_tree("", node, false);
}

int main() {
    std::cout << "Enter 'exit' to exit the program" << std::endl;
    while (true) {
        std::string expression;
        std::cout << ">>>";

        std::cin >> expression;
        if (expression == "exit") {
            break;
        }

        auto parser = Parser(expression);
        auto tree = parser.Parse();

        if (!tree) {
            std::cout << "Invalid expression" << std::endl;
            continue;
        }

        std::cout << "Result: " << std::to_string(tree->eval()) << '\n';
        std::cout << "Tree: " << std::endl;
        pretty_print_tree(tree.get());
        std::cout << std::endl;
    }
}
