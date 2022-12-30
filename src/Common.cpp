#include "Common.hpp"

// true if a can be implicitly converted to b
bool Msaga::implicitlyConvertible(ExprType a, ExprType b) {
    if(a == b)
        return true;

    //const
    if(a == ExprType::ConstInt && b == ExprType::Int)
        return true;
    if(a == ExprType::Int && b == ExprType::ConstInt)
        return true;

    if(a == ExprType::ConstChar && b == ExprType::Char)
        return true;
    if(a == ExprType::Char && b == ExprType::ConstChar)
        return true;

    //char
    if(a == ExprType::Char && b == ExprType::Int)
        return true;

    //array
    if(a == ExprType::ArrayInt && b == ExprType::ArrayConstInt)
        return true;

    if(a == ExprType::ArrayChar && b == ExprType::ArrayConstChar)
        return true;

    return false;
}

ExprType Msaga::arrayBaseType(ExprType a) {
    if(a == ExprType::ArrayChar)
        return ExprType::Char;

    if(a == ExprType::ArrayInt)
        return ExprType::Int;

    if(a == ExprType::ArrayConstChar)
        return ExprType::ConstChar;

    if(a == ExprType::ArrayConstInt)
        return ExprType::ConstInt;

    return ExprType::Void;
}

ExprType Msaga::baseTypeToArray(ExprType a) {
    if(a == ExprType::Char)
        return ExprType::ArrayChar;

    if(a == ExprType::Int)
        return ExprType::ArrayInt;

    if(a == ExprType::ConstChar)
        return ExprType::ArrayConstChar;

    if(a == ExprType::ConstInt)
        return ExprType::ArrayConstInt;

    return ExprType::Void;
}

Msaga::FunctionType::FunctionType(const std::vector<ExprType> &argsTypes, ExprType retType) 
    : argumentsTypes(argsTypes), returnType(retType) {}

bool Msaga::isValidChar(const std::string &s) {
    if(s.size() == 1)
        return true;
    if(s.size() == 2 && (s == "\\t" || s == "\\n" || s == "\\0" || s == "\\'" || s == "\\\"" || s == "\\\\"))
        return true;
    return false;
}

bool Msaga::isValidCharArray(const std::string &s) {
    for(size_t i = 0;i < s.size(); i++) {
        if(s[i] == '\\') {
            if(i + 1 >= s.size() - 1)
                return false;
            if(s[i+1] != 't' || s[i+1] != 'n' || s[i+1] != '0' || s[i+1] != '\'' || s[i+1] != '\"' || s[i+1] != '\\')
                return false;
        }
    }
    return true;
}