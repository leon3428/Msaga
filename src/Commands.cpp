#include "Commands.hpp"
#include "Leafs.hpp"
#include "Common.hpp"
#include "Declarations.hpp"
#include "Expressions.hpp"

void ComplexCommand::check() {
    if(checkChildren<NodeType::LeafLeftCurlyBracket, NodeType::ListCommand, NodeType::LeafRightCurlyBracket>()) {
		m_children[1] -> check();
    } else if (checkChildren<NodeType::LeafLeftCurlyBracket, NodeType::DeclarationList, NodeType::ListCommand, NodeType::LeafRightCurlyBracket>()) {
		m_children[1].get() -> check();
		m_children[2].get() -> check();
	} else {
        m_errorHandler();
    }
}

void ListCommand::check() {
    if(checkChildren<NodeType::Command>()) {
        m_children[0] -> check();
    } else if (checkChildren<NodeType::ListCommand, NodeType::Command>()) {
		m_children[0] -> check();
		m_children[1] -> check();
	} else {
        m_errorHandler();
    }
}

void Command::check() {
	if(checkChildren<NodeType::ComplexCommand>() ||
	   checkChildren<NodeType::ExpressionCommand>() ||
	   checkChildren<NodeType::BranchCommand>() ||
	   checkChildren<NodeType::LoopCommand>() ||
	   checkChildren<NodeType::JumpCommand>()
	   )
	{
        m_children[0] -> check();
    } else {
        m_errorHandler();
    }
}

void ExpressionCommand::check() {
	if(checkChildren<NodeType::LeafSemicolon>()) {
        m_exprType = ExprType::Int;
    } else if (checkChildren<NodeType::Expression, NodeType::LeafSemicolon>()) {
		Expression *l = static_cast<Expression*>(m_children[0].get());
		l -> check();
		m_exprType = l -> getExprType();
	} else {
        m_errorHandler();
    }
}

void BranchCommand::check() {
	if(checkChildren<NodeType::LeafKwIf, NodeType::LeafLeftBracket, NodeType::Expression, NodeType::LeafRightBracket, NodeType::Command>()) {
        Expression *exp = static_cast<Expression *>(m_children[2].get());
		exp -> check();
		if(!Msaga::implicitlyConvertible(exp -> getExprType(), ExprType::Int))
            m_errorHandler();
		m_children[4] -> check();
    } else if (checkChildren<NodeType::LeafKwIf, NodeType::LeafLeftBracket, NodeType::Expression,
				NodeType::LeafRightBracket, NodeType::Command, NodeType::LeafKwElse, NodeType::Command>())
	{
		Expression *exp = static_cast<Expression *>(m_children[2].get());
		exp -> check();
		if(!Msaga::implicitlyConvertible(exp -> getExprType(), ExprType::Int))
            m_errorHandler();
		m_children[4] -> check();
		m_children[6] -> check();
	} else {
        m_errorHandler();
    }	
}

void LoopCommand::check() {
	if(checkChildren<NodeType::LeafKwWhile, NodeType::LeafLeftBracket, NodeType::Expression, NodeType::LeafRightBracket, NodeType::Command>()) {
        Expression *exp = static_cast<Expression *>(m_children[2].get());
		exp -> check();
		if(!Msaga::implicitlyConvertible(exp -> getExprType(), ExprType::Int))
            m_errorHandler();
		m_children[4] -> check();

    } else if (checkChildren<NodeType::LeafKwFor, NodeType::LeafLeftBracket, NodeType::ExpressionCommand,
				NodeType::ExpressionCommand, NodeType::LeafRightBracket, NodeType::Command>()) {
		m_children[2] -> check();
		ExpressionCommand *c2 = static_cast<ExpressionCommand *>(m_children[3].get());
		c2 -> check();
		if(!Msaga::implicitlyConvertible(c2 -> getExprType(), ExprType::Int))
            m_errorHandler();
		m_children[5].get() -> check();

	} else if (checkChildren<NodeType::LeafKwFor, NodeType::LeafLeftBracket, NodeType::ExpressionCommand,
				NodeType::ExpressionCommand, NodeType::Expression, NodeType::LeafRightBracket, NodeType::Command>()) {
		m_children[2] -> check();
		ExpressionCommand *c2 = static_cast<ExpressionCommand *>(m_children[3].get());
		c2 -> check();
		if(!Msaga::implicitlyConvertible(c2 -> getExprType(), ExprType::Int))
            m_errorHandler();
		m_children[4] -> check();
		m_children[6] -> check();
	} else {
        m_errorHandler();
    }	
}

void JumpCommand::check() {
	if(checkChildren<NodeType::LeafKwContinue, NodeType::LeafSemicolon>() ||
		checkChildren<NodeType::LeafKwBreak, NodeType::LeafSemicolon>()) 
	{
		if(m_insideLoop == nullptr)
			m_errorHandler();
	} else if(checkChildren<NodeType::LeafKwReturn, NodeType::LeafSemicolon>()) {
		if(m_functionType == nullptr || m_functionType -> returnType != ExprType::Void)
			m_errorHandler();
	} else if(checkChildren<NodeType::LeafKwReturn, NodeType::Expression, NodeType::LeafSemicolon>()) {
		Expression *exp = static_cast<Expression *>(m_children[1].get());
		exp -> check();

		if(m_functionType == nullptr || !Msaga::implicitlyConvertible(exp -> getExprType(), m_functionType -> returnType))
			m_errorHandler();
	} else {
		m_errorHandler();
	}
}

void TranslationUnit::check() {
	if(checkChildren<NodeType::ExternalDeclaration>()) {
        m_children[0] -> check();
    } else if(checkChildren<NodeType::TranslationUnit, NodeType::ExternalDeclaration>()) {
        m_children[0] -> check();
		m_children[1] -> check();
	} else {
        m_errorHandler();
    }
}

void ExternalDeclaration::check() {
	if(checkChildren<NodeType::FunctionDefinition>() ||
	   checkChildren<NodeType::Declaration>())
	{
        m_children[0] -> check();
    } else {
        m_errorHandler();
    }
}