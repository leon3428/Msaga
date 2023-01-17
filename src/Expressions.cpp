#include "Expressions.hpp"
#include "Leafs.hpp"
#include "OtherNodes.hpp"
#include <string>

void PrimaryExpression::check() {
    if(checkChildren<NodeType::LeafIdn>()) {
        LeafIdn *l = static_cast<LeafIdn *>(m_children[0].get());

        m_idn = m_localContext -> getIdentifier(l -> getLexicalUnit());
        if(m_idn == nullptr)
            m_errorHandler();

        if(m_idn -> exprType == ExprType::Function)
            m_functionType = m_idn -> functionType;
        m_exprType = m_idn -> exprType;
        m_isLValue = m_idn -> exprType == ExprType::Int || m_idn -> exprType == ExprType::Char; // check
    } else if(checkChildren<NodeType::LeafNum>()) {
        LeafNum *l = static_cast<LeafNum *>(m_children[0].get());

        try {
            std::stol(l -> getLexicalUnit());
        } catch(...) {
            m_errorHandler();
        }

        if(std::stol(l -> getLexicalUnit()) < INT32_MIN|| std::stol(l -> getLexicalUnit()) >= INT32_MAX)
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
        m_idn = nullptr;
    } else if(checkChildren<NodeType::LeafCharacter>()) {
        LeafCharacter *l = static_cast<LeafCharacter *>(m_children[0].get());
        if(!Msaga::isValidChar(l -> getLexicalUnit()))
            m_errorHandler();

        m_exprType = ExprType::Char;
        m_isLValue = false;
        m_idn = nullptr;
    } else if(checkChildren<NodeType::LeafCharArray>()) {
        LeafCharArray *l = static_cast<LeafCharArray*>(m_children[0].get());
        if(!Msaga::isValidCharArray(l -> getLexicalUnit()))
            m_errorHandler();

        m_exprType = ExprType::ArrayConstChar;
        m_isLValue = false;
        m_idn = nullptr;
    } else if(checkChildren<NodeType::LeafLeftBracket, NodeType::Expression, NodeType::LeafRightBracket>()){
        Expression *expr = static_cast<Expression*>(m_children[1].get());
        expr -> check();
        m_idn = expr -> getIdentifier();

        m_exprType = expr -> getExprType();
        m_isLValue = expr -> isLValue();
    } else {
        m_errorHandler();
    }
}

void PrimaryExpression::generateCode(std::ostream &stream) {
    if(checkChildren<NodeType::LeafIdn>()) {
        LeafIdn *l = static_cast<LeafIdn *>(m_children[0].get());
        auto idn = m_localContext -> getIdentifier(l -> getLexicalUnit());

        stream << '\t' << "LOAD R0, (R6 + 0" << std::hex << idn -> offset << ")\n";
        stream << '\t' << "PUSH R0\n";
    } else if(checkChildren<NodeType::LeafNum>()) {
        LeafNum *l = static_cast<LeafNum *>(m_children[0].get());

        Msaga::writeConstToReg(stream, "R0", std::stoi(l -> getLexicalUnit()));
        stream << '\t' << "PUSH R0\n";
    } else if(checkChildren<NodeType::LeafCharacter>()) {
        LeafCharacter *l = static_cast<LeafCharacter*>(m_children[0].get());

        Msaga::writeConstToReg(stream, "R0", static_cast<int>(l -> getLexicalUnit()[1]));
        stream << '\t' << "PUSH R0\n";
    } else if(checkChildren<NodeType::LeafCharArray>()) {
        LeafCharArray *l = static_cast<LeafCharArray*>(m_children[0].get());
        std::string_view s = l -> getLexicalUnit();
        for(size_t i = s.size() - 2; i >= 1; i--) {
            Msaga::writeConstToReg(stream, "R0", static_cast<int>(s[i]));
            stream << '\t' << "PUSH R0\n";
        }
        Msaga::writeConstToReg(stream, "R0", 0);
        stream << '\t' << "PUSH R0\n";
    } else {
        Msaga::allChildrenGenerateCode(stream, this);
    }
}

void Expression::check() {
    if(checkChildren<NodeType::AssignmentExpression>()) {
        AssignmentExpression *aExpr = static_cast<AssignmentExpression*>(m_children[0].get());
        aExpr -> check();
        m_idn = aExpr -> getIdentifier();

        m_exprType = aExpr -> getExprType();
        m_isLValue = aExpr -> isLValue();
    } else if(checkChildren<NodeType::Expression, NodeType::LeafComma, NodeType::AssignmentExpression>()) {
        m_children[0] -> check();
        AssignmentExpression *aExpr = static_cast<AssignmentExpression*>(m_children[2].get());
        aExpr -> check();
        m_idn = nullptr;

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
        m_idn = lorExpr -> getIdentifier();

        m_exprType = lorExpr -> getExprType();
        m_isLValue = lorExpr -> isLValue();
    } else if (checkChildren<NodeType::PostfixExpression, NodeType::LeafAssignment, NodeType::AssignmentExpression>()){
        PostfixExpression *pExpr = static_cast<PostfixExpression*>(m_children[0].get());
        AssignmentExpression *aExpr = static_cast<AssignmentExpression*>(m_children[2].get());
        m_idn = nullptr;

        pExpr -> check();
        if(!pExpr -> isLValue())
            m_errorHandler();
        aExpr -> check();
        if(!Msaga::implicitlyConvertible(aExpr -> getExprType(), pExpr -> getExprType()))
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
        m_idn = landExpr -> getIdentifier();

        m_exprType = landExpr -> getExprType();
        m_isLValue = landExpr -> isLValue();
    } else if(checkChildren<NodeType::LogicalOrExpression , NodeType::LeafLogOr, NodeType::LogicalAndExpression>()) {
        LogicalOrExpression *lorExpr = static_cast<LogicalOrExpression*>(m_children[0].get());
        LogicalAndExpression *landExpr = static_cast<LogicalAndExpression*>(m_children[2].get());

        lorExpr -> check();
        if(!Msaga::implicitlyConvertible(lorExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        landExpr -> check();
        if(!Msaga::implicitlyConvertible(landExpr -> getExprType(), ExprType::Int))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
        m_idn = nullptr;
    } else {
        m_errorHandler();
    }
}

void LogicalAndExpression::check() {
    if(checkChildren<NodeType::BitwiseOrExpression>()) {
        BitwiseOrExpression *borExpr = static_cast<BitwiseOrExpression*>(m_children[0].get());
        borExpr -> check();
        m_idn = borExpr -> getIdentifier();

        m_exprType = borExpr -> getExprType();
        m_isLValue = borExpr -> isLValue(); 
    } else if(checkChildren<NodeType::LogicalAndExpression, NodeType::LeafLogAnd, NodeType::BitwiseOrExpression>()) {
        LogicalAndExpression *landExpr = static_cast<LogicalAndExpression*>(m_children[0].get());
        BitwiseOrExpression *borExpr = static_cast<BitwiseOrExpression*>(m_children[2].get());

        landExpr -> check();
        if(!Msaga::implicitlyConvertible(landExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        borExpr -> check();
        if(!Msaga::implicitlyConvertible(borExpr -> getExprType(), ExprType::Int))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
        m_idn = nullptr;
    } else {
        m_errorHandler();
    }
}

void BitwiseOrExpression::check() {
    if(checkChildren<NodeType::BitwiseXorExpression>()) {
        BitwiseXorExpression *bxorExpr = static_cast<BitwiseXorExpression*>(m_children[0].get());
        bxorExpr -> check();
        m_idn = bxorExpr -> getIdentifier();

        m_exprType = bxorExpr -> getExprType();
        m_isLValue = bxorExpr -> isLValue();
    } else if(checkChildren<NodeType::BitwiseOrExpression, NodeType::LeafBitOr, NodeType::BitwiseXorExpression>()) {
        BitwiseOrExpression *borExpr = static_cast<BitwiseOrExpression*>(m_children[0].get());
        BitwiseXorExpression *bxorExpr = static_cast<BitwiseXorExpression*>(m_children[2].get());

        borExpr -> check();
        if(!Msaga::implicitlyConvertible(borExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        bxorExpr -> check();
        if(!Msaga::implicitlyConvertible(bxorExpr -> getExprType(), ExprType::Int))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
        m_idn = nullptr;
    } else {
        m_errorHandler();
    }
}

void BitwiseXorExpression::check() {
    if(checkChildren<NodeType::BitwiseAndExpression>()) {
        BitwiseAndExpression *bandExpr = static_cast<BitwiseAndExpression*>(m_children[0].get());
        bandExpr -> check();
        m_idn = bandExpr -> getIdentifier();

        m_exprType = bandExpr -> getExprType();
        m_isLValue = bandExpr -> isLValue();
    } else if(checkChildren<NodeType::BitwiseXorExpression, NodeType::LeafBitXor, NodeType::BitwiseAndExpression>()) {
        BitwiseXorExpression *bxorExpr = static_cast<BitwiseXorExpression*>(m_children[0].get());
        BitwiseAndExpression *bandExpr = static_cast<BitwiseAndExpression*>(m_children[2].get());

        bxorExpr -> check();
        if(!Msaga::implicitlyConvertible(bxorExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        bandExpr -> check();
        if(!Msaga::implicitlyConvertible(bandExpr -> getExprType(), ExprType::Int))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
        m_idn = nullptr;
    } else {
        m_errorHandler();
    }
}

void BitwiseAndExpression::check() {
    if(checkChildren<NodeType::EqualsExpression>()) {
        EqualsExpression *eqExpr = static_cast<EqualsExpression*>(m_children[0].get());
        eqExpr -> check();
        m_idn = eqExpr -> getIdentifier();

        m_exprType = eqExpr -> getExprType();
        m_isLValue = eqExpr -> isLValue();
    } else if(checkChildren<NodeType::BitwiseAndExpression, NodeType::LeafBitAnd, NodeType::EqualsExpression>()) {
        BitwiseAndExpression *bandExpr = static_cast<BitwiseAndExpression*>(m_children[0].get());
        EqualsExpression *eqExpr = static_cast<EqualsExpression*>(m_children[2].get());

        bandExpr -> check();
        if(!Msaga::implicitlyConvertible(bandExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        eqExpr -> check();
        if(!Msaga::implicitlyConvertible(eqExpr -> getExprType(), ExprType::Int))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
        m_idn = nullptr;
    } else {
        m_errorHandler();
    }
}

void EqualsExpression::check() {
    if(checkChildren<NodeType::ComparisonExpression>()) {
        ComparisonExpression *cmpExpr = static_cast<ComparisonExpression*>(m_children[0].get());
        cmpExpr -> check();
        m_idn = cmpExpr -> getIdentifier();

        m_exprType = cmpExpr -> getExprType();
        m_isLValue = cmpExpr -> isLValue(); 
    } else if(checkChildren<NodeType::EqualsExpression, NodeType::LeafEq, NodeType::ComparisonExpression>() ||
              checkChildren<NodeType::EqualsExpression, NodeType::LeafNeq, NodeType::ComparisonExpression>()   ) {

        EqualsExpression *eqExpr = static_cast<EqualsExpression*>(m_children[0].get());
        ComparisonExpression *cmpExpr = static_cast<ComparisonExpression*>(m_children[2].get());

        eqExpr -> check();
        if(!Msaga::implicitlyConvertible(eqExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        cmpExpr -> check();
        if(!Msaga::implicitlyConvertible(cmpExpr -> getExprType(), ExprType::Int))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
        m_idn = nullptr;
    } else {
        m_errorHandler();
    }
}

void ComparisonExpression::check() {
    if(checkChildren<NodeType::AdditiveExpression>()) {
        AdditiveExpression *addExpr = static_cast<AdditiveExpression*>(m_children[0].get());
        addExpr -> check();
        m_idn = addExpr -> getIdentifier();

        m_exprType = addExpr -> getExprType();
        m_isLValue = addExpr -> isLValue();
    } else if(checkChildren<NodeType::ComparisonExpression, NodeType::LeafLt, NodeType::AdditiveExpression>() ||
              checkChildren<NodeType::ComparisonExpression, NodeType::LeafGt, NodeType::AdditiveExpression>() ||
              checkChildren<NodeType::ComparisonExpression, NodeType::LeafLte, NodeType::AdditiveExpression>() ||
              checkChildren<NodeType::ComparisonExpression, NodeType::LeafGte, NodeType::AdditiveExpression>()) 
    {
        ComparisonExpression *cmpExpr = static_cast<ComparisonExpression*>(m_children[0].get());
        AdditiveExpression *addExpr = static_cast<AdditiveExpression*>(m_children[2].get());

        cmpExpr -> check();
        if(!Msaga::implicitlyConvertible(cmpExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        addExpr -> check();
        if(!Msaga::implicitlyConvertible(addExpr -> getExprType(), ExprType::Int))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
        m_idn = nullptr;
    } else {
        m_errorHandler();
    }
}

void AdditiveExpression::check() {
    if(checkChildren<NodeType::MultiplicativeExpression>()) {
        MultiplicativeExpression *mulExpr = static_cast<MultiplicativeExpression*>(m_children[0].get());
        mulExpr -> check();
        m_idn = mulExpr -> getIdentifier();
        m_exprType = mulExpr -> getExprType();
        m_isLValue = mulExpr -> isLValue();
    } else if(checkChildren<NodeType::AdditiveExpression, NodeType::LeafPlus, NodeType::MultiplicativeExpression>() ||
              checkChildren<NodeType::AdditiveExpression, NodeType::LeafMinus, NodeType::MultiplicativeExpression>())
    {
        AdditiveExpression *addExpr = static_cast<AdditiveExpression*>(m_children[0].get());
        MultiplicativeExpression *mulExpr = static_cast<MultiplicativeExpression*>(m_children[2].get());

        addExpr -> check();
        if(!Msaga::implicitlyConvertible(addExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        mulExpr -> check();
        if(!Msaga::implicitlyConvertible(mulExpr -> getExprType(), ExprType::Int))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
        m_idn = nullptr;
    } else {
        m_errorHandler();
    }
}

void MultiplicativeExpression::check() {
    if(checkChildren<NodeType::CastExpression>()) {
        CastExpression *castExpr = static_cast<CastExpression*>(m_children[0].get());
        castExpr -> check();
        m_idn = castExpr -> getIdentifier();
        m_exprType = castExpr -> getExprType();
        m_isLValue = castExpr -> isLValue();
    } else if(checkChildren<NodeType::MultiplicativeExpression, NodeType::LeafMult, NodeType::CastExpression>() ||
              checkChildren<NodeType::MultiplicativeExpression, NodeType::LeafDiv, NodeType::CastExpression>() ||
              checkChildren<NodeType::MultiplicativeExpression, NodeType::LeafMod, NodeType::CastExpression>())
    {
        MultiplicativeExpression *mulExpr = static_cast<MultiplicativeExpression*>(m_children[0].get());
        CastExpression *castExpr = static_cast<CastExpression*>(m_children[2].get());

        mulExpr -> check();
        if(!Msaga::implicitlyConvertible(mulExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        castExpr -> check();
        if(!Msaga::implicitlyConvertible(castExpr -> getExprType(), ExprType::Int))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
        m_idn = nullptr;
    } else {
        m_errorHandler();
    }
}

void CastExpression::check(){
    if(checkChildren<NodeType::UnaryExpression>()) {
        UnaryExpression *uExpr = static_cast<UnaryExpression*>(m_children[0].get());
        uExpr -> check();
        m_idn = uExpr -> getIdentifier();

        m_exprType = uExpr -> getExprType();
        m_isLValue = uExpr -> isLValue();
    } else if(checkChildren<NodeType::LeafLeftBracket, NodeType::TypeName, NodeType::LeafRightBracket, NodeType::CastExpression>()) {
        TypeName *tn = static_cast<TypeName*>(m_children[1].get());
        CastExpression *castExpr = static_cast<CastExpression*>(m_children[3].get());

        tn -> check();
        castExpr -> check();
        if(!(Msaga::explicitlyConvertible(castExpr -> getExprType(), tn -> getExprType())))
            m_errorHandler();

        m_exprType = tn -> getExprType();
        m_isLValue = false;
        m_idn = nullptr;
    } else {
        m_errorHandler();
    }
}

void UnaryExpression::check() {
    if(checkChildren<NodeType::PostfixExpression>()) {
        PostfixExpression *pExpr = static_cast<PostfixExpression*>(m_children[0].get());
        pExpr -> check();
        m_idn = pExpr -> getIdentifier();

        m_exprType = pExpr -> getExprType();
        m_isLValue = pExpr -> isLValue();
    } else if(checkChildren<NodeType::LeafInc, NodeType::UnaryExpression>() ||
              checkChildren<NodeType::LeafDec, NodeType::UnaryExpression>() )
    {
        UnaryExpression *uExpr = static_cast<UnaryExpression*>(m_children[1].get());
        uExpr -> check();
        if(!(uExpr -> isLValue() && Msaga::implicitlyConvertible(uExpr -> getExprType(), ExprType::Int)))
            m_errorHandler();
        
        m_exprType = ExprType::Int;
        m_isLValue = false;
        m_idn = nullptr;
    } else if(checkChildren<NodeType::UnaryOperator, NodeType::CastExpression>()) {
        CastExpression *cExpr = static_cast<CastExpression*>(m_children[1].get());

        cExpr -> check();
        if(!Msaga::implicitlyConvertible(cExpr -> getExprType(), ExprType::Int))
            m_errorHandler();
        
        m_exprType = ExprType::Int;
        m_isLValue = false;
        m_idn = nullptr;
    } else {
        m_errorHandler();
    }
}

void PostfixExpression::check() {
    if(checkChildren<NodeType::PrimaryExpression>()) {
        PrimaryExpression *pExpr = static_cast<PrimaryExpression*>(m_children[0].get());
        pExpr -> check();

        m_idn = pExpr -> getIdentifier();
        m_functionType = pExpr -> getFunctionType();
        m_exprType = pExpr -> getExprType();
        m_isLValue = pExpr -> isLValue();
    } else if(checkChildren<NodeType::PostfixExpression, NodeType::LeafLeftSquareBracket, NodeType::Expression, NodeType::LeafRightSquareBracket>()) {
        PostfixExpression *pExpr = static_cast<PostfixExpression*>(m_children[0].get());
        Expression *expr = static_cast<Expression*>(m_children[2].get());

        pExpr -> check();
        if(!Msaga::isArrayType(pExpr -> getExprType()))
            m_errorHandler();
        expr -> check();
        if(!Msaga::implicitlyConvertible(expr -> getExprType(), ExprType::Int))
            m_errorHandler();
        
        m_exprType = Msaga::arrayBaseType(pExpr -> getExprType());
        m_isLValue = !Msaga::isConst(pExpr -> getExprType());
        m_idn = nullptr;
    } else if(checkChildren<NodeType::PostfixExpression, NodeType::LeafLeftBracket, NodeType::LeafRightBracket>()) {
        PostfixExpression *pExpr = static_cast<PostfixExpression*>(m_children[0].get());

        pExpr -> check();
        const Msaga::FunctionType *ft = pExpr -> getFunctionType();
        if(!(pExpr -> getExprType() == ExprType::Function && ft != nullptr && ft -> argumentsTypes.size() == 1 && ft -> argumentsTypes[0] == ExprType::Void))
            m_errorHandler();

        m_exprType = ft -> returnType;
        m_isLValue = false;
        m_idn = nullptr;
    } else if(checkChildren<NodeType::PostfixExpression, NodeType::LeafLeftBracket, NodeType::ArgumentList, NodeType::LeafRightBracket>()) {
        PostfixExpression *pExpr = static_cast<PostfixExpression*>(m_children[0].get());
        ArgumentList *al = static_cast<ArgumentList*>(m_children[2].get());

        pExpr -> check();
        al -> check();

        const Msaga::FunctionType *ft = pExpr -> getFunctionType();
        if(pExpr -> getExprType() == ExprType::Function && ft != nullptr && ft -> argumentsTypes.size() == al -> getSize()) {
            bool compatible = true;
            for(size_t i = 0;i < al -> getSize(); i++)
                compatible = compatible && Msaga::implicitlyConvertible(al -> getType(i), ft -> argumentsTypes[i]);

            if(!compatible)
                m_errorHandler();
        } else {
            m_errorHandler();
        }

        m_exprType = ft -> returnType;
        m_isLValue = false;
        m_idn = nullptr;
    } else if(checkChildren<NodeType::PostfixExpression, NodeType::LeafInc>() ||
              checkChildren<NodeType::PostfixExpression, NodeType::LeafDec>())
    {
        PostfixExpression *pExpr = static_cast<PostfixExpression*>(m_children[0].get());

        pExpr -> check();
        if(!(pExpr -> isLValue() && Msaga::implicitlyConvertible(pExpr -> getExprType(), ExprType::Int)))
            m_errorHandler();

        m_exprType = ExprType::Int;
        m_isLValue = false;
        m_idn = nullptr;
    } else {
        m_errorHandler();
    }
}


void PostfixExpression::generateCode(std::ostream &stream) {
    if(checkChildren<NodeType::PostfixExpression, NodeType::LeafLeftSquareBracket, NodeType::Expression, NodeType::LeafRightSquareBracket>()) {
        m_children[2] -> generateCode(stream);
        PostfixExpression *pExpr = static_cast<PostfixExpression*>(m_children[0].get());
        if(pExpr -> getIdentifier() == nullptr) {
            // =>* ConstCharacterArray
            stream << '\t' << "POP R0\n"; //index
            stream << '\t' << "ADD SP, R0, R0\n"; // address
            stream << '\t' << "LOAD R0, (R0)\n";
            stream << '\t' << "PUSH R0\n";
        } else {
            // array variable
            stream << '\t' << "POP R0\n"; //index
            stream << '\t' << "ADD FP, R0, R0\n"; 
            stream << '\t' << "LOAD R0, (R0 + 0" << std::hex << pExpr -> getIdentifier() -> offset << ")\n";
            stream << '\t' << "PUSH R0\n";
        }
    } else if(checkChildren<NodeType::PostfixExpression, NodeType::LeafLeftBracket, NodeType::LeafRightBracket>()) {
        PostfixExpression *pExpr = static_cast<PostfixExpression*>(m_children[0].get());

        stream << '\t' << "PUSH R6\n";
        stream << '\t' << "CALL func"  <<  pExpr -> getIdentifier() -> id << '\n';
        stream << '\t' << "POP R6\n";
        stream << '\t' << "PUSH R5\n";
    } else if(checkChildren<NodeType::PostfixExpression, NodeType::LeafLeftBracket, NodeType::ArgumentList, NodeType::LeafRightBracket>()) {
        PostfixExpression *pExpr = static_cast<PostfixExpression*>(m_children[0].get());
        ArgumentList *aList = static_cast<ArgumentList*>(m_children[2].get());

        stream << '\t' << "PUSH R6\n";
        aList -> generateCode(stream);
        stream << '\t' << "CALL func" << pExpr -> getIdentifier() -> id << '\n';
        for(size_t i = 0; i< aList -> getSize(); i++)
            stream << '\t' << "POP R0\n";
        stream << '\t' << "POP R6\n";
        stream << '\t' << "PUSH R5\n";
    } else if(checkChildren<NodeType::PostfixExpression, NodeType::LeafInc>()) {
        PostfixExpression *pExpr = static_cast<PostfixExpression*>(m_children[0].get());
        stream << '\t' << "LOAD R0, (R6 + 0" << std::hex << pExpr -> getIdentifier() -> offset << ")\n";
        stream << '\t' << "PUSH R0\n";
        stream << '\t' << "ADD R0, 1, R0\n";
        stream << '\t' << "STORE R0, (R6 + 0" << std::hex << pExpr -> getIdentifier() -> offset << ")\n";
    } else if(checkChildren<NodeType::PostfixExpression, NodeType::LeafDec>()) {
        PostfixExpression *pExpr = static_cast<PostfixExpression*>(m_children[0].get());
        stream << '\t' << "LOAD R0, (R6 + 0" << std::hex << pExpr -> getIdentifier() -> offset << ")\n";
        stream << '\t' << "PUSH R0\n";
        stream << '\t' << "ADD R0, -1, R0\n";
        stream << '\t' << "STORE R0, (R6 + 0" << std::hex << pExpr -> getIdentifier() -> offset << ")\n";
    } else {
        Msaga::allChildrenGenerateCode(stream, this);
    }
}