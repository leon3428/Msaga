#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <string>
#include <vector>
#include <memory>
#include "Common.hpp"

/**
 * @brief most generic class of the tree
 * 
 */
class SyntaxTreeNode {
protected:
    std::vector<std::unique_ptr<SyntaxTreeNode> > m_children;   ///> child nodes

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
    const SyntaxTreeNode* addChild(Args&&... args) {
        m_children.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));

        return m_children.back().get();
    }
};

#endif //SYNTAX_TREE_H