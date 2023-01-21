#include "Commands.hpp"
#include "Leafs.hpp"
#include "Common.hpp"
#include "Declarations.hpp"
#include "Expressions.hpp"
#include "OtherNodes.hpp"
#include <string>
#include <iostream>

void FunctionDefinition::check() {
    if(checkChildren<NodeType::TypeName, NodeType::LeafIdn, NodeType::LeafLeftBracket,
	   NodeType::LeafKwVoid, NodeType::LeafRightBracket, NodeType::ComplexCommand>())
	{
		TypeName *tn = static_cast<TypeName*>(m_children[0].get());
		tn -> check();
		if(Msaga::isConst(tn -> getExprType()))
			m_errorHandler();

		LeafIdn *lIdn = static_cast<LeafIdn*>(m_children[1].get());

		Identifier *idn = m_localContext -> getIdentifier(lIdn -> getLexicalUnit());
		if(idn != nullptr) {
			if(idn -> exprType != ExprType::Function || idn -> defined)
				m_errorHandler();

			if(idn -> functionType -> returnType != tn -> getExprType() ||
			   idn -> functionType -> argumentsTypes.size() != 1 ||
			   idn -> functionType -> argumentsTypes[0] != ExprType::Void)
			{
				m_errorHandler();
			}
			idn -> defined = true;
		} else {
			m_localContext -> getParent() -> declareFunction(lIdn -> getLexicalUnit(), true, {{ExprType::Void}, tn -> getExprType()});
		}

		m_children[5] -> check();

	} else if(checkChildren<NodeType::TypeName, NodeType::LeafIdn, NodeType::LeafLeftBracket,
	   NodeType::ParameterList, NodeType::LeafRightBracket, NodeType::ComplexCommand>())
	{
		TypeName *tn = static_cast<TypeName*>(m_children[0].get());
		tn -> check();
		if(Msaga::isConst(tn -> getExprType()))
			m_errorHandler();

		LeafIdn *lIdn = static_cast<LeafIdn*>(m_children[1].get());
		Identifier *idn = m_localContext -> getIdentifier(lIdn -> getLexicalUnit());
		if(idn != nullptr && (idn -> exprType != ExprType::Function || idn -> defined))
			m_errorHandler();
		
		ParameterList *pl = static_cast<ParameterList*>(m_children[3].get());
		pl -> check();

		if(idn != nullptr) {
			if(idn -> functionType -> returnType != tn -> getExprType() ||
			   idn -> functionType -> argumentsTypes.size() != pl -> getSize() ||
			   idn -> functionType -> argumentsTypes != pl -> getTypes())
			{
				m_errorHandler();
			}

			idn -> defined = true;
		} else {
			m_localContext -> getParent() -> declareFunction(lIdn -> getLexicalUnit(), true, {pl -> getTypes(), tn -> getExprType()});
			for(size_t i = 0;i < pl -> getSize();i++) {
				m_localContext -> declareVariable(pl -> getName(i), pl -> getType(i));
			}
		}
		m_children[5] -> check();

	} else {
		m_errorHandler();
	}
}

void FunctionDefinition::generateCode(std::ostream &stream) {
	int localVarSpace = 0;
	Msaga::blockOffsetHelper(m_localContext, localVarSpace);

	if(checkChildren<NodeType::TypeName, NodeType::LeafIdn, NodeType::LeafLeftBracket,
	   NodeType::LeafKwVoid, NodeType::LeafRightBracket, NodeType::ComplexCommand>())
	{
		LeafIdn *l = static_cast<LeafIdn*>(m_children[1].get());
		stream << "func" << m_localContext -> getIdentifier(l -> getLexicalUnit()) -> id << ' '; 
		stream << '\t' << "SUB SP, 0" << std::hex << localVarSpace << ", SP\n";
		Msaga::allChildrenGenerateCode(stream, this);
		stream << '\t' << "ADD SP, 0" << std::hex << localVarSpace << ", SP\n";
		stream << '\t' << "RET\n";
	} else if(checkChildren<NodeType::TypeName, NodeType::LeafIdn, NodeType::LeafLeftBracket,
	   NodeType::ParameterList, NodeType::LeafRightBracket, NodeType::ComplexCommand>())
	{

	} else {
		Msaga::allChildrenGenerateCode(stream, this);
	}
}

void ParameterList::check() {
	if(checkChildren<NodeType::ParameterDeclaration>()) {
		ParameterDeclaration *decl = static_cast<ParameterDeclaration*>(m_children[0].get());
		decl -> check();
		m_names = { decl -> getName() };
		m_types = { decl -> getExprType() };

	} else if(checkChildren<NodeType::ParameterList, NodeType::LeafComma, NodeType::ParameterDeclaration>()) {
		ParameterList *list = static_cast<ParameterList*>(m_children[0].get());
		list -> check();
		ParameterDeclaration *decl = static_cast<ParameterDeclaration *>(m_children[2].get());
		decl -> check();

		for(const std::string &name : m_names)
			if(name == decl -> getName())
				m_errorHandler();

		m_types = list -> getTypes();
		m_types.push_back(decl -> getExprType());
		m_names = list -> getNames();
		m_names.push_back(decl -> getName());
	} else{
		m_errorHandler();
	}
}

void ParameterDeclaration::check() {
	if(checkChildren<NodeType::TypeName, NodeType::LeafIdn>()) {
		TypeName *tn = static_cast<TypeName*>(m_children[0].get());
		tn -> check();
		if(tn -> getExprType() == ExprType::Void)
			m_errorHandler();

		LeafIdn *idn = static_cast<LeafIdn*>(m_children[1].get());

		m_exprType = tn -> getExprType();
		m_name = idn -> getLexicalUnit();
	} else if(checkChildren<NodeType::TypeName, NodeType::LeafIdn, NodeType::LeafLeftSquareBracket, NodeType::LeafRightSquareBracket>()) {
		TypeName *tn = static_cast<TypeName *>(m_children[0].get());
		tn -> check();
		if(tn -> getExprType() == ExprType::Void)
			m_errorHandler();
		
		LeafIdn *idn = static_cast<LeafIdn *>(m_children[1].get());

		m_exprType = Msaga::baseTypeToArray(tn -> getExprType());
		m_name = idn -> getLexicalUnit();
	} else{
		m_errorHandler();
	}
}

void DeclarationList::check() {
	if(checkChildren<NodeType::Declaration>()) {
		m_children[0] -> check();
	} else if(checkChildren<NodeType::DeclarationList, NodeType::Declaration>()) {
		m_children[0] -> check();
		m_children[1] -> check();
	} else{
		m_errorHandler();
	}
}

void Declaration::check() {
	if(checkChildren<NodeType::TypeName, NodeType::DeclaratorInitList, NodeType::LeafSemicolon>()) {
		TypeName *tn = static_cast<TypeName*>(m_children[0].get());
		tn -> check();

		DeclaratorInitList *declList = static_cast<DeclaratorInitList*>(m_children[1].get());
		declList -> setNtype(tn -> getExprType());
		declList -> check();
	} else{
		m_errorHandler();
	}
}

void DeclaratorInitList::check() {
	if(checkChildren<NodeType::InitDeclarator>()) {
		InitDeclarator *decl = static_cast<InitDeclarator *>(m_children[0].get());
		decl -> setNtype(m_ntype);
		decl -> check();
	} else if(checkChildren<NodeType::DeclaratorInitList, NodeType::LeafComma, NodeType::InitDeclarator>()) {
		DeclaratorInitList *declList = static_cast<DeclaratorInitList*>(m_children[0].get());				
		declList -> setNtype(m_ntype);
		declList -> check();
		InitDeclarator *declInit = static_cast<InitDeclarator*>(m_children[2].get());
		declInit -> setNtype(m_ntype);
		declInit -> check();
	} else{
		m_errorHandler();
	}
}

void InitDeclarator::check() {
	if(checkChildren<NodeType::DirectDeclarator>()) {
		DirectDeclarator *decl = static_cast<DirectDeclarator *>(m_children[0].get());
		decl -> setNtype(m_ntype);
		decl -> check();
		if(Msaga::isConst(decl -> getExprType()) || Msaga::isConstArray(decl -> getExprType()))
			m_errorHandler();

	} else if(checkChildren<NodeType::DirectDeclarator, NodeType::LeafAssignment, NodeType::Initializer>()) {
		DirectDeclarator *decl = static_cast<DirectDeclarator *>(m_children[0].get());
		decl -> setNtype(m_ntype);
		decl -> check();

		Initializer *init = static_cast<Initializer *>(m_children[2].get());
		init -> check();

		if(Msaga::isConst(decl -> getExprType()) || Msaga::isNumber(decl -> getExprType())) {
			if(init -> getElementCount() != 1 || !Msaga::implicitlyConvertible(init -> getType(0), decl -> getExprType()))
				m_errorHandler();
		} else if(Msaga::isArrayType(decl -> getExprType())) {
			if(!init -> reducesToCharArray())
				m_errorHandler();
			if(init -> getElementCount() > decl -> getElementCnt())
				m_errorHandler();
			for(int i = 0;i < init -> getElementCount(); i++) {
				if(!Msaga::implicitlyConvertible(init -> getType(i), Msaga::arrayBaseType(decl -> getExprType())))
					m_errorHandler();
			}
		} else {
			m_errorHandler();
		}
	} else{
		m_errorHandler();
	}
}

void InitDeclarator::generateCode(std::ostream &stream) {
	if(checkChildren<NodeType::DirectDeclarator, NodeType::LeafAssignment, NodeType::Initializer>()) {
		m_children[2] -> generateCode(stream);

		DirectDeclarator *dd = static_cast<DirectDeclarator*>(m_children[0].get());
		if(dd -> getChildrenCnt() == 1) {
			stream << '\t' << "POP R0\n";
			LeafIdn *lIdn = static_cast<LeafIdn*>(dd -> getChild(0));
			auto idn = m_localContext -> getIdentifier(lIdn -> getLexicalUnit());
			Msaga::storeRegToVar(stream, this, "R0", idn -> name, "R6");
		} else {
			Initializer *initializer = static_cast<Initializer*>(m_children[2].get());
			LeafIdn *lIdn = static_cast<LeafIdn*>(dd -> getChild(0));
			auto idn = m_localContext -> getIdentifier(lIdn -> getLexicalUnit());
			
			if(initializer -> getChildrenCnt() == 1) {
				// const char array
				int tmpId = Msaga::getTmpLabelId();

				stream << '\t' << "MOVE R6, R0\n"; // counter
				stream << "tmp" << tmpId << '\n'; // loop start
				stream << '\t' << "POP R1" << '\n';
				Msaga::storeRegToVar(stream, this, "R1", idn -> name, "R0");
				stream << '\t' << "ADD R0, 4, R0\n";
				stream << '\t' << "CMP R1, 0\n";
				stream << '\t' << "JP_NE tmp" << tmpId << '\n';
			} else {
				// initializer list
				JoinExpressionList *jel = static_cast<JoinExpressionList*>(initializer -> getChild(1));
				int tmpId = Msaga::getTmpLabelId();

				Msaga::writeConstToReg(stream, "R0", jel -> getElementCount() * 4); // counter
				stream << "\t" << "MOVE 0, R3\n";
				stream << "tmp" << tmpId << '\n'; // loop start
				stream << '\t' << "POP R1\n";
				stream << '\t' << "ADD R6, R3, R2\n";
				Msaga::storeRegToVar(stream, this, "R1", idn -> name, "R2");
				stream << '\t' << "ADD R3, 4, R3\n";
				stream << '\t' << "CMP R3, R0\n";
				stream << '\t' << "JP_NE tmp" << tmpId << '\n';
			}
		}

	} else{
		Msaga::allChildrenGenerateCode(stream, this);
	}
}

void DirectDeclarator::check() {
	if(checkChildren<NodeType::LeafIdn>()) {
		if(m_ntype == ExprType::Void)
			m_errorHandler();
		
		LeafIdn *idn = static_cast<LeafIdn *>(m_children[0].get());
		if(m_localContext -> inLocalScope(idn -> getLexicalUnit()))
			m_errorHandler();
		
		m_exprType = m_ntype;

		m_localContext -> declareVariable(idn -> getLexicalUnit(), m_exprType);
	} else if(checkChildren<NodeType::LeafIdn, NodeType::LeafLeftSquareBracket, NodeType::LeafNum, NodeType::LeafRightSquareBracket>()) {
		if(m_ntype == ExprType::Void)
			m_errorHandler();
		LeafIdn *idn = static_cast<LeafIdn *>(m_children[0].get());
		if(m_localContext -> inLocalScope(idn -> getLexicalUnit()))
			m_errorHandler();

		LeafNum *num = static_cast<LeafNum *>(m_children[2].get()); 
		int cnt = std::stoi(num -> getLexicalUnit());
		if(cnt <= 0 || cnt > 1024)
			m_errorHandler();

		m_elementCnt = cnt;
		m_exprType = Msaga::baseTypeToArray(m_ntype);
		m_localContext -> declareArrayVariable(idn -> getLexicalUnit(), m_exprType, cnt);

	} else if(checkChildren<NodeType::LeafIdn, NodeType::LeafLeftBracket, NodeType::LeafKwVoid, NodeType::LeafRightBracket>()) {
		LeafIdn *idnLeaf = static_cast<LeafIdn *>(m_children[0].get());
		if(m_localContext -> inLocalScope(idnLeaf -> getLexicalUnit())) {
			Identifier *idn = m_localContext -> getIdentifier(idnLeaf -> getLexicalUnit());
			if(idn -> exprType != ExprType::Function || *(idn -> functionType) != Msaga::FunctionType({ExprType::Void}, m_ntype))
				m_errorHandler();	
		} else {
			m_localContext -> declareFunction(idnLeaf -> getLexicalUnit(), false, {{ExprType::Void}, m_ntype});
		}
		m_exprType = ExprType::Function; // Check

	} else if(checkChildren<NodeType::LeafIdn, NodeType::LeafLeftBracket, NodeType::ParameterList, NodeType::LeafRightBracket>()) {
		ParameterList *list = static_cast<ParameterList *>(m_children[2].get());
		list -> check();
		
		LeafIdn *idnLeaf = static_cast<LeafIdn *>(m_children[0].get());

		if(m_localContext -> inLocalScope(idnLeaf -> getLexicalUnit())) {
			Identifier *idn = m_localContext -> getIdentifier(idnLeaf -> getLexicalUnit());
			if(idn -> exprType != ExprType::Function || *(idn -> functionType) != Msaga::FunctionType(list -> getTypes(), m_ntype))
				m_errorHandler();	
		} else {
			m_localContext -> declareFunction(idnLeaf -> getLexicalUnit(), false, {list -> getTypes(), m_ntype});
		}
		m_exprType = ExprType::Function; // Check
	}
	else {
		m_errorHandler();
	}
}

void Initializer::check() {
	if(checkChildren<NodeType::AssignmentExpression>()) {
		m_reducesToCharArray = false;
		AssignmentExpression *expr = static_cast<AssignmentExpression *>(m_children[0].get());
		expr -> check();
		
		if(expr -> isCharacterArray()) {
			m_types = {expr -> getCharacterArrayLength() + 1, ExprType::Char };
			m_reducesToCharArray = true;
		} else {
			m_types = {expr -> getExprType() };
		}
	} else if(checkChildren<NodeType::LeafLeftCurlyBracket, NodeType::JoinExpressionList, NodeType::LeafRightCurlyBracket>()) {
		m_reducesToCharArray = true;
		JoinExpressionList *list = static_cast<JoinExpressionList *>(m_children[1].get());
		list -> check();

		m_types = list -> getTypes();
	}
	else {
		m_errorHandler();
	}
}

void JoinExpressionList::check() {
	if(checkChildren<NodeType::AssignmentExpression>()) {
		AssignmentExpression *expr = static_cast<AssignmentExpression *>(m_children[0].get());
		expr -> check();

		m_types = {expr -> getExprType()};
	} else if(checkChildren<NodeType::JoinExpressionList, NodeType::LeafComma, NodeType::AssignmentExpression>()) {
		JoinExpressionList *list = static_cast<JoinExpressionList *>(m_children[0].get());
		list -> check();
		AssignmentExpression *expr = static_cast<AssignmentExpression *>(m_children[2].get());
		expr -> check();

		m_types = list -> getTypes();
		m_types.push_back(expr -> getExprType());
	}
	else {
		m_errorHandler();
	}
}

void JoinExpressionList::generateCode(std::ostream &stream) {
	if(checkChildren<NodeType::JoinExpressionList, NodeType::LeafComma, NodeType::AssignmentExpression>()) {
		m_children[2] -> generateCode(stream);
		m_children[0] -> generateCode(stream);
	}
	else {
		Msaga::allChildrenGenerateCode(stream, this);
	}
}