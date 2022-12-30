#ifndef CONTEXT_H
#define CONTEXT_H

#include "Common.hpp"
#include <map>
#include <string>
#include <memory>
#include <vector>

struct Identifier {
    ExprType exprType = ExprType::Void;
    bool defined = false;
    const Msaga::FunctionType *functionType = nullptr;

    Identifier() = default;
    Identifier(ExprType type, bool isDefined, const Msaga::FunctionType *ft);
};

class ContextNode {
private:
    ContextNode *m_parent = nullptr;
    std::map<std::string, Identifier> m_identifierTable;
public:
    ContextNode() = default;
    ContextNode(ContextNode *parent);

    [[nodiscard]] inline bool inLocalScope(const std::string &name) const { return m_identifierTable.find(name) != m_identifierTable.end(); }
    [[nodiscard]] Identifier* getIdentifier(const std::string &name);
    [[nodiscard]] inline bool inScope(const std::string &name) { return getIdentifier(name) != nullptr; }
    inline void declareVariable(const std::string &name, ExprType exprType) {
        m_identifierTable[name] = {exprType, true, nullptr};
    }
    inline void declareFunction(const std::string &name, bool isDefined, const Msaga::FunctionType &functionType) {
        m_identifierTable[name] = {ExprType::Function, isDefined, &functionType};
    }
};

#endif //CONTEXT_H