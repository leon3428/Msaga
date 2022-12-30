#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <string>
#include <vector>
#include <memory>
#include "Common.hpp"
#include "Context.hpp"

/**
 * @brief most generic class of the tree
 * 
 */
class SyntaxTreeNode {
protected:
    std::vector<std::unique_ptr<SyntaxTreeNode> > m_children;   ///> child nodes
    ContextNode* m_localContext; 

    void m_errorHandler();
    
    template<NodeType... TYPES>
    inline bool checkChildren() const {
        if(sizeof...(TYPES) != m_children.size())
            return false;

        int i = 0;
        bool ret = true;
        ([&]{
            ret = ret && (m_children[i] -> getNodeType() == TYPES);
            i++;
        } (), ...);
        return ret;
    }

public: 
    virtual void check() = 0;                                   ///> checks all associated rules
    virtual inline NodeType getNodeType() const = 0;

    template<typename T, typename... Args>
    SyntaxTreeNode* addChild(Args&&... args) {
        m_children.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));

        return m_children.back().get();
    }

    [[nodiscard]] inline size_t getChildrenCnt() const { return m_children.size(); }
    [[nodiscard]] inline SyntaxTreeNode* getChild(size_t i) { return m_children[i].get(); }
    [[nodiscard]] inline ContextNode* getLocalContextNode() { return m_localContext; }
    inline void setLocalContextNode(ContextNode *contextNode) { m_localContext = contextNode; }
};

struct StackItem {
    SyntaxTreeNode *node;
    int indentLevel;
    bool insideLoop;
    ExprType functionReturnType;
    int characterArrayLength;

    StackItem(SyntaxTreeNode *n, int indLevel, bool inLoop, ExprType funRetType, int charArrayLen);
};

class SyntaxTree {
private:
    std::vector<std::unique_ptr<ContextNode> > m_contextNodes;
    std::unique_ptr<SyntaxTreeNode> m_root;

    void m_printHelper(SyntaxTreeNode *node, int indent_level);

public:
    void load(std::istream &stream);
    inline void print() { m_printHelper(m_root.get(), 0); }
    inline void check() { m_root -> check(); }
};

#endif //SYNTAX_TREE_H