#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include "SyntaxTree.h"
#include <iostream>

/**
 * @brief All other expression classes should be based on this class
 * 
 */
class GenericExpression : public SyntaxTreeNode {
protected:
    std::string m_exprType = "";
    bool m_isLValue = false;

public:
    GenericExpression() = default;
    GenericExpression(const std::string &exprType, bool isLValue);

    [[nodiscard]] inline std::string getExprType() const noexcept { return m_exprType; }
    [[nodiscard]] inline bool isLValue() const noexcept { return m_isLValue; }
};


/**
 * @brief Node for nonterminal character <primary_expression>
 * 
 */
class PrimaryExpression : public GenericExpression {
public:
    PrimaryExpression() = default;
    PrimaryExpression(const std::string &exprType, bool isLValue);

    bool check() override;
};

#endif //EXPRESSIONS_H