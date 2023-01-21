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
    int id = -1;
    int offset = 0;
    std::string name = "";

    Identifier() = default;
    Identifier(ExprType type, bool isDefined, const Msaga::FunctionType *ft, int off, const std::string &n);
};

class ContextNode {
private:
    ContextNode *m_parent = nullptr;
    std::map<std::string, Identifier> m_identifierTable;
    std::vector<std::unique_ptr<Msaga::FunctionType> > m_functionTypes;
    std::vector<ContextNode*> m_children;
    int m_maxOffset = 4;
    int m_blockOffset;

public:
    ContextNode() = default;
    ContextNode(ContextNode *parent);

    [[nodiscard]] inline bool inLocalScope(const std::string &name) const { return m_identifierTable.find(name) != m_identifierTable.end(); }
    [[nodiscard]] Identifier* getIdentifier(const std::string &name);
    [[nodiscard]] int getOffset(const std::string &name);
    [[nodiscard]] inline bool inScope(const std::string &name) { return getIdentifier(name) != nullptr; }
    [[nodiscard]] bool allDefined(ContextNode *globalContext);
    [[nodiscard]] inline ContextNode* getParent() { return m_parent; }
    [[nodiscard]] inline int getMaxOffset() const { return m_maxOffset; }
    [[nodiscard]] inline int getBlockOffset() const { return m_blockOffset; }
    [[nodiscard]] inline int getChildrenCnt() const { return m_children.size(); }
    [[nodiscard]] inline ContextNode* getChild(size_t i) { return m_children[i]; }
    inline void addChild(ContextNode *child) { m_children.push_back(child); }
    inline void setBlockOffset(int blockOffset) { m_blockOffset = blockOffset; }

    inline void declareVariable(const std::string &name, ExprType exprType) {
        m_identifierTable[name] = {exprType, true, nullptr, m_maxOffset, name};
        m_maxOffset += 4;
    }
    inline void declareArrayVariable(const std::string &name, ExprType exprType, int arrayLength) {
        m_identifierTable[name] = {exprType, true, nullptr, m_maxOffset + (arrayLength - 1) * 4, name};
        m_maxOffset += arrayLength * 4;
    }

    inline void declareFunction(const std::string &name, bool isDefined, const Msaga::FunctionType &functionType) {
        m_functionTypes.push_back(std::make_unique<Msaga::FunctionType>(functionType));
        m_identifierTable[name] = {ExprType::Function, isDefined, m_functionTypes.back().get(), 0, name};
    }    
};

#endif //CONTEXT_H