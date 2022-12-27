#ifndef LEAFS_H
#define LEAFS_H

#include "SyntaxTree.hpp"

/**
 * @brief Leafs of the syntax tree
 * 
 */
class GenericLeaf : public SyntaxTreeNode {
private:
    int m_row = -1;                                                 ///> row in original source file
    std::string m_lexicalUnit = "";                                 ///> actual string read from source

public:
    GenericLeaf() = default;
    GenericLeaf(int row, const std::string &lexicalUnit);

    void check() override;
    
    [[nodiscard]] inline int getRow() const { return m_row; }
    [[nodiscard]] inline std::string getLexicalUnit() const { return m_lexicalUnit; }
};

class LeafIdn : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafIdn; }
};

class LeafNum : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafNum; }
};

class LeafChar : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafChar; }
};

class LeafCharArray : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafCharArray; }
};

class LeafLeftBracket : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafLeftBracket; }
};

class LeafRightBracket : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafRightBracket; }
};

#endif // LEAFS_H