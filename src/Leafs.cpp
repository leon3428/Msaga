#include "Leafs.hpp"

GenericLeaf::GenericLeaf(int row, const std::string &lexicalUnit)
    : m_row(row), m_lexicalUnit(lexicalUnit) {}

void GenericLeaf::check() {}