#ifndef COMMANDS_H
#define COMMANDS_H

#include "SyntaxTree.hpp"
#include <iostream>

/**
 * @brief All other command classes should be based on this class
 * 
 */
class GenericCommand : public SyntaxTreeNode {
protected:
    ExprType m_exprType;

public:
    [[nodiscard]] inline ExprType getExprType() const { return m_exprType; }
};

/**
 * @brief <slozena_naredba>
 * 
 */
class ComplexCommand : public GenericCommand {
public:
    void check() override;
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::ComplexCommand; }
};

/**
 * @brief <lista_naredbi>
 * 
 */
class ListCommand : public GenericCommand {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::ListCommand; }
};

/**
 * @brief <naredba>
 * 
 */
class Command : public GenericCommand {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::Command; }
};

/**
 * @brief <izraz_naredba>
 * 
 */
class ExpressionCommand : public GenericCommand {
public:
    void check() override;
    void generateCode(std::ostream& stream) override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::ExpressionCommand; }
};

/**
 * @brief <naredba_grananja>
 * 
 */
class BranchCommand : public GenericCommand {
public:
    void check() override;
    void generateCode(std::ostream &stream) override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::BranchCommand; }
};

/**
 * @brief <naredba_petlje>
 * 
 */
class LoopCommand : public GenericCommand {
protected:
    int m_loopStartTmpId;
    int m_loopEndTmpId;
    int m_loopContinueTmpId;
public:
    void check() override;
    void generateCode(std::ostream &stream) override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LoopCommand; }
    [[nodiscard]] inline int getLoopEndTmpId() const { return m_loopEndTmpId; }
    [[nodiscard]] inline int getLoopStartTmpId() const { return m_loopStartTmpId; }
    [[nodiscard]] inline int getLoopContinueTmpId() const { return m_loopContinueTmpId; }
};

/**
 * @brief <naredba_skoka>
 * 
 */
class JumpCommand : public GenericCommand {
private:
	ExprType m_functionReturnType = ExprType::Error; 
	SyntaxTreeNode *m_loop = nullptr;

public:
	JumpCommand() = default;
	inline void setFunctionReturnType(ExprType functionReturnType) { m_functionReturnType = functionReturnType; }
	inline void setMyLoop(SyntaxTreeNode *loop) { m_loop = loop; }
	[[nodiscard]] inline SyntaxTreeNode* getMyLoop() const { return m_loop; }
    void check() override;
    void generateCode(std::ostream &stream) override;

    [[nodiscard]] inline ExprType getFunctionReturnType() const { return m_functionReturnType; }
    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::JumpCommand; }
};

/**
 * @brief <prijevodna_jedinica>
 * 
 */
class TranslationUnit : public GenericCommand {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::TranslationUnit; }
};

/**
 * @brief <vanjska_deklaracija>
 * 
 */
class ExternalDeclaration : public GenericCommand {
public:
    void check() override;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::ExternalDeclaration; }
};

#endif //COMMANDS_H