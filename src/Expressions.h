#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "SyntaxTree.h"
#include <iostream>
#include "Global.h"

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


/**
 * @brief Node for nonterminal character <primary_expression>
 * 
 */
class PrimaryExpression : public GenericExpression {
public:
    bool check() override;
};

#endif //EXPRESSIONS_H