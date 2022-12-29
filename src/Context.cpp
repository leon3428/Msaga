#include "Context.hpp"

Identifier::Identifier(ExprType type, bool isDefined, const Msaga::FunctionType *ft)
    : exprType(type), defined(isDefined), functionType(ft) {}

ContextNode::ContextNode(ContextNode *parent)
    : m_parent(parent) {}

Identifier* ContextNode::getIdentifier(const std::string &name) {
    if(inLocalScope(name))
        return &m_identifierTable[name];
    if(m_parent == nullptr)
        return nullptr;
    return m_parent -> getIdentifier(name);
}