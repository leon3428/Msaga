#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "SyntaxTree.hpp"
#include <iostream>
#include <forward_list>

/**
 * @brief All other expression classes should be based on this class
 * 
 */
class GenericExpression : public SyntaxTreeNode {
protected:
    std::forward_list<PrimitiveExprType> m_exprType;
    bool m_isLValue = false;

public:
    [[nodiscard]] inline std::forward_list<PrimitiveExprType> getExprType() const noexcept { return m_exprType; }
    [[nodiscard]] inline bool isLValue() const noexcept { return m_isLValue; }
};


class PrimaryExpression : public GenericExpression {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::PrimaryExpression; }
};





#endif //EXPRESSIONS_H