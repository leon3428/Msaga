#ifndef GLOBAL_H
#define GLOBAL_H

#include <unordered_map>
#include <forward_list>
#include <string>

#include "SyntaxTree.hpp"

struct Identifier {
    std::forward_list<PrimitiveExprType> exprType;
    bool LValue;
};

namespace Global {
    extern std::unordered_map<std::string, Identifier> identifierTable;
}


#endif // GLOBAL_H