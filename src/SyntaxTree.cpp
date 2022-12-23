#include "SyntaxTree.h"

template<typename T, typename... Args>
const T* SyntaxTreeNode::addChild(Args&&... args)
{
    m_children.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));

    return m_children.back();
}

Leaf::Leaf(UniformCharacter uniformCharacter, int row, const std::string &lexicalUnit)
    : m_uniformCharacter(uniformCharacter), m_row(row), m_lexicalUnit(lexicalUnit) {}

bool Leaf::check() {
    return true;
}