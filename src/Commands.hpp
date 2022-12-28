#ifndef COMMANDS_H
#define COMMANDS_H

#include "SyntaxTree.hpp"
#include <iostream>
#include <forward_list>

/**
 * @brief All other command classes should be based on this class
 * 
 */
class GenericCommand : public SyntaxTreeNode {
protected:
    ExprType m_exprType;

public:
    [[nodiscard]] inline ExprType getExprType() const { return m_exprType; }

    inline void setExprType(ExprType exprType) { m_exprType = exprType; }
};

/**
 * @brief <slozena_naredba>
 * 
 */
class ComplexCommand : public GenericCommand {
private:
	Msaga::FunctionType *m_functionType = nullptr;
	SyntaxTreeNode *m_insideLoop = nullptr;

public:
	ComplexCommand() = default;
	inline void setFunctionType(Msaga::FunctionType *functionType) { m_functionType = functionType; }
	void setInsideLoop(SyntaxTreeNode* insideLoop) { m_insideLoop = insideLoop; }
	SyntaxTreeNode* isInsideLoop() { return m_insideLoop; }
    void check() override;

	[[nodiscard]] inline Msaga::FunctionType* getFunctionType() const { return m_functionType; }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::ComplexCommand; }
};

/**
 * @brief <lista_naredbi>
 * 
 */
class ListCommand : public GenericCommand {
private:
	Msaga::FunctionType *m_functionType = nullptr;
	SyntaxTreeNode *m_insideLoop = nullptr;

public:
	ListCommand() = default;
	inline void setFunctionType(Msaga::FunctionType *functionType) { m_functionType = functionType; }
	void setInsideLoop(SyntaxTreeNode* insideLoop) { m_insideLoop = insideLoop; }
	SyntaxTreeNode* isInsideLoop() { return m_insideLoop; }
    void check() override;

	[[nodiscard]] inline Msaga::FunctionType* getFunctionType() const { return m_functionType; }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::ListCommand; }
};

/**
 * @brief <naredba>
 * 
 */
class Command : public GenericCommand {
private:
	Msaga::FunctionType *m_functionType = nullptr;
	SyntaxTreeNode *m_insideLoop = nullptr;

public:
	Command() = default;
	inline void setFunctionType(Msaga::FunctionType *functionType) { m_functionType = functionType; }
	void setInsideLoop(SyntaxTreeNode* insideLoop) { m_insideLoop = insideLoop; }
	SyntaxTreeNode* isInsideLoop() { return m_insideLoop; }
    void check() override;

	[[nodiscard]] inline Msaga::FunctionType* getFunctionType() const { return m_functionType; }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::Command; }
};

/**
 * @brief <izraz_naredba>
 * 
 */
class ExpressionCommand : public GenericCommand {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::ExpressionCommand; }
};

/**
 * @brief <naredba_grananja>
 * 
 */
class BranchCommand : public GenericCommand {
private:
	Msaga::FunctionType *m_functionType = nullptr;
	SyntaxTreeNode *m_insideLoop = nullptr;

public:
	BranchCommand() = default;
	inline void setFunctionType(Msaga::FunctionType *functionType) { m_functionType = functionType; }
	void setInsideLoop(SyntaxTreeNode* insideLoop) { m_insideLoop = insideLoop; }
	SyntaxTreeNode* isInsideLoop() { return m_insideLoop; }
    void check() override;

	[[nodiscard]] inline Msaga::FunctionType* getFunctionType() const { return m_functionType; }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::BranchCommand; }
};

/**
 * @brief <naredba_petlje>
 * 
 */
class LoopCommand : public GenericCommand {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LoopCommand; }
};

/**
 * @brief <naredba_skoka>
 * 
 */
class GotoCommand : public GenericCommand {
private:
	Msaga::FunctionType *m_functionType = nullptr;
	SyntaxTreeNode *m_insideLoop = nullptr;

public:
	GotoCommand() = default;
	inline void setFunctionType(Msaga::FunctionType *functionType) { m_functionType = functionType; }
	void setInsideLoop(SyntaxTreeNode* insideLoop) { m_insideLoop = insideLoop; }
	SyntaxTreeNode* isInsideLoop() { return m_insideLoop; }
    void check() override;

	[[nodiscard]] inline Msaga::FunctionType* getFunctionType() const { return m_functionType; }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::GotoCommand; }
};

/**
 * @brief <prijevodna_jedinica>
 * 
 */
class TranslationUnit : public GenericCommand {
private:
	Msaga::FunctionType *m_functionType = nullptr;
	SyntaxTreeNode *m_insideLoop = nullptr;

public:
	TranslationUnit() = default;
	inline void setFunctionType(Msaga::FunctionType *functionType) { m_functionType = functionType; }
	void setInsideLoop(SyntaxTreeNode* insideLoop) { m_insideLoop = insideLoop; }
	SyntaxTreeNode* isInsideLoop() { return m_insideLoop; }
    void check() override;

	[[nodiscard]] inline Msaga::FunctionType* getFunctionType() const { return m_functionType; }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::TranslationUnit; }
};

/**
 * @brief <vanjska_deklaracija>
 * 
 */
class ExternalDeclaration : public GenericCommand {
private:
	Msaga::FunctionType *m_functionType = nullptr;
	SyntaxTreeNode *m_insideLoop = nullptr;

public:
	ExternalDeclaration() = default;
	inline void setFunctionType(Msaga::FunctionType *functionType) { m_functionType = functionType; }
	void setInsideLoop(SyntaxTreeNode* insideLoop) { m_insideLoop = insideLoop; }
	SyntaxTreeNode* isInsideLoop() { return m_insideLoop; }
    void check() override;

	[[nodiscard]] inline Msaga::FunctionType* getFunctionType() const { return m_functionType; }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::ExternalDeclaration; }
};

#endif //COMMANDS_H