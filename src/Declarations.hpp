#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "SyntaxTree.hpp"
#include <iostream>
#include <forward_list>
#include <vector>

/**
 * @brief <definicija funkcije>
 * 
 */
class FunctionDefinition : public SyntaxTreeNode {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::FunctionDefinition; }
};

/**
 * @brief <lista_parametara>
 * 
 */
class ParameterList : public SyntaxTreeNode {
protected:
	std::vector<ExprType> m_types;
	std::vector<std::string> m_names;
public:
    void check() override;

	inline std::vector<ExprType> getTypes() const { return m_types; }
	inline std::vector<std::string> getNames() const { return m_names; }
	inline size_t getSize() const { return m_types.size(); }
   
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::ParameterList; }
};

/**
 * @brief <deklaracija_parametara>
 * 
 */
class ParameterDeclaration : public SyntaxTreeNode {
protected:
	std::string m_name;
	ExprType m_exprType;
public:
    void check() override;

	[[nodiscard]] inline std::string getName() const { return m_name; }
	[[nodiscard]] inline ExprType getExprType() const { return m_exprType; }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::ParameterDeclaration; }
};

/**
 * @brief <lista_deklaracija>
 * 
 */
class DeclarationList : public SyntaxTreeNode {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::DeclarationList; }
};

/**
 * @brief <deklaracija>
 * 
 */
class Declaration : public SyntaxTreeNode {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::Declaration; }
};

/**
 * @brief <lista_init_deklaratora>
 * 
 */
class DeclaratorInitList : public SyntaxTreeNode {
private:
	ExprType m_ntype;

public:
    void check() override;
	
	inline void setNtype(ExprType ntype) { m_ntype = ntype; }
	[[nodiscard]] inline ExprType getNtype() const { return m_ntype; }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::DeclaratorInitList; }
};

/**
 * @brief <init_deklarator>
 * 
 */
class InitDeclarator : public SyntaxTreeNode {
private:
	ExprType m_ntype;

public:
    void check() override;

	inline void setNtype(ExprType ntype) { m_ntype = ntype; }
	[[nodiscard]] inline ExprType getNtype() const { return m_ntype; }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::InitDeclarator; }
};

/**
 * @brief <izravni_deklarator>
 * 
 */
class DirectDeclarator : public SyntaxTreeNode {
private:
	ExprType m_exprType;
	ExprType m_ntype;
	int m_elementCnt;

public:
    void check() override;

	[[nodiscard]] inline int getElementCnt() const { return m_elementCnt; }
	inline void setNtype(ExprType ntype) { m_ntype = ntype; }
	[[nodiscard]] inline ExprType getNtype() const { return m_ntype; }
	[[nodiscard]] inline ExprType getExprType() const { return m_exprType; }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::DirectDeclarator; }
};

/**
 * @brief <inicijalizator>
 * 
 */
class Initializer : public SyntaxTreeNode {
private:
	std::vector<ExprType> m_types;
public:
    void check() override;
    
	[[nodiscard]] inline std::vector<ExprType> getTypes() const { return m_types; }
	[[nodiscard]] inline ExprType getType(int i) const { return m_types[i]; }
	[[nodiscard]] inline int getElementCount() const { return m_types.size(); }
	[[nodiscard]] inline NodeType getNodeType() const override { return NodeType::Initializer; }
};

/**
 * @brief <lista_izraza_pridruzivanja>
 * 
 */
class JoinExpressionList : public SyntaxTreeNode {
private:
	std::vector<ExprType> m_types;
public:
    void check() override;
	
	[[nodiscard]] inline std::vector<ExprType> getTypes() const { return m_types; }
	[[nodiscard]] inline ExprType getType(int i) const { return m_types[i]; }
	[[nodiscard]] inline int getElementCount() const { return m_types.size(); }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::JoinExpressionList; }
};

#endif //DECLARATIONS_H