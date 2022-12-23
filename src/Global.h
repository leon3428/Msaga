#ifndef GLOBAL_H
#define GLOBAL_H

#include <unordered_map>
#include <string>

struct Identifier {
    std::string type;
    bool LValue;
};

std::unordered_map<std::string, Identifier> identifierTable;

#endif //GLOBAL_H