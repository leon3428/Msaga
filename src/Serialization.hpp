#include "Common.hpp"

namespace Msaga {
    [[nodiscard]] std::string NodeTypeToString(NodeType nt);
    [[nodiscard]] NodeType StringToNodeType(const std::string &s); 
    [[nodiscard]] bool isLeaf(NodeType nt);
}