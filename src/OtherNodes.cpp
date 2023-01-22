#include "OtherNodes.hpp"
#include "Expressions.hpp"

void TypeName::check() {
    if(checkChildren<NodeType::TypeSpecifier>()) {
        TypeSpecifier *ts = static_cast<TypeSpecifier*>(m_children[0].get());
        ts -> check();
        m_exprType = ts -> getExprType();
    } else if(checkChildren<NodeType::LeafKwConst, NodeType::TypeSpecifier>()) {
        TypeSpecifier *ts = static_cast<TypeSpecifier*>(m_children[1].get());
        
        ts -> check();
        if(ts -> getExprType() == ExprType::Int)
            m_exprType = ExprType::ConstInt;
        else if(ts -> getExprType() == ExprType::Char)
            m_exprType = ExprType::ConstChar;
        else {
            m_errorHandler();
        }
    } else {
        m_errorHandler();
    }
}

void TypeSpecifier::check() {
    if(checkChildren<NodeType::LeafKwVoid>()) {
        m_exprType = ExprType::Void;
    } else  if(checkChildren<NodeType::LeafKwChar>()) {
        m_exprType = ExprType::Char;
    } else  if(checkChildren<NodeType::LeafKwInt>()) {
        m_exprType = ExprType::Int;
    } else {
        m_errorHandler();
    }
}

void UnaryOperator::check() {}

void UnaryOperator::generateCode(std::ostream &stream) {
	if(checkChildren<NodeType::LeafPlus>()){
		Msaga::allChildrenGenerateCode(stream, this);
	} else if(checkChildren<NodeType::LeafMinus>()) {
		Msaga::allChildrenGenerateCode(stream, this);
		stream << "\tPOP r5\n";
		stream << "\tMOVE -1, R0\n";
		stream << "\tXOR r5, r0, r5\n";
		stream << "\tADD r5, 1, r5\n";
		stream << "\tPUSH r5\n";
	} else if(checkChildren<NodeType::LeafTilde>()) {
		Msaga::allChildrenGenerateCode(stream, this);
		stream << "\tPOP r5\n";
		stream << "\tMOVE -1, R0\n";
		stream << "\tXOR r5, r0, r5\n";
		stream << "\tPUSH r5\n";
	} else if(checkChildren<NodeType::LeafNeg>()){
		Msaga::allChildrenGenerateCode(stream, this);
		stream << "\tPOP r0\n";
		stream << "\tMOVE 0, r5\n";
		stream << "\tCMP r0, 0\n";
		stream << "\tCALL_Z unaryoperj\n";
		stream << "\tPUSH r5\n";
	} else {
		Msaga::allChildrenGenerateCode(stream, this);
	}
}

void ArgumentList::check() {
    if(checkChildren<NodeType::AssignmentExpression>()) {
        AssignmentExpression *aExpr = static_cast<AssignmentExpression*>(m_children[0].get());

        aExpr -> check();
        m_exprTypes.push_back(aExpr -> getExprType());
    } else if(checkChildren<NodeType::ArgumentList, NodeType::LeafComma, NodeType::AssignmentExpression>()) {
        ArgumentList *al = static_cast<ArgumentList*>(m_children[0].get());
        AssignmentExpression *aExpr = static_cast<AssignmentExpression*>(m_children[2].get());

        al -> check();
        aExpr -> check();

        m_exprTypes = al -> getExprTypes();
        m_exprTypes.push_back(aExpr -> getExprType());
    } else {
        m_errorHandler();
    }
}

void ArgumentList::generateCode(std::ostream &stream) {
     if(checkChildren<NodeType::AssignmentExpression>()) {
        AssignmentExpression *aExpr = static_cast<AssignmentExpression*>(m_children[0].get());

        auto idn = aExpr -> getIdentifier();
        if(idn != nullptr && Msaga::isArrayType(idn -> exprType)) {
            auto [localOffset, isGlobal] = m_localContext-> getOffset(aExpr -> getIdentifier() -> name);
            if(isGlobal) {
                stream << '\t' << "MOVE "<< std::hex << 0x40000 - localOffset << ", R0\n";
                stream << '\t' << "PUSH R0\n";
            } else if(localOffset > 0) {
                stream << '\t' << "SUB R6, 0" << std::hex << localOffset << ", R0\n";
                stream << '\t' << "PUSH R0\n";
            } else {
                stream << '\t' << "LOAD R0, (R6+0" << std::hex << localOffset * -1 << ")\n";
                stream << '\t' << "PUSH R0\n";
            }
           
        } else {
            m_children[0] -> generateCode(stream);
        }
    } else if(checkChildren<NodeType::ArgumentList, NodeType::LeafComma, NodeType::AssignmentExpression>()) {
        AssignmentExpression *aExpr = static_cast<AssignmentExpression*>(m_children[2].get());

        auto idn = aExpr -> getIdentifier();
        if(idn != nullptr && Msaga::isArrayType(idn -> exprType)) {
            auto [localOffset, isGlobal] = m_localContext-> getOffset(aExpr -> getIdentifier() -> name);
            if(isGlobal) {
                stream << '\t' << "MOVE "<< std::hex << 0x40000 - localOffset << ", R0\n";
                stream << '\t' << "PUSH R0\n";
            } else if(localOffset > 0) {
                stream << '\t' << "SUB R6, 0" << std::hex << localOffset << ", R0\n";
                stream << '\t' << "PUSH R0\n";
            } else {
                stream << '\t' << "LOAD R0, (R6+0" << std::hex << localOffset * -1 << ")\n";
                stream << '\t' << "PUSH R0\n";
            }
        } else {
            m_children[2] -> generateCode(stream);
        }
		m_children[0] -> generateCode(stream);
	} else{
		Msaga::allChildrenGenerateCode(stream, this);
	}
}