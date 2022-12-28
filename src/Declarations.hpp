#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "SyntaxTree.hpp"
#include <iostream>
#include <forward_list>
#include <vector>

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
private:
	Msaga::FunctionType *m_functionType = nullptr;
	SyntaxTreeNode *m_insideLoop = nullptr;

public:
	FunctionDefinition() = default;
	inline void setFunctionType(Msaga::FunctionType *functionType) { m_functionType = functionType; }
	void setInsideLoop(SyntaxTreeNode* insideLoop) { m_insideLoop = insideLoop; }
	SyntaxTreeNode* isInsideLoop() { return m_insideLoop; }
    void check() override;

	[[nodiscard]] inline Msaga::FunctionType* getFunctionType() const { return m_functionType; }
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
private:
	ExprType m_ntype;

public:
    void check() override;
	void setNtype(ExprType ntype) { m_ntype = ntype; }
	ExprType getNtype() { return m_ntype; }

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::DeclaratorInitList; }
};

/**
 * @brief <init_deklarator>
 * 
 */
class InitDeclarator : public GenericDeclaration {
private:
	ExprType m_ntype;

public:
    void check() override;
	void setNtype(ExprType ntype) { m_ntype = ntype; }
	ExprType getNtype() { return m_ntype; }


    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::InitDeclarator; }
};

/**
 * @brief <izravni_deklarator>
 * 
 */
class DirectDeclarator : public GenericDeclaration {
private:
	ExprType m_ntype;
	int m_elementCnt;
public:
    void check() override;
	void setNtype(ExprType ntype) { m_ntype = ntype; }
	ExprType getNtype() { return m_ntype; }
	void setElementCnt(int elementCnt) { m_elementCnt = elementCnt; }
	int getElementCnt() { return m_elementCnt; }

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
private:
	ExprType m_ntype;
	int m_elementCnt;
	std::vector<ExprType> m_types;
public:
    void check() override;
	void setNtype(ExprType ntype) { m_ntype = ntype; }
	ExprType getNtype() { return m_ntype; }
	void setElementCnt(int elementCnt) { m_elementCnt = elementCnt; }
	int getElementCnt() { return m_elementCnt; }
	void setTypes(std::vector<ExprType> types) { m_types = types; }
	void addType(ExprType tip) { m_types.push_back(tip); }
	std::vector<ExprType> getTypes() { return m_types; }


    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::JoinExpressionList; }
};

#endif //DECLARATIONS_H