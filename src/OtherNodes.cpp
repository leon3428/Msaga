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