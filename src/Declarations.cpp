#include "Commands.hpp"
#include "Leafs.hpp"
#include "Common.hpp"
#include "Declarations.hpp"
#include "Expressions.hpp"
#include "OtherNodes.hpp"
#include <string>
#include <iostream>

void FunctionDefinition::check() {
    
}

void ParameterList::check() {
	if(checkChildren<NodeType::ParameterDeclaration>()) {
		ParameterDeclaration *decl = static_cast<ParameterDeclaration *>(m_children[0].get());
		decl -> check();
		this -> addName(decl -> getName());
		this -> addType(decl -> getExprType());
	} else if(checkChildren<NodeType::ParameterList, NodeType::LeafComma, NodeType::ParameterDeclaration>()) {
		ParameterList *list = static_cast<ParameterList *>(m_children[0].get());
		list -> check();
		ParameterDeclaration *decl = static_cast<ParameterDeclaration *>(m_children[2].get());
		decl -> check();

		this -> setNames(list -> getNames());
		for(std::string name : this -> getNames())
			if(name == decl -> getName())
				m_errorHandler();

		this -> addName(decl -> getName());
		this -> setTypes(list -> getTypes());
		this -> addType(list -> getExprType());
	} else{
		m_errorHandler();
	}
}

void ParameterDeclaration::check() {
	if(checkChildren<NodeType::TypeName, NodeType::LeafIdn>()) {
		TypeName *tip = static_cast<TypeName *>(m_children[0].get());
		tip -> check();
		if(tip -> getExprType() == ExprType::Void)
			m_errorHandler();
		LeafIdn *idn = static_cast<LeafIdn *>(m_children[1].get());

		this -> setName(idn -> getLexicalUnit());
		this -> setExprType(tip -> getExprType());
	} else if(checkChildren<NodeType::TypeName, NodeType::LeafIdn, NodeType::LeafLeftSquareBracket, NodeType::LeafRightSquareBracket>()) {
		TypeName *tip = static_cast<TypeName *>(m_children[0].get());
		tip -> check();
		if(tip -> getExprType() == ExprType::Void)
			m_errorHandler();
		LeafIdn *idn = static_cast<LeafIdn *>(m_children[1].get());

		this -> setName(idn -> getLexicalUnit());
		this -> setExprType(Msaga::baseTypeToArray(tip -> getExprType()));
	} else{
		m_errorHandler();
	}
}

void DeclarationList::check() {
	if(checkChildren<NodeType::Declaration>()) {
		Declaration *decl = static_cast<Declaration *>(m_children[0].get());
		decl -> check();
	} else if(checkChildren<NodeType::DeclarationList, NodeType::Declaration>()) {
		DeclarationList *declList = static_cast<DeclarationList *>(m_children[0].get());
		declList -> check();
		Declaration *decl = static_cast<Declaration *>(m_children[1].get());
		decl -> check();
	} else{
		m_errorHandler();
	}
}

void Declaration::check() {
	if(checkChildren<NodeType::TypeName, NodeType::DeclaratorInitList, NodeType::LeafSemicolon>()) {
		Declaration *tip = static_cast<Declaration *>(m_children[0].get());
		tip -> check();
		DeclaratorInitList *declList = static_cast<DeclaratorInitList*>(m_children[1].get());
		declList -> setNtype(tip -> getExprType());
		declList -> check();
	} else{
		m_errorHandler();
	}
}

void DeclaratorInitList::check() {
	if(checkChildren<NodeType::InitDeclarator>()) {
		InitDeclarator *decl = static_cast<InitDeclarator *>(m_children[0].get());
		decl -> setNtype(this -> getNtype());
		decl -> check();
	} else if(checkChildren<NodeType::DeclaratorInitList, NodeType::LeafComma, NodeType::InitDeclarator>()) {
		DeclaratorInitList *declList = static_cast<DeclaratorInitList*>(m_children[0].get());				
		declList -> setNtype(this -> getNtype());
		declList -> check();
		InitDeclarator *declInit = static_cast<InitDeclarator*>(m_children[2].get());
		declInit -> setNtype(this -> getNtype());
		declInit -> check();
	} else{
		m_errorHandler();
	}
}

void InitDeclarator::check() {
	if(checkChildren<NodeType::DirectDeclarator>()) {
		DirectDeclarator *decl = static_cast<DirectDeclarator *>(m_children[0].get());
		decl -> setNtype(this -> getNtype());
		decl -> check();
		if(Msaga::isConst(decl -> getExprType()) || Msaga::isConstArray(decl -> getExprType()))
			m_errorHandler();
	} else if(checkChildren<NodeType::DirectDeclarator, NodeType::LeafAssignment, NodeType::Initializator>()) {
		DirectDeclarator *decl = static_cast<DirectDeclarator *>(m_children[0].get());
		decl -> setNtype(this -> getNtype());
		decl -> check();
		Initializator *init = static_cast<Initializator *>(m_children[2].get());
		init -> check();
		if(Msaga::isConst(decl -> getExprType()) || Msaga::isNumber(decl -> getExprType())) {
			if(!Msaga::implicitlyConvertibleToT(init -> getExprType()))
				m_errorHandler();
		} else if(Msaga::isArrayType(decl -> getExprType())) {
			if(init -> getElementCnt() > decl -> getElementCnt())
				m_errorHandler();
			for(auto tip : init -> getTypes())
				if(!Msaga::implicitlyConvertibleToT(tip))
					m_errorHandler(); // malo mi je upitno ovo
		} else {
			m_errorHandler();
		}
	} else{
		m_errorHandler();
	}
}

void DirectDeclarator::check() {
	if(checkChildren<NodeType::LeafIdn>()) {
		if(this -> getNtype() == ExprType::Void)
			m_errorHandler();
		
		LeafIdn *idn = static_cast<LeafIdn *>(m_children[0].get());
		if(Msaga::inLocalScope(idn -> getLexicalUnit()))
			m_errorHandler();
		this -> setExprType(this -> getNtype());
		Msaga::declareVariable(idn -> getLexicalUnit(), this -> getExprType());
	} else if(checkChildren<NodeType::LeafIdn, NodeType::LeafLeftSquareBracket, NodeType::LeafNum, NodeType::LeafRightSquareBracket>()) {
		LeafNum *num = static_cast<LeafNum *>(m_children[2].get()); 
		int cnt = std::stoi(num -> getLexicalUnit());

		if(this -> getNtype() == ExprType::Void)
			m_errorHandler();
		LeafIdn *idn = static_cast<LeafIdn *>(m_children[0].get());
		if(Msaga::inLocalScope(idn -> getLexicalUnit()))
			m_errorHandler();
		if(cnt <= 0 || cnt > 1024)
			m_errorHandler();
		this -> setElementCnt(cnt);
		this -> setExprType(Msaga::baseTypeToArray(this -> getNtype()));
		Msaga::declareVariable(idn -> getLexicalUnit(), this -> getExprType());
	} else if(checkChildren<NodeType::LeafIdn, NodeType::LeafLeftBracket, NodeType::LeafKwVoid, NodeType::LeafRightBracket>()) {
		; // TODO
	} else if(checkChildren<NodeType::LeafIdn, NodeType::LeafLeftBracket, NodeType::ParameterList, NodeType::LeafRightBracket>()) {
		ParameterList *list = static_cast<ParameterList *>(m_children[2].get());
		list -> check();
		// TODO
	}
	else {
		m_errorHandler();
	}
}

void Initializator::check() {
	if(checkChildren<NodeType::AssignmentExpression>()) {
		AssignmentExpression *expr = static_cast<AssignmentExpression *>(m_children[0].get());
		expr -> check();
		// TODO: NEKAK PROVJERIT JEL EXPR IDE U NIZ_ZNAKOVA I OSTATAK
	} else if(checkChildren<NodeType::LeafLeftCurlyBracket, NodeType::JoinExpressionList, NodeType::LeafRightCurlyBracket>()) {
		JoinExpressionList *list = static_cast<JoinExpressionList *>(m_children[0].get());
		list -> check();
		this -> setElementCnt(list -> getElementCnt());
		this -> setTypes(list -> getTypes());
	}
	else {
		m_errorHandler();
	}
}

void JoinExpressionList::check() {
	if(checkChildren<NodeType::AssignmentExpression>()) {
		AssignmentExpression *expr = static_cast<AssignmentExpression *>(m_children[0].get());
		expr -> check();
		this -> setElementCnt(1);
		this -> addType(expr -> getExprType());
	} else if(checkChildren<NodeType::JoinExpressionList, NodeType::LeafComma, NodeType::AssignmentExpression>()) {
		JoinExpressionList *list = static_cast<JoinExpressionList *>(m_children[0].get());
		list -> check();
		AssignmentExpression *expr = static_cast<AssignmentExpression *>(m_children[2].get());
		expr -> check();

		this -> setElementCnt(list -> getElementCnt() + 1);
		this -> setTypes(list -> getTypes());
		this -> addType(expr -> getExprType());
	}
	else {
		m_errorHandler();
	}
}