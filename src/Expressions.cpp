#include "Expressions.hpp"
#include "Leafs.hpp"
#include "Common.hpp"

void PrimaryExpression::check() {
    if(checkChildren<NodeType::LeafIdn>()) {
        LeafIdn *l = static_cast<LeafIdn *>(m_children[0].get());
        m_exprType = Global::identifierTable[l -> getLexicalUnit()].exprType;
        m_isLValue = Global::identifierTable[l -> getLexicalUnit()].LValue;
    } else if(checkChildren<NodeType::LeafNum>()) {
        m_exprType = ExprType::Int;
        m_isLValue = false;
    } else if(checkChildren<NodeType::LeafChar>()) {
        m_exprType = ExprType::Char;
        m_isLValue = false;
    } else if(checkChildren<NodeType::LeafCharArray>()) {
        m_exprType = ExprType::ArrayConstChar;
        m_isLValue = false;
    } else if(checkChildren<NodeType::LeafLeftBracket, NodeType::Expression, NodeType::LeafRightBracket>()){
        Expression *expr = static_cast<Expression*>(m_children[1].get());

        expr -> check();

        m_exprType = expr -> getExprType();
        m_isLValue = expr -> isLValue();
    } else {
        m_errorHandler();
    }
}

void Expression::check() {
    if(checkChildren<NodeType::AssignmentExpression>()) {
        AssignmentExpression *aExpr = static_cast<AssignmentExpression*>(m_children[0].get());
        aExpr -> check();

        m_exprType = aExpr -> getExprType();
        m_isLValue = aExpr -> isLValue();
    } else if(checkChildren<NodeType::Expression, NodeType::LeafComma, NodeType::AssignmentExpression>()) {
        m_children[0] -> check();
        AssignmentExpression *aExpr = static_cast<AssignmentExpression*>(m_children[2].get());
        aExpr -> check();

        m_exprType = aExpr -> getExprType();
        m_isLValue = false;
    } else {
        m_errorHandler();
    }
}

void AssignmentExpression::check() {
    if(checkChildren<NodeType::LogicalOrExpression>()) {
        LogicalOrExpression *lorExpr = static_cast<LogicalOrExpression*>(m_children[0].get());
        lorExpr -> check();

        m_exprType = lorExpr -> getExprType();
        m_isLValue = lorExpr -> isLValue();
    } else if (checkChildren<NodeType::PostfixExpression, NodeType::LeafAssignment, NodeType::AssignmentExpression>()){
        PostfixExpression *pExpr = static_cast<PostfixExpression*>(m_children[0].get());
        AssignmentExpression *aExpr = static_cast<AssignmentExpression*>(m_children[2].get());

        pExpr -> check();
        pExpr -> setLValue(true);
        aExpr -> check();
        if(!implicitlyConvertible(aExpr -> getExprType(), pExpr -> getExprType()))
            m_errorHandler();

        m_exprType = pExpr -> getExprType();
        m_isLValue = false;
    } else {
        m_errorHandler();
    }
}

void LogicalOrExpression::check() {
    if(checkChildren<NodeType::LogicalAndExpression>()) {
        LogicalAndExpression *landExpr = static_cast<LogicalAndExpression*>(m_children[0].get());
        landExpr -> check();

        m_exprType = landExpr -> getExprType();
        m_isLValue = landExpr -> isLValue();
    } else if(checkChildren<NodeType::LogicalOrExpression , NodeType::LeafLogOr, NodeType::LogicalAndExpression>()) {
        LogicalOrExpression *lorExpr = static_cast<LogicalOrExpression*>(m_children[0].get());
        LogicalAndExpression *landExpr = static_cast<LogicalAndExpression*>(m_children[2].get());

        lorExpr -> check();
        if(!implicitlyConvertible(lorExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        landExpr -> check();
        if(!implicitlyConvertible(landExpr -> getExprType(), ExprType::Int))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
    } else {
        m_errorHandler();
    }
}

void LogicalAndExpression::check() {
    if(checkChildren<NodeType::BitwiseOrExpression>()) {
        BitwiseOrExpression *borExpr = static_cast<BitwiseOrExpression*>(m_children[0].get());
        borExpr -> check();

        m_exprType = borExpr -> getExprType();
        m_isLValue = borExpr -> isLValue(); 
    } else if(checkChildren<NodeType::LogicalAndExpression, NodeType::LeafLogAnd, NodeType::BitwiseOrExpression>()) {
        LogicalAndExpression *landExpr = static_cast<LogicalAndExpression*>(m_children[0].get());
        BitwiseOrExpression *borExpr = static_cast<BitwiseOrExpression*>(m_children[2].get());

        landExpr -> check();
        if(!implicitlyConvertible(landExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        borExpr -> check();
        if(!implicitlyConvertible(borExpr -> getExprType(), ExprType::Int))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
    } else {
        m_errorHandler();
    }
}

void BitwiseOrExpression::check() {
    if(checkChildren<NodeType::BitwiseXorExpression>()) {
        BitwiseXorExpression *bxorExpr = static_cast<BitwiseXorExpression*>(m_children[0].get());
        bxorExpr -> check();

        m_exprType = bxorExpr -> getExprType();
        m_isLValue = bxorExpr -> isLValue();
    } else if(checkChildren<NodeType::BitwiseOrExpression, NodeType::LeafBitOr, NodeType::BitwiseXorExpression>()) {
        BitwiseOrExpression *borExpr = static_cast<BitwiseOrExpression*>(m_children[0].get());
        BitwiseXorExpression *bxorExpr = static_cast<BitwiseXorExpression*>(m_children[2].get());

        borExpr -> check();
        if(!implicitlyConvertible(borExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        bxorExpr -> check();
        if(!implicitlyConvertible(bxorExpr -> getExprType(), ExprType::Int))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
    } else {
        m_errorHandler();
    }
}

void BitwiseXorExpression::check() {
    if(checkChildren<NodeType::BitwiseAndExpression>()) {
        BitwiseAndExpression *bandExpr = static_cast<BitwiseAndExpression*>(m_children[0].get());
        bandExpr -> check();

        m_exprType = bandExpr -> getExprType();
        m_isLValue = bandExpr -> isLValue();
    } else if(checkChildren<NodeType::BitwiseXorExpression, NodeType::LeafBitXor, NodeType::BitwiseAndExpression>()) {
        BitwiseXorExpression *bxorExpr = static_cast<BitwiseXorExpression*>(m_children[0].get());
        BitwiseAndExpression *bandExpr = static_cast<BitwiseAndExpression*>(m_children[2].get());

        bxorExpr -> check();
        if(!implicitlyConvertible(bxorExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        bandExpr -> check();
        if(!implicitlyConvertible(bandExpr -> getExprType(), ExprType::Int))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
    } else {
        m_errorHandler();
    }
}

void BitwiseAndExpression::check() {
    if(checkChildren<NodeType::EqualsExpression>()) {
        EqualsExpression *eqExpr = static_cast<EqualsExpression*>(m_children[0].get());
        eqExpr -> check();

        m_exprType = eqExpr -> getExprType();
        m_isLValue = eqExpr -> isLValue();
    } else if(checkChildren<NodeType::BitwiseAndExpression, NodeType::LeafBitAnd, NodeType::EqualsExpression>()) {
        BitwiseAndExpression *bandExpr = static_cast<BitwiseAndExpression*>(m_children[0].get());
        EqualsExpression *eqExpr = static_cast<EqualsExpression*>(m_children[2].get());

        bandExpr -> check();
        if(!implicitlyConvertible(bandExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        eqExpr -> check();
        if(!implicitlyConvertible(eqExpr -> getExprType(), ExprType::Int))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
    } else {
        m_errorHandler();
    }
}