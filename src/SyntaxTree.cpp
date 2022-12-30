#include "SyntaxTree.hpp"
#include <iostream>
#include "Serialization.hpp"
#include "Leafs.hpp"

void SyntaxTreeNode::m_errorHandler() {
    std::cout << Msaga::NodeTypeToString(this -> getNodeType()) << " ::=";
    for(size_t i = 0;i < m_children.size();i++) {
        std::cout << ' ' << Msaga::NodeTypeToString(m_children[i] -> getNodeType());

        if(Msaga::isLeaf(this -> getNodeType())) {
            GenericLeaf *l = static_cast<GenericLeaf*>(m_children[i].get());
            std::cout << '(' << l -> getRow() << ',' << l -> getLexicalUnit() << ')';
        }
    }

    std::cout << '\n';
    exit(1);
}