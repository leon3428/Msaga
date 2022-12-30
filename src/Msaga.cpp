#include <iostream>
#include <fstream>
#include "SyntaxTree.hpp"

int main() {
    std::ifstream inputStream("test/examples/01_idn/test.in");

    SyntaxTree st;
    st.load(inputStream);
    st.print();
    st.check();
    return 0;
}