#ifndef GLOBAL_H
#define GLOBAL_H

#include <unordered_map>
#include <forward_list>
#include <string>

#include "SyntaxTree.hpp"

struct Identifier {
    ExprType exprType;
    bool LValue;
};

namespace Global {
    extern std::unordered_map<std::string, Identifier> identifierTable;
}

/**
 * @brief true if a can be implicitly converted to b
 * 
 * @param a 
 * @param b 
 * @return true 
 * @return false 
 */
bool implicitlyConvertible(ExprType a, ExprType b);

#endif // GLOBAL_H