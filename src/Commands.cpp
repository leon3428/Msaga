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

void ExpressionCommand::generateCode(std::ostream& stream) {
	if (checkChildren<NodeType::Expression, NodeType::LeafSemicolon>()) {
		Msaga::allChildrenGenerateCode(stream, this);
		stream << '\t' << "POP R0\n";
	} else {
		Msaga::allChildrenGenerateCode(stream, this);
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

void BranchCommand::generateCode(std::ostream &stream) {
	if(checkChildren<NodeType::LeafKwIf, NodeType::LeafLeftBracket, NodeType::Expression, NodeType::LeafRightBracket, NodeType::Command>()) {
		int tmpId = Msaga::getTmpLabelId();
		
		m_children[2] -> generateCode(stream);
		stream << '\t' << "POP R0\n";
		stream << '\t' << "CMP R0, 0\n";
		stream << '\t' << "JP_EQ tmp" << tmpId << '\n';

		m_children[4] -> generateCode(stream);

		stream << "tmp" << tmpId << '\n'; // endif
    } else if (checkChildren<NodeType::LeafKwIf, NodeType::LeafLeftBracket, NodeType::Expression,
				NodeType::LeafRightBracket, NodeType::Command, NodeType::LeafKwElse, NodeType::Command>())
	{
		int tmpId1 = Msaga::getTmpLabelId();
		int tmpId2 = Msaga::getTmpLabelId();
		
		m_children[2] -> generateCode(stream);
		stream << '\t' << "POP R0\n";
		stream << '\t' << "CMP R0, 0\n";
		stream << '\t' << "JP_EQ tmp" << tmpId1 << '\n';

		m_children[4] -> generateCode(stream);
		stream << '\t' << "JP tmp" << tmpId2 << '\n';

		stream << "tmp" << tmpId1 << '\n'; // else
		m_children[6] -> generateCode(stream);
		stream << "tmp" << tmpId2 << '\n'; // endif

	} else {
        Msaga::allChildrenGenerateCode(stream, this);
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

void LoopCommand::generateCode(std::ostream &stream) {
	if(checkChildren<NodeType::LeafKwWhile, NodeType::LeafLeftBracket, NodeType::Expression, NodeType::LeafRightBracket, NodeType::Command>()) {
		m_loopStartTmpId = Msaga::getTmpLabelId();
		m_loopEndTmpId = Msaga::getTmpLabelId();
		m_loopContinueTmpId = m_loopStartTmpId;

		stream << "tmp" << m_loopStartTmpId << "\n"; // loop start
		m_children[2] -> generateCode(stream);
		stream << '\t' << "POP R0\n";
		stream << '\t' << "CMP R0, 0\n";
		stream << '\t' << "JP_EQ tmp" << m_loopEndTmpId << '\n';
		m_children[4] -> generateCode(stream);
		stream << '\t' << "JP tmp" << m_loopStartTmpId << '\n';
		stream << "tmp" << m_loopEndTmpId << '\n'; // loop end
    } else if (checkChildren<NodeType::LeafKwFor, NodeType::LeafLeftBracket, NodeType::ExpressionCommand,
				NodeType::ExpressionCommand, NodeType::LeafRightBracket, NodeType::Command>())
	{
		m_loopStartTmpId = Msaga::getTmpLabelId();
		m_loopEndTmpId = Msaga::getTmpLabelId();
		m_loopContinueTmpId = m_loopStartTmpId;

		m_children[2] -> generateCode(stream);
		stream << "tmp" << m_loopStartTmpId << '\n'; // loop start
		if(m_children[3] -> getChildrenCnt() == 2) {
			m_children[3] -> getChild(0) -> generateCode(stream);
			stream << '\t' << "POP R0\n";
			stream << '\t' << "CMP R0, 0\n";
			stream << '\t' << "JP_EQ tmp" << m_loopEndTmpId << '\n';
		}
		m_children[5] -> generateCode(stream);
		stream << '\t' << "JP tmp" << m_loopStartTmpId << '\n';
		stream << "tmp" << m_loopEndTmpId << '\n'; // loop end
	} else if (checkChildren<NodeType::LeafKwFor, NodeType::LeafLeftBracket, NodeType::ExpressionCommand,
				NodeType::ExpressionCommand, NodeType::Expression, NodeType::LeafRightBracket, NodeType::Command>()) 
	{
		m_loopStartTmpId = Msaga::getTmpLabelId();
		m_loopEndTmpId = Msaga::getTmpLabelId();
		m_loopContinueTmpId = Msaga::getTmpLabelId();

		m_children[2] -> generateCode(stream);
		stream << "tmp" << m_loopStartTmpId << '\n'; // loop start
		if(m_children[3] -> getChildrenCnt() == 2) {
			m_children[3] -> getChild(0) -> generateCode(stream);
			stream << '\t' << "POP R0\n";
			stream << '\t' << "CMP R0, 0\n";
			stream << '\t' << "JP_EQ tmp" << m_loopEndTmpId << '\n';
		}
		m_children[6] -> generateCode(stream);
		stream << "tmp" << m_loopContinueTmpId << '\n';
		m_children[4] -> generateCode(stream);
		stream << '\t' << "POP R0\n";
		stream << '\t' << "JP tmp" << m_loopStartTmpId << '\n';
		stream << "tmp" << m_loopEndTmpId << '\n'; // loop end
	} else {
        Msaga::allChildrenGenerateCode(stream, this);
    }	
}

void JumpCommand::check() {
	if(checkChildren<NodeType::LeafKwContinue, NodeType::LeafSemicolon>() ||
		checkChildren<NodeType::LeafKwBreak, NodeType::LeafSemicolon>()) 
	{
		if(m_loop == nullptr)
			m_errorHandler();
	} else if(checkChildren<NodeType::LeafKwReturn, NodeType::LeafSemicolon>()) {
		if(m_functionReturnType != ExprType::Void)
			m_errorHandler();
	} else if(checkChildren<NodeType::LeafKwReturn, NodeType::Expression, NodeType::LeafSemicolon>()) {
		Expression *exp = static_cast<Expression *>(m_children[1].get());
		exp -> check();

		if(!Msaga::implicitlyConvertible(exp -> getExprType(), m_functionReturnType))
			m_errorHandler();
	} else {
		m_errorHandler();
	}
}

void JumpCommand::generateCode(std::ostream &stream) {
	if(checkChildren<NodeType::LeafKwContinue, NodeType::LeafSemicolon>()) {
		LoopCommand *lc = static_cast<LoopCommand*>(m_loop);
		stream << '\t' << "JP tmp" << lc -> getLoopContinueTmpId() << '\n';
	} else if(checkChildren<NodeType::LeafKwBreak, NodeType::LeafSemicolon>()) {
		LoopCommand *lc = static_cast<LoopCommand*>(m_loop);
		stream << '\t' << "JP tmp" << lc -> getLoopEndTmpId() << '\n';
	} else if(checkChildren<NodeType::LeafKwReturn, NodeType::LeafSemicolon>()) {
		stream << '\t' << "MOVE R6, SP\n";
		stream << '\t' << "RET\n";
	} else if(checkChildren<NodeType::LeafKwReturn, NodeType::Expression, NodeType::LeafSemicolon>()) {
		m_children[1] -> generateCode(stream);
		stream << '\t' << "POP R5\n";
		stream << '\t' << "MOVE R6, SP\n";
		stream << '\t' << "RET\n";
	} else {
        Msaga::allChildrenGenerateCode(stream, this);
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