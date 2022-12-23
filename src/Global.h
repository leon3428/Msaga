#ifndef GLOBAL_H
#define GLOBAL_H

#include <unordered_map>
#include <string>
#include <forward_list>

enum class PrimitiveExprType : int8_t {
    Int, Char, Const, Array, Void
};

struct Identifier {
    std::forward_list<PrimitiveExprType> type;
    bool LValue;
};


std::unordered_map<std::string, Identifier> identifierTable;

#endif //GLOBAL_H