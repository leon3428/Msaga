#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <vector>
#include <iostream>

enum class NodeType : uint8_t {
    PrimaryExpression, Expression, 
    AssignmentExpression, EqualsExpression, ComparisonExpression, 
    AdditiveExpression, MultiplicativeExpression, CastExpression,
    LogicalOrExpression, LogicalAndExpression,
    BitwiseOrExpression, BitwiseXorExpression, BitwiseAndExpression,
    PostfixExpression, UnaryExpression,

	ComplexCommand, ListCommand, Command, 
	ExpressionCommand, BranchCommand, LoopCommand,
	JumpCommand, TranslationUnit, ExternalDeclaration,

	FunctionDefinition, ParameterList, ParameterDeclaration,
	DeclarationList, Declaration, DeclaratorInitList,
	InitDeclarator, DirectDeclarator, Initializer,
	JoinExpressionList,

    LeafIdn, LeafNum, LeafCharacter, LeafCharArray,
    LeafComma, LeafAssignment, LeafLogOr, LeafLogAnd, LeafBitOr, LeafBitXor, LeafBitAnd,
    LeafEq, LeafNeq,
    LeafLt, LeafGt, LeafLte, LeafGte,
    LeafRightBracket, LeafLeftBracket,
    LeafRightSquareBracket, LeafLeftSquareBracket,
	LeafLeftCurlyBracket, LeafRightCurlyBracket,
    LeafPlus, LeafMinus, LeafMult, LeafDiv, LeafMod,
    LeafInc, LeafDec, LeafSemicolon, LeafTilde, LeafNeg,

	LeafKwIf, LeafKwElse, LeafKwWhile, LeafKwFor,
    LeafKwConst, LeafKwInt, LeafKwChar, LeafKwVoid,
	LeafKwContinue, LeafKwBreak, LeafKwReturn,

    TypeName, TypeSpecifier, UnaryOperator, ArgumentList, Error
};

enum class ExprType : int8_t {
    Void, Int, Char,
    ConstInt, ConstChar,
    ArrayInt, ArrayChar, ArrayConstInt, ArrayConstChar,
    Function, Error,
};


namespace Msaga {
    
    struct FunctionType {
        std::vector<ExprType> argumentsTypes;
        ExprType returnType;

        inline bool operator==(const FunctionType& other) const {
            return argumentsTypes == other.argumentsTypes && returnType == other.returnType;
        }

        inline bool operator!=(const FunctionType& other) const {
            return argumentsTypes != other.argumentsTypes || returnType != other.returnType;
        }
        
        FunctionType(const std::vector<ExprType> &argsTypes, ExprType retType);
    };

    bool implicitlyConvertible(ExprType a, ExprType b);
    bool explicitlyConvertible(ExprType a, ExprType b);

    inline bool isArrayType(ExprType a) {
        return a == ExprType::ArrayChar || a == ExprType::ArrayInt || a == ExprType::ArrayConstChar || a == ExprType::ArrayConstInt;
    }

    ExprType arrayBaseType(ExprType a);
	ExprType baseTypeToArray(ExprType a);

    inline bool isConst(ExprType a) {
        return a == ExprType::ConstChar || a == ExprType::ConstInt;
    }
	inline bool isConstArray(ExprType a) {
        return a == ExprType::ArrayConstChar || a == ExprType::ArrayConstInt;
    }
	inline bool isNumber(ExprType a) {
		return a == ExprType::Char || a == ExprType::Int;
	}
    bool isValidChar(const std::string &s);
    bool isValidCharArray(const std::string &s);

    std::string exprTypeToString(ExprType t);

    inline void writeConstToReg(std::ostream& stream, std::string_view reg, int constant) {
        if(constant < (1 << 12)) {
            stream << '\t' << "addi " << reg << ", x0, " << constant << '\n';
        } else {
            stream << '\t' << "lui " << reg << ", %hi(" << constant << ")\n";
            stream << '\t' << "addi " << reg << ',' << reg << " %lo(" << constant << ")\n"; 
        }
    }
    inline void writeLabelToReg(std::ostream& stream, std::string_view reg, std::string_view label) {
        stream << '\t' << "lui " << reg << ", %hi(" << label << ")\n";
        stream << '\t' << "addi " << reg << ',' << reg << " %lo(" << label << ")\n"; 
    }

    inline void writeRegToStack(std::ostream& stream, std::string_view reg) {
        stream << '\t' << "addi sp, sp, -4\n";
        stream << '\t' << "sw " << reg << ", 0(sp)\n";
    }
}

#endif // GLOBAL_H