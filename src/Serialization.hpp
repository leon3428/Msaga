#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "Common.hpp"
#include "SyntaxTree.hpp"

namespace Msaga {
    [[nodiscard]] std::string NodeTypeToString(NodeType nt);
    SyntaxTreeNode* constructInnerNode(const std::string &s, SyntaxTreeNode *parent);
    SyntaxTreeNode* constructLeafNode(const std::string &s, int row, const std::string &lexicalUnit, SyntaxTreeNode *parent);
    [[nodiscard]] bool isLeaf(NodeType nt);
}

#endif // SERIALIZATION_H