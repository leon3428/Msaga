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

class LeafCharacter : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafCharacter; }
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

class LeafAssignment : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafAssignment; }
};

class LeafLogOr : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafLogOr; }
};

class LeafLogAnd : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafLogAnd; }
};

class LeafBitOr : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafBitOr; }
};

class LeafBitXor : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafBitXor; }
};

class LeafBitAnd : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafBitAnd; }
};

class LeafEq : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafEq; }
};

class LeafNeq : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafNeq; }
};

class LeafLt : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafLt; }
};

class LeafGt : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafGt; }
};

class LeafGte : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafGte; }
};

class LeafLte : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafLte; }
};

class LeafPlus : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafPlus; }
};

class LeafMinus : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafMinus; }
};


class LeafMult : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafMult; }
};

class LeafDiv : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafDiv; }
};

class LeafMod : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafMod; }
};

class LeafKwConst : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafKwConst; }
};

class LeafKwVoid : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafKwVoid; }
};

class LeafKwInt : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafKwInt; }
};

class LeafKwChar : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafKwChar; }
};

class LeafInc : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafInc; }
};

class LeafDec : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafDec; }
};

class LeafLeftSquareBracket : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafLeftSquareBracket; }
};

class LeafRightSquareBracket : public GenericLeaf {
public:
    using GenericLeaf::GenericLeaf;

    [[nodiscard]] inline NodeType getNodeType() const override { return NodeType::LeafRightSquareBracket; }
};

#endif // LEAFS_H