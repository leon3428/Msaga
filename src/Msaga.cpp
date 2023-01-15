#include <iostream>
#include <fstream>
#include "SyntaxTree.hpp"

int main() {
    std::ifstream inputStream("test/examples6/01/test.in");
    std::ofstream outputStream("out.asm");

    SyntaxTree st;
    st.load(inputStream);
    st.check();
    st.generateCode(outputStream);

    outputStream.close();
    return 0;
}