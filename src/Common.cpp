#include "Common.hpp"

std::unordered_map<std::string, Identifier> Global::identifierTable;


// true if a can be implicitly converted to b
bool implicitlyConvertible(ExprType a, ExprType b) {
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