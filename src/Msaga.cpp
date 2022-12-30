#include <iostream>
#include <fstream>
#include "SyntaxTree.hpp"

int main() {
    //std::ifstream inputStream("test/examples/15_cast1/test.in");

    SyntaxTree st;
    st.load(std::cin);
    //st.print();
    st.check();
    return 0;
}