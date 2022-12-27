#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "SyntaxTree.hpp"
#include <iostream>
#include <forward_list>

/**
 * @brief All other command classes should be based on this class
 * 
 */
class GenericDeclaration : public SyntaxTreeNode {
protected:
    ExprType m_exprType;

public:
    [[nodiscard]] inline ExprType getExprType() const { return m_exprType; }

    inline void setExprType(ExprType exprType) { m_exprType = exprType; }
};

/**
 * @brief <definicija funkcije>
 * 
 */
class FunctionDefinition : public GenericDeclaration {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::FunctionDefinition; }
};

/**
 * @brief <lista_parametara>
 * 
 */
class ParameterList : public GenericDeclaration {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::ParameterList; }
};

/**
 * @brief <deklaracija_parametara>
 * 
 */
class ParameterDeclaration : public GenericDeclaration {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::ParameterDeclaration; }
};

/**
 * @brief <lista_deklaracija>
 * 
 */
class DeclarationList : public GenericDeclaration {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::DeclarationList; }
};

/**
 * @brief <deklaracija>
 * 
 */
class Declaration : public GenericDeclaration {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::Declaration; }
};

/**
 * @brief <lista_init_deklaratora>
 * 
 */
class DeclaratorInitList : public GenericDeclaration {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::DeclaratorInitList; }
};

/**
 * @brief <init_deklarator>
 * 
 */
class InitDeclarator : public GenericDeclaration {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::InitDeclarator; }
};

/**
 * @brief <izravni_deklarator>
 * 
 */
class DirectDeclarator : public GenericDeclaration {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::DirectDeclarator; }
};

/**
 * @brief <inicijalizator>
 * 
 */
class Initializator : public GenericDeclaration {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::Initializator; }
};

/**
 * @brief <lista_izraza_pridruzivanja>
 * 
 */
class JoinExpressionList : public GenericDeclaration {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::JoinExpressionList; }
};

#endif //DECLARATIONS_H