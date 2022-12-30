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
    ExprType m_exprType;
    bool m_isLValue;

public:
    [[nodiscard]] inline ExprType getExprType() const { return m_exprType; }
    [[nodiscard]] inline bool isLValue() const { return m_isLValue; }

    inline void setExprType(ExprType exprType) { m_exprType = exprType; }
    inline void setLValue(bool LValue) { m_isLValue = LValue; }
};

/**
 * @brief <primarni_izraz>
 * 
 */
class PrimaryExpression : public GenericExpression {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::PrimaryExpression; }
};

/**
 * @brief <izraz>
 * 
 */
class Expression : public GenericExpression {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::Expression; }
};

/**
 * @brief <izraz_pridruzivanja>
 * 
 */
class AssignmentExpression : public GenericExpression {
protected:
    int m_characterArrayLength;
public:
    void check() override;

    [[nodiscard]] inline bool isCharacterArray() const { return m_characterArrayLength >= 0; }
    [[nodiscard]] inline size_t getCharacterArrayLength() const { return m_characterArrayLength; }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::AssignmentExpression; }
    inline void setCharacterArrayLength(int length) { m_characterArrayLength = length; }
};

/**
 * @brief <log_ili_izraz>
 * 
 */
class LogicalOrExpression : public GenericExpression {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LogicalOrExpression; }
};

/**
 * @brief <log_i_izraz>
 * 
 */
class LogicalAndExpression : public GenericExpression {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LogicalAndExpression; }
};


/**
 * @brief <postfiks_izraz>
 * 
 */
class PostfixExpression : public GenericExpression {
private:
	Msaga::FunctionType *m_functionType = nullptr;

public:
	PostfixExpression() = default;
	void check() override;

	[[nodiscard]] inline Msaga::FunctionType* getFunctionType() const { return m_functionType; }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::PostfixExpression; }
};


/**
 * @brief <bin_ili_izraz>
 * 
 */
class BitwiseOrExpression : public GenericExpression {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::BitwiseOrExpression; }
};

/**
 * @brief <bin_xili_izraz>
 * 
 */
class BitwiseXorExpression : public GenericExpression {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::BitwiseXorExpression; }
};

/**
 * @brief <bin_i_izraz>
 * 
 */
class BitwiseAndExpression : public GenericExpression {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::BitwiseAndExpression; }
};

/**
 * @brief <jednakosti_izraz>
 * 
 */
class EqualsExpression : public GenericExpression {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::EqualsExpression; }
};

/**
 * @brief <odnosni_izraz>
 * 
 */
class ComparisonExpression : public GenericExpression {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::ComparisonExpression; }
};

/**
 * @brief <aditivni_izraz>
 * 
 */
class AdditiveExpression : public GenericExpression {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::AdditiveExpression; }
};

/**
 * @brief <multiplikativni_izraz>
 * 
 */
class MultiplicativeExpression : public GenericExpression {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::MultiplicativeExpression; }
};

/**
 * @brief <cast_izraz>
 * 
 */
class CastExpression : public GenericExpression {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::CastExpression; }
};

/**
 * @brief <unarni_izraz>
 * 
 */
class UnaryExpression : public GenericExpression {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::UnaryExpression; }
};

#endif //EXPRESSIONS_H