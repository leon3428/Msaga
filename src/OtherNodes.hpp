#ifndef OTHER_NODES_H
#define OTHER_NODES_H

#include "SyntaxTree.hpp"
#include <vector>
#include "Utils.hpp"

/**
 * @brief <ime_tipa>
 * 
 */
class TypeName : public SyntaxTreeNode {
protected:
    ExprType m_exprType;

public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::TypeName; }
    [[nodiscard]] inline ExprType getExprType() const { return m_exprType; }

    inline void setExprType(ExprType exprType) { m_exprType = exprType; }
};

/**
 * @brief <specifikator_tipa>
 * 
 */
class TypeSpecifier : public SyntaxTreeNode {
protected:
    ExprType m_exprType;

public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::TypeSpecifier; }
    [[nodiscard]] inline ExprType getExprType() const { return m_exprType; }

    inline void setExprType(ExprType exprType) { m_exprType = exprType; }
};

/**
 * @brief <unarni_operator>
 * 
 */
class UnaryOperator : public SyntaxTreeNode {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::UnaryOperator; }
};

/**
 * @brief <list_argumenata>
 * 
 */
class ArgumentList : public SyntaxTreeNode {
protected:
    std::vector<ExprType> m_exprTypes;
public:
    void check() override;

    [[nodiscard]] inline std::vector<ExprType> getExprTypes() const { return m_exprTypes; }
    [[nodiscard]] inline size_t getSize() const { return m_exprTypes.size(); }
    [[nodiscard]] inline ExprType getType(size_t i) const {
        DebugAssert(i >= m_exprTypes.size(), "Index out of range");
        return m_exprTypes[i];
    }
    inline void setType(ExprType exprType, size_t i) {
        DebugAssert(i >= m_exprTypes.size(), "Index out of range");
        m_exprTypes[i] = exprType;
    }


    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::ArgumentList; }
};

#endif // OTHER_NODES_H