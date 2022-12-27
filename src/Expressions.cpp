#include "Expressions.hpp"
#include "Leafs.hpp"
#include "Global.hpp"

void PrimaryExpression::check() {
    if(checkChildren<NodeType::LeafIdn>()) {
        LeafIdn *l = static_cast<LeafIdn *>(m_children[0].get());
        m_exprType = Global::identifierTable[l -> getLexicalUnit()].exprType;
        m_isLValue = Global::identifierTable[l -> getLexicalUnit()].LValue;
    } else if(checkChildren<NodeType::LeafNum>()) {
        m_exprType = {PrimitiveExprType::Int};
        m_isLValue = false;
    } else if(checkChildren<NodeType::LeafChar>()) {
        m_exprType = {PrimitiveExprType::Char};
        m_isLValue = false;
    } else if(checkChildren<NodeType::LeafCharArray>()) {
        m_exprType = {PrimitiveExprType::Array, PrimitiveExprType::Const, PrimitiveExprType::Char};
        m_isLValue = false;
    } else if(checkChildren<NodeType::LeafLeftBracket, NodeType::Expression, NodeType::LeafRightBracket>()){
        // TODO: implement this case
    } else {
        m_errorHandler();
    }
}