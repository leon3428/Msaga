#include "Commands.hpp"
#include "Leafs.hpp"
#include "Common.hpp"
#include "Declarations.hpp"
#include "Expressions.hpp"

void ComplexCommand::check() {
    if(checkChildren<NodeType::LeafLeftCurlyBracket, NodeType::ListCommand, NodeType::LeafRightCurlyBracket>()) {
		ListCommand *l = static_cast<ListCommand *>(m_children[1].get());
		l -> setInsideLoop(this -> isInsideLoop());
		l -> setFunctionType(this -> getFunctionType());
        l -> check();
    } else if (checkChildren<NodeType::LeafLeftCurlyBracket, NodeType::DeclarationList, NodeType::ListCommand, NodeType::LeafRightCurlyBracket>()) {
		DeclarationList *l = static_cast<DeclarationList *>(m_children[1].get());
		l -> check();
		ListCommand *r = static_cast<ListCommand *>(m_children[2].get());
		r -> setInsideLoop(this -> isInsideLoop());
		r -> setFunctionType(this -> getFunctionType());
		r -> check();
	} else {
        m_errorHandler();
    }
}

void ListCommand::check() {
    if(checkChildren<NodeType::Command>()) {
        Command *l = static_cast<Command *>(m_children[0].get());
		l -> setInsideLoop(this -> isInsideLoop());
		l -> setFunctionType(this -> getFunctionType());
        l -> check();
    } else if (checkChildren<NodeType::ListCommand, NodeType::Command>()) {
		ListCommand *l = static_cast<ListCommand *>(m_children[0].get());
		l -> setInsideLoop(this -> isInsideLoop());
		l -> setFunctionType(this -> getFunctionType());
		l -> check();
		Command *r = static_cast<Command *>(m_children[1].get());
		r -> setInsideLoop(this -> isInsideLoop());
		r -> setFunctionType(this -> getFunctionType());
		r -> check();
	} else {
        m_errorHandler();
    }
}

void Command::check() {
	if(checkChildren<NodeType::ComplexCommand>()) {
        ComplexCommand *l = static_cast<ComplexCommand *>(m_children[0].get());
		l -> setInsideLoop(this -> isInsideLoop());
		l -> setFunctionType(this -> getFunctionType());
        l -> check();
    } else if (checkChildren<NodeType::ExpressionCommand>()) {
		ExpressionCommand *l = static_cast<ExpressionCommand *>(m_children[0].get());
		l -> check();
	} else if (checkChildren<NodeType::BranchCommand>()) {
		BranchCommand *l = static_cast<BranchCommand *>(m_children[0].get());
		l -> setInsideLoop(this -> isInsideLoop());
		l -> setFunctionType(this -> getFunctionType());
		l -> check();
	} else if (checkChildren<NodeType::LoopCommand>()) {
		LoopCommand *l = static_cast<LoopCommand *>(m_children[0].get());
		l -> check();
	} else if (checkChildren<NodeType::GotoCommand>()) {
		GotoCommand *l = static_cast<GotoCommand *>(m_children[0].get());
		l -> setInsideLoop(this -> isInsideLoop());
		l -> setFunctionType(this -> getFunctionType());
		l -> check();
	} else {
        m_errorHandler();
    }
}

void ExpressionCommand::check() {
	if(checkChildren<NodeType::LeafSemicolon>()) {
        m_exprType = ExprType::Int;
    } else if (checkChildren<NodeType::Expression, NodeType::LeafSemicolon>()) {
		Expression *l = static_cast<Expression *>(m_children[0].get());
		l -> check();
		m_exprType = l -> getExprType();
	} else {
        m_errorHandler();
    }
}

void BranchCommand::check() {
	if(checkChildren<NodeType::LeafKrIf, NodeType::LeafLeftBracket, NodeType::Expression, NodeType::LeafRightBracket, NodeType::Command>()) {
        Expression *exp = static_cast<Expression *>(m_children[2].get());
		exp -> check();
		if(!Msaga::implicitlyConvertible(exp -> getExprType(), ExprType::Int))
            m_errorHandler();
		Command *r = static_cast<Command *>(m_children[4].get());
		r -> setInsideLoop(this -> isInsideLoop());
		r -> setFunctionType(this -> getFunctionType());
		r -> check();
    } else if (checkChildren<NodeType::LeafKrIf, NodeType::LeafLeftBracket, NodeType::Expression,
				NodeType::LeafRightBracket, NodeType::Command, NodeType::LeafKrElse, NodeType::Command>()) {
		Expression *exp = static_cast<Expression *>(m_children[2].get());
		exp -> check();
		if(!Msaga::implicitlyConvertible(exp -> getExprType(), ExprType::Int))
            m_errorHandler();
		Command *c1 = static_cast<Command *>(m_children[4].get());
		c1 -> setInsideLoop(this -> isInsideLoop());
		c1 -> setFunctionType(this -> getFunctionType());
		c1 -> check();
		Command *c2 = static_cast<Command *>(m_children[6].get());
		c2 -> setInsideLoop(this -> isInsideLoop());
		c2 -> setFunctionType(this -> getFunctionType());
		c2 -> check();
	} else {
        m_errorHandler();
    }	
}

void LoopCommand::check() {
	if(checkChildren<NodeType::LeafKrWhile, NodeType::LeafLeftBracket, NodeType::Expression, NodeType::LeafRightBracket, NodeType::Command>()) {
        Expression *exp = static_cast<Expression *>(m_children[2].get());
		exp -> check();
		if(!Msaga::implicitlyConvertible(exp -> getExprType(), ExprType::Int))
            m_errorHandler();
		Command *c1 = static_cast<Command *>(m_children[4].get());
		c1 -> check();
    } else if (checkChildren<NodeType::LeafKrFor, NodeType::LeafLeftBracket, NodeType::ExpressionCommand,
				NodeType::ExpressionCommand, NodeType::LeafRightBracket, NodeType::Command>()) {
		ExpressionCommand *c1 = static_cast<ExpressionCommand *>(m_children[2].get());
		c1 -> check();
		ExpressionCommand *c2 = static_cast<ExpressionCommand *>(m_children[3].get());
		c2 -> check();
		if(!Msaga::implicitlyConvertible(c2 -> getExprType(), ExprType::Int))
            m_errorHandler();
		Command *com = static_cast<Command *>(m_children[5].get());
		com -> check();
	} else if (checkChildren<NodeType::LeafKrFor, NodeType::LeafLeftBracket, NodeType::ExpressionCommand,
				NodeType::ExpressionCommand, NodeType::Expression, NodeType::LeafRightBracket, NodeType::Command>()) {
		ExpressionCommand *c1 = static_cast<ExpressionCommand *>(m_children[2].get());
		c1 -> check();
		ExpressionCommand *c2 = static_cast<ExpressionCommand *>(m_children[3].get());
		c2 -> check();
		if(!Msaga::implicitlyConvertible(c2 -> getExprType(), ExprType::Int))
            m_errorHandler();
		Expression *exp = static_cast<Expression *>(m_children[4].get());
		exp -> check();
		Command *com = static_cast<Command *>(m_children[6].get());
		com -> check();
	} else {
        m_errorHandler();
    }	
}

void GotoCommand::check() {
	if(checkChildren<NodeType::LeafKrContinue, NodeType::LeafSemicolon>() ||
		checkChildren<NodeType::LeafKrBreak, NodeType::LeafSemicolon>()) {
		if(!(this -> isInsideLoop()))
			m_errorHandler();
	} else if(checkChildren<NodeType::LeafKrReturn, NodeType::LeafSemicolon>()) {
		Msaga::FunctionType *func = this -> getFunctionType();
		if(!func || func -> returnType != ExprType::Void)
			m_errorHandler();
	} else if(checkChildren<NodeType::LeafKrReturn, NodeType::Expression, NodeType::LeafSemicolon>()) {
		Expression *exp = static_cast<Expression *>(m_children[1].get());
		exp -> check();
		Msaga::FunctionType *func = this -> getFunctionType();
		if(!func || !(Msaga::implicitlyConvertible(exp -> getExprType(), func -> returnType)))
			m_errorHandler();
	} else {
		m_errorHandler();
	}
}

void TranslationUnit::check() {
	if(checkChildren<NodeType::ExternalDeclaration>()) {
        ExternalDeclaration *l = static_cast<ExternalDeclaration *>(m_children[0].get());
		l -> setInsideLoop(this -> isInsideLoop());
		l -> setFunctionType(this -> getFunctionType());
		l -> check();
    } else if(checkChildren<NodeType::TranslationUnit, NodeType::ExternalDeclaration>()) {
        TranslationUnit *l = static_cast<TranslationUnit *>(m_children[0].get());
		l -> setInsideLoop(this -> isInsideLoop());
		l -> setFunctionType(this -> getFunctionType());
		l -> check();
		ExternalDeclaration *r = static_cast<ExternalDeclaration *>(m_children[1].get());
		r -> setInsideLoop(this -> isInsideLoop());
		r -> setFunctionType(this -> getFunctionType());
		r -> check();
	} else {
        m_errorHandler();
    }
}

void ExternalDeclaration::check() {
	if(checkChildren<NodeType::FunctionDefinition>()) {
        FunctionDefinition *l = static_cast<FunctionDefinition *>(m_children[0].get());
		l -> setInsideLoop(this -> isInsideLoop());
		l -> setFunctionType(this -> getFunctionType());
		l -> check();
    } else if(checkChildren<NodeType::Declaration>()) {
        Declaration *l = static_cast<Declaration *>(m_children[0].get());
		l -> check();
	} else {
        m_errorHandler();
    }
}