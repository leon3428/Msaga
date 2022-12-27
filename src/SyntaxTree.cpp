#include "SyntaxTree.hpp"
#include <iostream>

void SyntaxTreeNode::m_errorHandler() {
    std::cout << "error" << std::endl;
    exit(1);
}