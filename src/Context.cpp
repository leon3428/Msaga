#include "Context.hpp"

static int maxId = 0;

Identifier::Identifier(ExprType type, bool isDefined, const Msaga::FunctionType *ft, int off, const std::string &n)
    : exprType(type), defined(isDefined), functionType(ft), id(maxId++), offset(off), name(n) {}

ContextNode::ContextNode(ContextNode *parent)
    : m_parent(parent), m_maxOffset(4), m_minOffset(-4) {}

Identifier* ContextNode::getIdentifier(const std::string &name) {
    if(inLocalScope(name))
        return &m_identifierTable[name];
    if(m_parent == nullptr)
        return nullptr;
    return m_parent -> getIdentifier(name);
}

[[nodiscard]] std::tuple<int,bool> ContextNode::getOffset(const std::string &name) {
    if(inLocalScope(name)){
        int offset = m_identifierTable[name].offset;
        if(offset > 0)
            offset += m_blockOffset;
        return {offset, m_parent == nullptr};
    }
        
    if(m_parent == nullptr)
        return {0, false};
    return m_parent -> getOffset(name);
}

bool ContextNode::allDefined(ContextNode *globalContext) {
    for(auto const& [name, identifier] : m_identifierTable) {
        if(identifier.defined || identifier.exprType != ExprType::Function)
            continue;

        Identifier *global_idn = globalContext -> getIdentifier(name);
        if(global_idn == nullptr || !(global_idn -> defined))
            return false;
        if(global_idn -> functionType -> returnType != identifier.functionType -> returnType)
            return false;
        if(global_idn -> functionType -> argumentsTypes != identifier.functionType -> argumentsTypes)
            return false;
    }
    return true;
}