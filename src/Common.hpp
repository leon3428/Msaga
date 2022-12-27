#ifndef GLOBAL_H
#define GLOBAL_H

#include <unordered_map>
#include <forward_list>
#include <string>
#include <vector>

enum class NodeType : uint8_t {
    PrimaryExpression, Expression, 
    AssignmentExpression, EqualsExpression, ComparisonExpression, 
    AdditiveExpression, MultiplicativeExpression, CastExpression,
    LogicalOrExpression, LogicalAndExpression,
    BitwiseOrExpression, BitwiseXorExpression, BitwiseAndExpression,
    PostfixExpression, UnaryExpression,

    LeafIdn, LeafNum, LeafCharacter, LeafCharArray,
    LeafComma, LeafAssignment, LeafLogOr, LeafLogAnd, LeafBitOr, LeafBitXor, LeafBitAnd,
    LeafEq, LeafNeq,
    LeafLt, LeafGt, LeafLte, LeafGte,
    LeafRightBracket, LeafLeftBracket,
    LeafRightSquareBracket, LeafLeftSquareBracket,
    LeafPlus, LeafMinus, LeafMult, LeafDiv, LeafMod,
    LeafInc, LeafDec,

    LeafKwConst, LeafKwInt, LeafKwChar, LeafKwVoid,

    TypeName, TypeSpecifier, UnaryOperator, ArgumentList
};

enum class ExprType : int8_t {
    Void, Int, Char,
    ConstInt, ConstChar,
    ArrayInt, ArrayChar, ArrayConstInt, ArrayConstChar,
    Function,
};


namespace Global {

    extern std::unordered_map<std::string, Msaga::Identifier> identifierTable;
}

namespace Msaga {
    struct Identifier {
        ExprType exprType;
        bool LValue;
    };

    struct FunctionType {
        std::vector<ExprType> argumentsTypes;
        ExprType returnType;

        FunctionType(const std::vector<ExprType> &argsTypes, ExprType retType);
    };

    bool implicitlyConvertible(ExprType a, ExprType b);

    inline bool isArrayType(ExprType a) {
        return a == ExprType::ArrayChar || a == ExprType::ArrayInt || a == ExprType::ArrayConstChar || a == ExprType::ArrayConstInt;
    }

    ExprType arrayBaseType(ExprType a);

    inline bool isConst(ExprType a) {
        return a == ExprType::ConstChar || a == ExprType::ConstInt;
    }
}


#endif // GLOBAL_H