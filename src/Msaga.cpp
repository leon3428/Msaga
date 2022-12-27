#include <iostream>
#include "Expressions.hpp"
#include "Leafs.hpp"

int main() {
    
    std::cout << "Hello World" << std::endl;

    PrimaryExpression pExpr;
    pExpr.addChild<LeafIdn>();
    
    pExpr.check();
    return 0;
}